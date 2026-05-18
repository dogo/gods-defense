#!/usr/bin/env python3
from __future__ import annotations

from collections import Counter
from pathlib import Path
from typing import NamedTuple
import random
import xml.etree.ElementTree as ET

from PIL import Image
from PIL import ImageEnhance
from PIL import ImageDraw
from PIL import ImageFilter
from PIL import ImageOps


ROOT = Path(__file__).resolve().parents[2]
TILED = ROOT / "tower-defense-2d-game-kit-v1.1" / "td-tilesets" / "version-for-the-program-Tiled" / "PNG"
DEST = ROOT / "PSP Project" / "Res" / "maps"
DEBUG_DIR = ROOT / "tools" / "asset_pipeline" / "_debug"
TILE_SIZE = 32
GRID_SIZE = 15
MAP_SIZE = TILE_SIZE * GRID_SIZE

# Render at source-native resolution (256px per cell), then LANCZOS-downsize
# to MAP_SIZE before saving. Keeps full tile detail until the final pass.
HIRES_SCALE = 8
RENDER_TILE = TILE_SIZE * HIRES_SCALE   # 256
RENDER_MAP = MAP_SIZE * HIRES_SCALE     # 3840

CORNER_BAND = 2
POCKET_MAX = 1
DEAD_ZONE_MAX = 4
DENSITY_POWER = 0.75

CLASS_COLORS = {
    "path":           (210, 60, 60, 200),
    "path_margin":    (240, 165, 70, 180),
    "corner":         (200, 90, 220, 180),
    "edge":           (80, 140, 230, 180),
    "pocket":         (245, 230, 90, 200),
    "dead_zone":      (120, 120, 120, 180),
    "buildable_core": (90, 200, 90, 170),
}

CLASS_ORDER = (
    "path", "path_margin", "corner", "edge",
    "pocket", "dead_zone", "buildable_core",
)

DECOR_CLASSES = ("corner", "edge", "dead_zone", "pocket")
FORBIDDEN_FOR_PROPS = ("path", "path_margin", "buildable_core")

ZONE_PALETTE = (
    (90, 200, 150), (210, 130, 90), (160, 100, 220), (90, 160, 220),
    (220, 200, 90), (220, 90, 140), (90, 220, 220), (140, 220, 90),
    (200, 180, 100), (200, 100, 200), (110, 200, 110), (220, 160, 80),
)

BIOME_PROFILES = {
    "olympus": {
        # tail_2 — ATOMIC ONLY (audited at native 256px)
        # 43=white watchtower, 29=single cactus, 32=spine, 33=bull skull,
        # 42,50,51=dry trees, 23=stump
        "category_pools": {
            "watchtower": (43,),
            "dry_tree":   (42, 50, 51),
        },
        "rules": {
            "corner": {"category": "watchtower", "density": 0.30, "scale": (0.95, 1.00), "max": 1},
        },
        "terrain_tints": {
            "corner":         (140,  87,  42,  28),
            "edge":           (180, 130,  60,  20),
            "buildable_core": (240, 200, 110,  18),
        },
    },
    "icarusfalls": {
        # tail_7 — ATOMIC ONLY (already correct)
        # 35-40=dead trees, 24=cabin, 33=single grave, 27=bull skull, 28=spine
        "category_pools": {
            "dead_tree": {"anchor": (35, 36), "filler": (37, 38, 39, 40)},
            "cabin":     (24,),
            "grave":     (33,),
            "skull":     (27, 28),
        },
        "rules": {
            "corner":    {"category": "dead_tree", "density": 0.30, "scale": (0.95, 1.00), "max": 1},
            "dead_zone": {"category": "grave",     "density": 0.90, "scale": (0.85, 1.00)},
            "pocket":    {"category": "cabin",     "density": 1.00, "scale": (0.95, 1.00)},
        },
        "terrain_tints": {
            "corner":         ( 30,  50,  45,  75),
            "edge":           ( 38,  55,  48,  55),
            "dead_zone":      ( 32,  48,  42,  80),
            "pocket":         ( 28,  45,  40,  90),
            "buildable_core": ( 45,  65,  55,  35),
        },
    },
    "rescueathena": {
        # tail_1 — ATOMIC ONLY (full rewrite after re-audit)
        # 28=ONLY atomic house, 38=windmill atomic, 33=ONLY atomic single tree
        # Tiles 39, 40 are tilemap pieces (gate, isolated roof) — NOT used standalone
        "category_pools": {
            "house":    (28,),
            "windmill": (38,),
            "tree":     (33,),
        },
        "rules": {
            "corner":    {"category": "tree",     "density": 0.30, "scale": (0.95, 1.00), "max": 1},
            "dead_zone": {"category": "house",    "density": 0.75, "scale": (0.85, 1.00)},
        },
        "terrain_tints": {
            "corner":         ( 60, 110,  30,  38),
            "edge":           ( 90, 130,  40,  26),
            "dead_zone":      (110,  90,  60,  35),
            "buildable_core": (100, 145,  55,  18),
        },
    },
    "icymanipulator": {
        # tail_4 — ATOMIC ONLY (tile 29 removed from pine — it's actually pair-composite)
        # 21,23=stone towers atomic, 31=wooden cabin atomic,
        # 27,28=ONLY atomic single pines, 33,34=snow rocks, 37=campfire
        # Scales reduced and max=1 on dead_zone because pockets sit adjacent to
        # corners in this map; full-cell tower + full-cell cabin in neighbors
        # read as visual overlap. Single pine per dead_zone reads as landmark
        # rather than ambiguous cluster.
        "category_pools": {
            # Tile 21 only — tile 23 has content_bbox top-loaded (y=0..176)
            # with 80px transparent below, which lacks a shadow region so
            # the tower base abuts the road abruptly. Tile 21 fills the
            # frame (y=5..251) including a soft shadow base, grounding
            # correctly when placed against path cells.
            "tower":     (21,),
            "cabin":     (31,),
            # Tile 29 only — re-audit at native 256px showed tiles 27 and 28
            # are NOT atomic singles: 27 packs 4 pines in a 2x2 cluster,
            # 28 has 2 pines side by side. Tile 29 is the only true single
            # pine (bbox width 120/256, ratio 0.64).
            "pine":      (29,),
            "snow_rock": (33, 34),
        },
        "rules": {
            "corner":    {"category": "tower", "density": 0.30, "scale": (0.80, 0.90), "max": 1},
            # fill=True puts 1 atomic pine per dead_zone cell — mimics the
            # "snow forest cluster" feel from tail_4.tmx without using
            # composite tiles.
            "dead_zone": {"category": "pine",  "density": 1.00, "scale": (0.75, 0.90), "fill": True},
            "pocket":    {"category": "cabin", "density": 1.00, "scale": (0.80, 0.90)},
        },
        "terrain_tints": {
            "corner":         (190, 215, 230,  45),
            "edge":           (200, 220, 235,  32),
            "dead_zone":      (170, 195, 215,  50),
            "pocket":         (165, 190, 215,  55),
            "buildable_core": (215, 230, 245,  18),
        },
    },
}


