#!/usr/bin/env python3
"""Build shared control hints in the menu's wood/gold style."""
from PIL import Image, ImageDraw

from build_ingame_ui import DEST, GUI, trim_alpha


def build_icon(kind: str) -> Image.Image:
    frame = trim_alpha(Image.open(GUI / "levels" / "btton_empty.png"))
    frame = frame.resize((176, 176), Image.Resampling.LANCZOS)
    pixels = frame.load()
    metal = Image.new("L", frame.size)
    for y in range(frame.height):
        for x in range(frame.width):
            r, g, b, a = pixels[x, y]
            if min(r, g, b) > 100 and max(r, g, b) - min(r, g, b) < 35 and a > 240:
                metal.putpixel((x, y), 255)
            if max(r, g, b) - min(r, g, b) < 35:
                pixels[x, y] = (r, round(g * 0.83), round(b * 0.45), a)
    # Center on the metal rim, excluding the source's bottom/right shadow.
    bounds = metal.getbbox()
    assert bounds is not None
    offset = ((256 - bounds[0] - bounds[2]) // 2, (256 - bounds[1] - bounds[3]) // 2)
    canvas = Image.new("RGBA", (256, 256))
    canvas.alpha_composite(frame, offset)
    draw = ImageDraw.Draw(canvas)
    gold = (255, 232, 163, 255)
    cx = offset[0] + (bounds[0] + bounds[2] - 1) / 2
    cy = offset[1] + (bounds[1] + bounds[3] - 1) / 2
    if kind == "cross":
        draw.line((cx - 40, cy - 40, cx + 40, cy + 40), fill=gold, width=16)
        draw.line((cx - 40, cy + 40, cx + 40, cy - 40), fill=gold, width=16)
    elif kind == "circle":
        draw.ellipse((cx - 48, cy - 48, cx + 48, cy + 48), outline=gold, width=16)
    elif kind == "square":
        draw.rectangle((cx - 44, cy - 44, cx + 44, cy + 44), outline=gold, width=16)
    elif kind == "triangle":
        draw.polygon(((cx, cy - 56), (cx + 50, cy + 32), (cx - 50, cy + 32)), outline=gold, width=16)
    else:
        raise ValueError(kind)
    return canvas.resize((64, 64), Image.Resampling.LANCZOS)


def main() -> None:
    icons = [build_icon(kind) for kind in ("cross", "circle", "square", "triangle")]
    assert len({icon.tobytes() for icon in icons}) == 4
    for name, icon in zip(("x.png", "circle.png", "square.png", "triangle.png"), icons):
        assert icon.size == (64, 64) and icon.mode == "RGBA"
        assert icon.getpixel((0, 0))[3] == 0 and icon.getpixel((32, 32))[3] == 255
        icon.save(DEST / name)
        with Image.open(DEST / name) as saved:
            assert saved.tobytes() == icon.tobytes()
        print(f"{name}: 64x64 RGBA, shared control hint")


if __name__ == "__main__":
    main()
