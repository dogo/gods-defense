#!/usr/bin/env python3
from __future__ import annotations

from pathlib import Path

from PIL import Image
from PIL import ImageDraw


ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "tower-defense-2d-game-kit-v1.1" / "archer-tower-game-assets" / "PNG"
GUI_UPGRADE = ROOT / "tower-defense-2d-game-kit-v1.1" / "td-gui" / "PNG" / "upgrade"
DEST = ROOT / "PSP Project" / "Res" / "towers" / "arrow"


def trim_alpha(image: Image.Image) -> Image.Image:
    image = image.convert("RGBA")
    bbox = image.getbbox()
    if bbox is None:
        return image
    return image.crop(bbox)


def fit_on_canvas(
    image: Image.Image,
    size: tuple[int, int],
    max_size: tuple[int, int],
    *,
    bottom_align: bool = False,
    offset: tuple[int, int] = (0, 0),
) -> Image.Image:
    image = trim_alpha(image)
    image.thumbnail(max_size, Image.Resampling.LANCZOS)

    canvas = Image.new("RGBA", size, (0, 0, 0, 0))
    x = (size[0] - image.width) // 2 + offset[0]
    if bottom_align:
        y = size[1] - image.height + offset[1]
    else:
        y = (size[1] - image.height) // 2 + offset[1]
    canvas.alpha_composite(image, (x, y))
    return canvas


def make_sheet(frames: list[Image.Image]) -> Image.Image:
    frame_width = frames[0].width
    frame_height = frames[0].height
    sheet = Image.new("RGBA", (frame_width * len(frames), frame_height), (0, 0, 0, 0))
    for index, frame in enumerate(frames):
        sheet.alpha_composite(frame, (index * frame_width, 0))
    return sheet


def accent_idle_frames(
    frame: Image.Image,
    hues: tuple[tuple[int, int], ...],
    min_saturation: int,
    min_value: int,
    gains: tuple[float, ...] = (1.0, 1.25, 1.5, 1.25),
) -> list[Image.Image]:
    # Idle = pulse only the saturated accent pixels (gems, runes); hue/sat/value use PIL's 0-255 HSV.
    hsv = frame.convert("RGB").convert("HSV").load()
    alpha = frame.getchannel("A").load()
    mask = Image.new("L", frame.size, 0)
    mask_px = mask.load()
    for y in range(frame.height):
        for x in range(frame.width):
            h, s, v = hsv[x, y]
            if alpha[x, y] and s >= min_saturation and v >= min_value and any(lo <= h <= hi for lo, hi in hues):
                mask_px[x, y] = 255

    frames = []
    for gain in gains:
        bright = frame.point(lambda c: min(255, int(c * gain)))
        bright.putalpha(frame.getchannel("A"))
        frames.append(Image.composite(bright, frame, mask))
    return frames


def make_menu_icon(symbol: Image.Image) -> Image.Image:
    icon = Image.new("RGBA", (32, 32), (0, 0, 0, 255))
    draw = ImageDraw.Draw(icon)

    # Match the existing tower icons: dark inset, metal frame, red corner gems.
    draw.rectangle((0, 0, 31, 31), outline=(37, 35, 31, 255))
    draw.rectangle((2, 2, 29, 29), outline=(82, 68, 31, 255))
    draw.rectangle((4, 4, 27, 27), outline=(116, 104, 75, 255))
    draw.rectangle((5, 5, 26, 26), fill=(4, 4, 4, 255))
    for x, y in ((3, 3), (26, 3), (3, 26), (26, 26)):
        draw.rectangle((x, y, x + 2, y + 2), fill=(142, 0, 0, 255))
        draw.point((x + 1, y + 1), fill=(255, 48, 36, 255))

    symbol = trim_alpha(symbol)
    symbol.thumbnail((21, 21), Image.Resampling.LANCZOS)
    icon.alpha_composite(symbol, ((32 - symbol.width) // 2, (32 - symbol.height) // 2 + 1))
    return icon


def resize_gui_icon(image: Image.Image) -> Image.Image:
    canvas = Image.new("RGBA", (32, 32), (0, 0, 0, 255))
    frame = fit_on_canvas(trim_alpha(image), (32, 32), (36, 36))
    canvas.alpha_composite(frame)
    draw = ImageDraw.Draw(canvas)
    draw.rectangle((0, 0, 31, 31), outline=(0, 0, 0, 255))
    return canvas


def build_tower() -> None:
    source = Image.open(SOURCE / "6.png")
    frame = fit_on_canvas(source, (32, 32), (31, 31), bottom_align=True)
    # Wood/thatch tower has no glowing accent to pulse; kept static on purpose.
    frames = [frame.copy() for _ in range(4)]
    make_sheet(frames).save(DEST / "tower.png")

    resize_gui_icon(Image.open(GUI_UPGRADE / "ico_8.png")).save(DEST / "icon.png")


def build_projectile() -> None:
    arrow = Image.open(SOURCE / "35.png").convert("RGBA")
    arrow = arrow.rotate(225, expand=True, resample=Image.Resampling.BICUBIC)
    offsets = [(0, 0), (1, 0), (0, 0), (-1, 0)]
    frames = [
        fit_on_canvas(arrow.copy(), (32, 32), (26, 12), offset=offset)
        for offset in offsets
    ]
    make_sheet(frames).save(DEST / "ST_Arrow.png")


def main() -> None:
    build_tower()
    build_projectile()


if __name__ == "__main__":
    main()