class Zone(NamedTuple):
    zone_id: int
    class_name: str
    cells: tuple[tuple[int, int], ...]
    bbox: tuple[int, int, int, int]


class Placement(NamedTuple):
    tile_id: int
    x: int
    y: int
    scale: float
    category: str
    zone_id: int
    kind: str = "decor"
    alpha: int = 255


THEMES = {
    "olympus": {
        "tail": "tail_2",
        "base": 21,
        "road": 6,
        "tint": (255, 236, 186, 1.03),
        "road_tint": (246, 219, 150, 1.0),
    },
    "icarusfalls": {
        "tail": "tail_7",
        "base": 26,
        "road": 6,
        "tint": (190, 205, 190, 0.92),
        "road_tint": (210, 218, 206, 0.97),
    },
    "rescueathena": {
        "tail": "tail_1",
        "base": 42,
        "road": 6,
        "tint": (230, 236, 170, 1.0),
        "road_tint": (230, 221, 128, 1.0),
    },
    "icymanipulator": {
        "tail": "tail_4",
        "base": 35,
        "road": 6,
        "tint": (218, 236, 255, 1.02),
        "road_tint": (230, 242, 255, 1.02),
    },
}


def read_collision_grid(map_dir: Path) -> list[str]:
    root = ET.parse(map_dir / "map.xml").getroot()
    collision = root.findtext("CollisionMap")
    if not collision:
        raise RuntimeError(f"Missing CollisionMap in {map_dir / 'map.xml'}")

    rows = [line.strip() for line in collision.splitlines() if line.strip()]
    if len(rows) != GRID_SIZE or any(len(row) != GRID_SIZE for row in rows):
        raise RuntimeError(f"Expected {GRID_SIZE}x{GRID_SIZE} CollisionMap in {map_dir / 'map.xml'}")
    return rows


def read_path_points(map_dir: Path) -> list[tuple[int, int]]:
    root = ET.parse(map_dir / "map.xml").getroot()
    path = root.find("./Path[@Name='default']")
    if path is None:
        raise RuntimeError(f"Missing default Path in {map_dir / 'map.xml'}")
    return [
        (int(checkpoint.attrib["X"]), int(checkpoint.attrib["Y"]))
        for checkpoint in path.findall("Checkpoint")
    ]


def clamp_point(value: int) -> int:
    return max(0, min(MAP_SIZE - 1, value))


def clamp_path_point(point: tuple[int, int]) -> tuple[int, int]:
    x, y = point
    return (clamp_point(x), clamp_point(y))


def build_path_grid(points: list[tuple[int, int]]) -> list[list[bool]]:
    grid = [[False for _ in range(GRID_SIZE)] for _ in range(GRID_SIZE)]
    cells = [(clamp_point(x) // TILE_SIZE, clamp_point(y) // TILE_SIZE) for x, y in points]

    for (x0, y0), (x1, y1) in zip(cells, cells[1:]):
        if x0 == x1:
            start, end = sorted((y0, y1))
            for y in range(start, end + 1):
                grid[y][x0] = True
        elif y0 == y1:
            start, end = sorted((x0, x1))
            for x in range(start, end + 1):
                grid[y0][x] = True
        else:
            raise RuntimeError(f"Only orthogonal path segments are supported: {(x0, y0)} -> {(x1, y1)}")

    return grid


def load_tile(tail: str, tile_id: int) -> Image.Image:
    tile = Image.open(TILED / tail / f"{tile_id}.png").convert("RGBA")
    if tile.size != (RENDER_TILE, RENDER_TILE):
        tile = tile.resize((RENDER_TILE, RENDER_TILE), Image.Resampling.LANCZOS)
    return tile


def tinted(tile: Image.Image, color: tuple[int, int, int], brightness: float) -> Image.Image:
    r, g, b = color
    overlay = Image.new("RGBA", tile.size, (r, g, b, 38))
    result = Image.alpha_composite(tile.copy(), overlay)
    return ImageEnhance.Brightness(result).enhance(brightness)


def road_surface_fill(tile: Image.Image) -> Image.Image:
    # Crop the inner 12/32 region of the tile (proportional to original spec)
    inset = RENDER_TILE * 10 // 32
    outset = RENDER_TILE * 22 // 32
    center = tile.crop((inset, inset, outset, outset)).resize(
        (RENDER_TILE, RENDER_TILE), Image.Resampling.BICUBIC
    )
    center = center.filter(ImageFilter.GaussianBlur(0.35 * HIRES_SCALE))
    texture = Image.new("RGBA", (RENDER_MAP, RENDER_MAP), (0, 0, 0, 0))
    rng = random.Random("road-surface")

    for y in range(0, RENDER_MAP, RENDER_TILE):
        for x in range(0, RENDER_MAP, RENDER_TILE):
            block = center.copy()
            if rng.random() < 0.5:
                block = ImageOps.mirror(block)
            if rng.random() < 0.5:
                block = ImageOps.flip(block)
            block = ImageEnhance.Brightness(block).enhance(rng.uniform(0.96, 1.04))
            texture.alpha_composite(block, (x, y))
    return texture


def mask_to_image(source: Image.Image, mask: Image.Image) -> Image.Image:
    return Image.composite(source, Image.new("RGBA", source.size, (0, 0, 0, 0)), mask)


def set_alpha(image: Image.Image, alpha: int) -> Image.Image:
    result = image.copy()
    channel = result.getchannel("A").point(lambda value: value * alpha // 255)
    result.putalpha(channel)
    return result


def draw_road(canvas: Image.Image, points: list[tuple[int, int]], road_tile: Image.Image) -> None:
    # Canvas is RENDER_MAP. Path points come from XML in MAP_SIZE coords —
    # scale by HIRES_SCALE. No internal supersampling: rendering directly
    # at canvas resolution is already 8× the original render path.
    hi_points = [
        (clamp_point(x) * HIRES_SCALE, clamp_point(y) * HIRES_SCALE)
        for x, y in points
    ]
    hi_size = (RENDER_MAP, RENDER_MAP)

    edge_mask = Image.new("L", hi_size, 0)
    edge_draw = ImageDraw.Draw(edge_mask)
    edge_draw.line(hi_points, fill=255, width=38 * HIRES_SCALE, joint="curve")
    for x, y in hi_points:
        r = 19 * HIRES_SCALE
        edge_draw.ellipse((x - r, y - r, x + r, y + r), fill=255)
    edge_mask = edge_mask.filter(ImageFilter.GaussianBlur(1.1 * HIRES_SCALE))
    canvas.alpha_composite(mask_to_image(Image.new("RGBA", hi_size, (42, 27, 17, 150)), edge_mask))

    road_mask = Image.new("L", hi_size, 0)
    road_draw = ImageDraw.Draw(road_mask)
    road_draw.line(hi_points, fill=255, width=30 * HIRES_SCALE, joint="curve")
    for x, y in hi_points:
        r = 15 * HIRES_SCALE
        road_draw.ellipse((x - r, y - r, x + r, y + r), fill=255)
    road_mask = road_mask.filter(ImageFilter.GaussianBlur(0.45 * HIRES_SCALE))
    canvas.alpha_composite(mask_to_image(road_surface_fill(road_tile), road_mask))

    highlight_mask = Image.new("L", hi_size, 0)
    highlight_draw = ImageDraw.Draw(highlight_mask)
    highlight_draw.line(hi_points, fill=150, width=4 * HIRES_SCALE, joint="curve")
    highlight_mask = highlight_mask.filter(ImageFilter.GaussianBlur(0.6 * HIRES_SCALE))
    canvas.alpha_composite(mask_to_image(Image.new("RGBA", hi_size, (255, 245, 195, 48)), highlight_mask))


def has_orthogonal_path_neighbor(path_grid: list[list[bool]], x: int, y: int) -> bool:
    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        nx, ny = x + dx, y + dy
        if 0 <= nx < GRID_SIZE and 0 <= ny < GRID_SIZE and path_grid[ny][nx]:
            return True
    return False


def flood_fill_nonpath(start: tuple[int, int], path_grid: list[list[bool]], visited: list[list[bool]]) -> list[tuple[int, int]]:
    region: list[tuple[int, int]] = []
    stack = [start]
    while stack:
        x, y = stack.pop()
        if not (0 <= x < GRID_SIZE and 0 <= y < GRID_SIZE):
            continue
        if visited[y][x] or path_grid[y][x]:
            continue
        visited[y][x] = True
        region.append((x, y))
        stack.extend(((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)))
    return region


def compute_regions(path_grid: list[list[bool]]) -> tuple[list[list[int]], list[int]]:
    visited = [[False] * GRID_SIZE for _ in range(GRID_SIZE)]
    region_id_map = [[-1] * GRID_SIZE for _ in range(GRID_SIZE)]
    region_sizes: list[int] = []

    for y in range(GRID_SIZE):
        for x in range(GRID_SIZE):
            if visited[y][x] or path_grid[y][x]:
                continue
            cells = flood_fill_nonpath((x, y), path_grid, visited)
            rid = len(region_sizes)
            region_sizes.append(len(cells))
            for rx, ry in cells:
                region_id_map[ry][rx] = rid

    return region_id_map, region_sizes


def flood_fill_class(start: tuple[int, int], target: str, classes: list[list[str]], visited: list[list[bool]]) -> list[tuple[int, int]]:
    blob: list[tuple[int, int]] = []
    stack = [start]
    while stack:
        x, y = stack.pop()
        if not (0 <= x < GRID_SIZE and 0 <= y < GRID_SIZE):
            continue
        if visited[y][x] or classes[y][x] != target:
            continue
        visited[y][x] = True
        blob.append((x, y))
        stack.extend(((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)))
    return blob


def refine_thin_blobs(classes: list[list[str]], target: str) -> list[int]:
    """Reclassify small connected blobs of `target` cells as pocket/dead_zone.

    Used to demote tight interior areas that connect to a larger region only via
    margin/edge cells — geographically connected but functionally a pocket.
    """
    visited = [[False] * GRID_SIZE for _ in range(GRID_SIZE)]
    blob_sizes: list[int] = []
    for y in range(GRID_SIZE):
        for x in range(GRID_SIZE):
            if visited[y][x] or classes[y][x] != target:
                continue
            blob = flood_fill_class((x, y), target, classes, visited)
            size = len(blob)
            blob_sizes.append(size)
            if size <= POCKET_MAX:
                label = "pocket"
            elif size <= DEAD_ZONE_MAX:
                label = "dead_zone"
            else:
                continue
            for bx, by in blob:
                classes[by][bx] = label
    return blob_sizes


def classify_cells(path_grid: list[list[bool]]) -> tuple[list[list[str]], list[int], list[int]]:
    region_id_map, region_sizes = compute_regions(path_grid)
    classes: list[list[str | None]] = [[None] * GRID_SIZE for _ in range(GRID_SIZE)]

    for y in range(GRID_SIZE):
        for x in range(GRID_SIZE):
            if path_grid[y][x]:
                classes[y][x] = "path"
                continue

            size = region_sizes[region_id_map[y][x]]
            if size <= POCKET_MAX:
                classes[y][x] = "pocket"
            elif size <= DEAD_ZONE_MAX:
                classes[y][x] = "dead_zone"
            elif (x < CORNER_BAND or x >= GRID_SIZE - CORNER_BAND) and \
                 (y < CORNER_BAND or y >= GRID_SIZE - CORNER_BAND):
                classes[y][x] = "corner"
            elif x == 0 or y == 0 or x == GRID_SIZE - 1 or y == GRID_SIZE - 1:
                classes[y][x] = "edge"
            elif has_orthogonal_path_neighbor(path_grid, x, y):
                classes[y][x] = "path_margin"
            else:
                classes[y][x] = "buildable_core"

    core_blob_sizes = refine_thin_blobs(classes, "buildable_core")  # type: ignore[arg-type]
    return classes, region_sizes, core_blob_sizes  # type: ignore[return-value]


def class_counts(classes: list[list[str]]) -> dict[str, int]:
    counts = {name: 0 for name in CLASS_ORDER}
    for row in classes:
        for value in row:
            counts[value] += 1
    return counts


def render_class_layer(classes: list[list[str]]) -> Image.Image:
    layer = Image.new("RGBA", (MAP_SIZE, MAP_SIZE), (0, 0, 0, 0))
    draw = ImageDraw.Draw(layer)
    for y in range(GRID_SIZE):
        for x in range(GRID_SIZE):
            color = CLASS_COLORS[classes[y][x]]
            draw.rectangle(
                (x * TILE_SIZE, y * TILE_SIZE,
                 x * TILE_SIZE + TILE_SIZE - 1, y * TILE_SIZE + TILE_SIZE - 1),
                fill=color,
                outline=(20, 20, 20, 110),
                width=1,
            )
    return layer


def render_legend(counts: dict[str, int]) -> Image.Image:
    swatch = 14
    line_h = 18
    width = 168
    height = line_h * len(CLASS_ORDER) + 12
    legend = Image.new("RGBA", (width, height), (24, 24, 28, 230))
    draw = ImageDraw.Draw(legend)
    for index, name in enumerate(CLASS_ORDER):
        y = 6 + index * line_h
        color = CLASS_COLORS[name]
        draw.rectangle((8, y, 8 + swatch, y + swatch), fill=color, outline=(255, 255, 255, 180))
        draw.text((8 + swatch + 6, y + 1), f"{name} ({counts[name]})", fill=(235, 235, 235, 255))
    return legend


def compose_with_legend(base: Image.Image, legend: Image.Image) -> Image.Image:
    gap = 8
    width = base.width + gap + legend.width
    height = max(base.height, legend.height)
    canvas = Image.new("RGBA", (width, height), (18, 18, 22, 255))
    canvas.alpha_composite(base, (0, (height - base.height) // 2))
    canvas.alpha_composite(legend, (base.width + gap, (height - legend.height) // 2))
    return canvas


def summarize_regions(region_sizes: list[int]) -> str:
    if not region_sizes:
        return "regions=0"
    big = sum(1 for size in region_sizes if size > DEAD_ZONE_MAX)
    dead = sum(1 for size in region_sizes if POCKET_MAX < size <= DEAD_ZONE_MAX)
    pockets = sum(1 for size in region_sizes if size <= POCKET_MAX)
    sizes = ",".join(str(size) for size in sorted(region_sizes, reverse=True))
    return f"regions={len(region_sizes)}[big={big} dead={dead} pocket={pockets}] sizes=[{sizes}]"


def write_debug_overlays(name: str, map_image: Image.Image, classes: list[list[str]]) -> dict[str, int]:
    DEBUG_DIR.mkdir(parents=True, exist_ok=True)
    counts = class_counts(classes)
    class_layer = render_class_layer(classes)
    legend = render_legend(counts)

    solid_bg = Image.new("RGBA", (MAP_SIZE, MAP_SIZE), (32, 32, 36, 255))
    solid = Image.alpha_composite(solid_bg, class_layer)
    compose_with_legend(solid, legend).save(DEBUG_DIR / f"{name}_classes_solid.png")

    overlay = Image.alpha_composite(map_image.copy(), class_layer)
    compose_with_legend(overlay, legend).save(DEBUG_DIR / f"{name}_classes_overlay.png")

    return counts


def render_placements(canvas: Image.Image, placements: list[Placement], theme: dict[str, object]) -> None:
    tail = theme["tail"]
    for p in placements:
        decor = load_tile(tail, p.tile_id)
        if decor.getbbox() is None:
            continue
        on_edge = (p.x == 0 or p.x == GRID_SIZE - 1
                   or p.y == 0 or p.y == GRID_SIZE - 1)
        effective_scale = min(p.scale, 1.0) if on_edge else p.scale
        size = max(64, round(RENDER_TILE * effective_scale))
        if (size, size) != decor.size:
            decor = decor.resize((size, size), Image.Resampling.LANCZOS)
        if p.alpha < 255:
            decor = set_alpha(decor, p.alpha)

        # Use content bbox (not tile edge) as the anchor reference. Many
        # source tiles place their content offset within the 256x256 frame
        # (e.g., tile 23 in tail_4 has its tower in the top half with 80px
        # empty below). Bottom-aligning the tile edge would push that empty
        # region to the cell bottom and the actual content to the top of
        # the cell — making the prop look "cut" at the canvas edge.
        bbox = decor.getbbox()
        if bbox is None:
            continue
        content_left, _content_top, content_right, content_bottom = bbox
        content_cx = (content_left + content_right) / 2
        cell_cx = p.x * RENDER_TILE + RENDER_TILE / 2
        px = round(cell_cx - content_cx)
        py = (p.y + 1) * RENDER_TILE - content_bottom - 1

        # Safety clamp — content-aware anchoring usually keeps things inside,
        # but tile_height > cell_height combined with low content_bottom can
        # still push the tile origin past the canvas border.
        px = max(0, min(RENDER_MAP - decor.width, px))
        py = max(0, min(RENDER_MAP - decor.height, py))
        canvas.alpha_composite(decor, (px, py))


def render_terrain_tints(canvas: Image.Image, classes: list[list[str]], profile: dict) -> None:
    tints = profile.get("terrain_tints") or {}
    if not tints:
        return

    for class_name, color in tints.items():
        rgb = color[:3]
        target_alpha = color[3]

        mask = Image.new("L", (RENDER_MAP, RENDER_MAP), 0)
        mask_draw = ImageDraw.Draw(mask)
        has_cells = False
        for y in range(GRID_SIZE):
            for x in range(GRID_SIZE):
                if classes[y][x] != class_name:
                    continue
                has_cells = True
                mask_draw.rectangle(
                    (x * RENDER_TILE, y * RENDER_TILE,
                     (x + 1) * RENDER_TILE - 1, (y + 1) * RENDER_TILE - 1),
                    fill=255,
                )
        if not has_cells:
            continue

        soft = mask.filter(ImageFilter.GaussianBlur(12 * HIRES_SCALE))
        scaled = soft.point(lambda v: v * target_alpha // 255)

        tint = Image.new("RGBA", (RENDER_MAP, RENDER_MAP), rgb + (0,))
        tint.putalpha(scaled)
        canvas.alpha_composite(tint)


def render_grain(canvas: Image.Image, seed: str) -> None:
    grain = Image.new("RGBA", (RENDER_MAP, RENDER_MAP), (0, 0, 0, 0))
    grain_draw = ImageDraw.Draw(grain)
    rng = random.Random(seed)
    count = 90 * HIRES_SCALE * HIRES_SCALE
    for _ in range(count):
        x = rng.randrange(RENDER_MAP)
        y = rng.randrange(RENDER_MAP)
        radius = rng.randrange(1 * HIRES_SCALE, 3 * HIRES_SCALE)
        shade = rng.choice(((255, 255, 255, 10), (0, 0, 0, 8)))
        grain_draw.ellipse((x - radius, y - radius, x + radius, y + radius), fill=shade)
    canvas.alpha_composite(grain.filter(ImageFilter.GaussianBlur(0.6 * HIRES_SCALE)))


def identify_zones(classes: list[list[str]], decor_classes: tuple[str, ...] = DECOR_CLASSES) -> list[Zone]:
    visited = [[False] * GRID_SIZE for _ in range(GRID_SIZE)]
    zones: list[Zone] = []
    for y in range(GRID_SIZE):
        for x in range(GRID_SIZE):
            cls = classes[y][x]
            if cls not in decor_classes or visited[y][x]:
                continue
            cells = flood_fill_class((x, y), cls, classes, visited)
            xs = [cx for cx, _ in cells]
            ys = [cy for _, cy in cells]
            bbox = (min(xs), min(ys), max(xs), max(ys))
            zones.append(Zone(len(zones), cls, tuple(cells), bbox))
    return zones


def cluster_target(cell_count: int, density: float, power: float = DENSITY_POWER) -> int:
    if cell_count <= 0:
        return 0
    raw = density * (cell_count ** power)
    return max(1, min(cell_count, int(round(raw))))


def bucket_jitter_pick(cells: list[tuple[int, int]], target: int, rng: random.Random) -> list[tuple[int, int]]:
    n = len(cells)
    if target >= n:
        return list(cells)
    step = n / target
    chosen: list[tuple[int, int]] = []
    for i in range(target):
        start = int(round(i * step))
        end = int(round((i + 1) * step))
        end = max(start + 1, min(n, end))
        chosen.append(rng.choice(cells[start:end]))
    return chosen


def resolve_pool(pool, use_anchor: bool = True) -> tuple[tuple[int, ...], tuple[int, ...]]:
    """Returns (anchor_tiles, filler_tiles).

    Flat tuple/list = same for both. When use_anchor is False, anchor and
    filler are combined (deduped, order preserved) and returned as the
    filler-only side — the planner then skips anchor-at-centroid selection.
    """
    if isinstance(pool, dict):
        anchor = tuple(pool.get("anchor") or pool.get("filler") or ())
        filler = tuple(pool.get("filler") or pool.get("anchor") or ())
    else:
        flat = tuple(pool)
        anchor, filler = flat, flat

    if not use_anchor:
        combined = tuple(dict.fromkeys(anchor + filler))
        return (), combined
    return anchor, filler


def zone_centroid(cells: tuple[tuple[int, int], ...]) -> tuple[float, float]:
    n = len(cells)
    return (sum(c[0] for c in cells) / n, sum(c[1] for c in cells) / n)


def index_nearest_to(cells: list[tuple[int, int]], centroid: tuple[float, float]) -> int:
    best_i = 0
    best_d = float("inf")
    cx0, cy0 = centroid
    for i, (cx, cy) in enumerate(cells):
        d = (cx - cx0) ** 2 + (cy - cy0) ** 2
        if d < best_d:
            best_d = d
            best_i = i
    return best_i


def plan_section(zones: list[Zone], rules: dict, pools: dict, seed_prefix: str,
                  kind: str, default_alpha: int, use_anchor: bool = True) -> list[Placement]:
    placements: list[Placement] = []
    for zone in zones:
        rule = rules.get(zone.class_name)
        if not rule:
            continue
        pool = pools.get(rule["category"])
        if not pool:
            continue

        anchor_tiles, filler_tiles = resolve_pool(pool, use_anchor=use_anchor)
        if not anchor_tiles and not filler_tiles:
            continue

        density = rule["density"]
        scale_lo, scale_hi = rule["scale"]
        alpha = rule.get("alpha", default_alpha)
        if rule.get("fill"):
            target = len(zone.cells)
        else:
            target = cluster_target(len(zone.cells), density)
            max_cap = rule.get("max")
            if max_cap is not None:
                target = min(target, max_cap)

        sorted_cells = sorted(zone.cells, key=lambda c: (c[1], c[0]))
        stride_rng = random.Random(f"{seed_prefix}-{zone.zone_id}-stride")
        chosen = bucket_jitter_pick(sorted_cells, target, stride_rng)

        centroid = zone_centroid(zone.cells)
        anchor_idx = index_nearest_to(chosen, centroid) if anchor_tiles else -1

        for i, (cx, cy) in enumerate(chosen):
            tiles = anchor_tiles if i == anchor_idx and anchor_tiles else (filler_tiles or anchor_tiles)
            local_rng = random.Random(f"{seed_prefix}-{zone.zone_id}-{cx}-{cy}")
            tile_id = local_rng.choice(tiles)
            scale = local_rng.uniform(scale_lo, scale_hi)
            placements.append(Placement(tile_id, cx, cy, scale, rule["category"], zone.zone_id, kind, alpha))

    return placements


def plan_decorations(zones: list[Zone], profile: dict, seed: str) -> list[Placement]:
    pools = profile["category_pools"]
    placements: list[Placement] = []
    placements.extend(plan_section(zones, profile.get("backdrops", {}), pools,
                                    f"{seed}-bg", kind="backdrop", default_alpha=180,
                                    use_anchor=False))
    placements.extend(plan_section(zones, profile.get("rules", {}), pools,
                                    f"{seed}-fg", kind="decor", default_alpha=255,
                                    use_anchor=True))
    return placements


def validate_placements(placements: list[Placement], classes: list[list[str]],
                         forbidden: tuple[str, ...] = FORBIDDEN_FOR_PROPS) -> list[str]:
    errors: list[str] = []
    for p in placements:
        cls = classes[p.y][p.x]
        if cls in forbidden:
            errors.append(f"placement(tile={p.tile_id} cell=({p.x},{p.y}) zone={p.zone_id}) on forbidden class '{cls}'")
    return errors


def render_plan_layer(zones: list[Zone], placements: list[Placement]) -> Image.Image:
    layer = Image.new("RGBA", (MAP_SIZE, MAP_SIZE), (0, 0, 0, 0))
    draw = ImageDraw.Draw(layer)

    for zone in zones:
        color = ZONE_PALETTE[zone.zone_id % len(ZONE_PALETTE)]
        fill = (*color, 70)
        outline = (*color, 230)
        for cx, cy in zone.cells:
            x0 = cx * TILE_SIZE
            y0 = cy * TILE_SIZE
            x1 = x0 + TILE_SIZE - 1
            y1 = y0 + TILE_SIZE - 1
            draw.rectangle((x0, y0, x1, y1), fill=fill, outline=outline, width=1)

    for p in placements:
        cx_px = p.x * TILE_SIZE + TILE_SIZE // 2
        cy_px = p.y * TILE_SIZE + TILE_SIZE // 2
        radius = 8
        color = ZONE_PALETTE[p.zone_id % len(ZONE_PALETTE)]
        draw.ellipse(
            (cx_px - radius, cy_px - radius, cx_px + radius, cy_px + radius),
            fill=(*color, 235),
            outline=(20, 20, 20, 255),
            width=1,
        )
        draw.text((cx_px - 8, cy_px - 5), str(p.tile_id), fill=(20, 20, 20, 255))

    return layer


def render_text_legend(lines: list[str]) -> Image.Image:
    line_h = 16
    width = 180
    height = line_h * len(lines) + 12
    legend = Image.new("RGBA", (width, height), (24, 24, 28, 230))
    draw = ImageDraw.Draw(legend)
    for index, text in enumerate(lines):
        y = 6 + index * line_h
        draw.text((10, y), text, fill=(235, 235, 235, 255))
    return legend


def write_plan_overlay(name: str, map_image: Image.Image, classes: list[list[str]],
                        zones: list[Zone], placements: list[Placement], errors: list[str]) -> dict:
    DEBUG_DIR.mkdir(parents=True, exist_ok=True)

    plan_layer = render_plan_layer(zones, placements)

    class_layer = render_class_layer(classes)
    faint = class_layer.copy()
    faint.putalpha(faint.getchannel("A").point(lambda v: v * 70 // 255))

    solid_bg = Image.new("RGBA", (MAP_SIZE, MAP_SIZE), (32, 32, 36, 255))
    composed = Image.alpha_composite(solid_bg, faint)
    composed = Image.alpha_composite(composed, plan_layer)

    cat_counts = Counter(p.category for p in placements)
    zone_counts = Counter(z.class_name for z in zones)
    lines = [
        f"zones={len(zones)}",
        *(f"  {cls}: {n}" for cls, n in sorted(zone_counts.items())),
        f"placements={len(placements)}",
        *(f"  {cat}: {n}" for cat, n in sorted(cat_counts.items())),
        f"errors={len(errors)}",
    ]
    legend = render_text_legend(lines)
    compose_with_legend(composed, legend).save(DEBUG_DIR / f"{name}_plan.png")

    return {"zones": len(zones), "placements": len(placements),
            "categories": dict(cat_counts), "errors": len(errors)}


def build_map(name: str) -> None:
    theme = THEMES[name]
    profile = BIOME_PROFILES[name]
    tail = theme["tail"]
    tint_color = theme["tint"][:3]
    brightness = theme["tint"][3]

    map_dir = DEST / name
    read_collision_grid(map_dir)
    path_points = read_path_points(map_dir)
    path_grid = build_path_grid(path_points)

    classes, region_sizes, core_blob_sizes = classify_cells(path_grid)
    zones = identify_zones(classes)
    placements = plan_decorations(zones, profile, seed=name)
    errors = validate_placements(placements, classes)
    valid = [p for p in placements if classes[p.y][p.x] not in FORBIDDEN_FOR_PROPS]
    backdrop_layer = [p for p in valid if p.kind == "backdrop"]
    decor_layer = [p for p in valid if p.kind == "decor"]

    base = tinted(load_tile(tail, theme["base"]), tint_color, brightness)
    road_tint = theme["road_tint"][:3]
    road_brightness = theme["road_tint"][3]
    road = tinted(load_tile(tail, theme["road"]), road_tint, road_brightness)
    canvas = Image.new("RGBA", (RENDER_MAP, RENDER_MAP), (0, 0, 0, 0))

    for y in range(GRID_SIZE):
        for x in range(GRID_SIZE):
            canvas.alpha_composite(base, (x * RENDER_TILE, y * RENDER_TILE))

    render_terrain_tints(canvas, classes, profile)
    render_placements(canvas, backdrop_layer, theme)
    draw_road(canvas, path_points, road)
    render_placements(canvas, decor_layer, theme)
    render_grain(canvas, str(theme["tail"]))

    # Single LANCZOS downsize from RENDER_MAP → MAP_SIZE: all native detail
    # composes at hi-res, then gets one clean anti-aliased pass to PSP size.
    final = canvas.resize((MAP_SIZE, MAP_SIZE), Image.Resampling.LANCZOS)
    final.save(map_dir / f"{name}.png")
    final.resize((100, 100), Image.Resampling.LANCZOS).convert("RGB").save(map_dir / "mini.png")

    counts = write_debug_overlays(name, final, classes)
    summary = " ".join(f"{cls}={counts[cls]}" for cls in CLASS_ORDER)
    core_sizes = ",".join(str(size) for size in sorted(core_blob_sizes, reverse=True))
    print(f"[{name}] {summary} | {summarize_regions(region_sizes)} core_blobs=[{core_sizes}]")

    plan_info = write_plan_overlay(name, final, classes, zones, placements, errors)
    cat_str = " ".join(f"{cat}={n}" for cat, n in sorted(plan_info["categories"].items()))
    print(f"[{name}] plan: zones={plan_info['zones']} placements={plan_info['placements']} "
          f"[{cat_str}] errors={plan_info['errors']}")
    for err in errors:
        print(f"  ! {err}")


def main() -> None:
    for name in THEMES:
        build_map(name)


if __name__ == "__main__":
    main()
