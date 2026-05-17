#!/usr/bin/env python3
from __future__ import annotations

from pathlib import Path

from PIL import Image
from PIL import ImageDraw


ROOT = Path(__file__).resolve().parents[2]
GUI = ROOT / "tower-defense-2d-game-kit-v1.1" / "td-gui" / "PNG"
DEST = ROOT / "PSP Project" / "Res"


def trim_alpha(image: Image.Image) -> Image.Image:
    image = image.convert("RGBA")
    bbox = image.getbbox()
    if bbox is None:
        return image
    return image.crop(bbox)


def fit(image: Image.Image, max_size: tuple[int, int]) -> Image.Image:
    image = trim_alpha(image)
    image.thumbnail(max_size, Image.Resampling.LANCZOS)
    return image


def paste_center(
    canvas: Image.Image,
    image: Image.Image,
    box: tuple[int, int, int, int],
    *,
    offset: tuple[int, int] = (0, 0),
) -> None:
    image = fit(image, (box[2] - box[0], box[3] - box[1]))
    x = box[0] + ((box[2] - box[0] - image.width) // 2) + offset[0]
    y = box[1] + ((box[3] - box[1] - image.height) // 2) + offset[1]
    canvas.alpha_composite(image, (x, y))


def draw_panel(draw: ImageDraw.ImageDraw, rect: tuple[int, int, int, int]) -> None:
    x0, y0, x1, y1 = rect
    draw.rectangle(rect, fill=(2, 2, 2, 255))
    draw.rectangle(rect, outline=(0, 0, 0, 255))
    draw.rectangle((x0 + 1, y0 + 1, x1 - 1, y1 - 1), outline=(64, 49, 12, 255))
    draw.rectangle((x0 + 2, y0 + 2, x1 - 2, y1 - 2), outline=(159, 128, 35, 255))
    draw.line((x0 + 3, y0 + 3, x1 - 3, y0 + 3), fill=(239, 205, 83, 255))
    draw.line((x0 + 3, y1 - 3, x1 - 3, y1 - 3), fill=(81, 59, 15, 255))


def draw_gem(draw: ImageDraw.ImageDraw, x: int, y: int) -> None:
    draw.rectangle((x, y, x + 3, y + 3), fill=(82, 0, 0, 255))
    draw.rectangle((x + 1, y + 1, x + 2, y + 2), fill=(218, 28, 22, 255))
    draw.point((x + 1, y + 1), fill=(255, 214, 164, 255))


def draw_slot(draw: ImageDraw.ImageDraw, rect: tuple[int, int, int, int]) -> None:
    x0, y0, x1, y1 = rect
    draw.rectangle(rect, fill=(7, 7, 7, 255), outline=(0, 0, 0, 255))
    draw.rectangle((x0 + 1, y0 + 1, x1 - 1, y1 - 1), outline=(48, 40, 18, 255))
    draw.rectangle((x0 + 3, y0 + 3, x1 - 3, y1 - 3), outline=(91, 78, 47, 255))


def build_hud() -> None:
    hud = Image.new("RGBA", (143, 19), (0, 0, 0, 0))
    draw = ImageDraw.Draw(hud)
    draw.rectangle((0, 0, 142, 18), fill=(0, 0, 0, 255))
    draw.rectangle((1, 1, 141, 17), outline=(61, 45, 10, 255))
    draw.rectangle((2, 2, 140, 16), fill=(9, 7, 5, 255), outline=(189, 149, 36, 255))
    draw.line((3, 3, 139, 3), fill=(246, 209, 78, 255))
    draw.line((3, 15, 139, 15), fill=(78, 55, 10, 255))
    draw.line((61, 3, 61, 15), fill=(189, 149, 36, 255))
    draw.line((62, 3, 62, 15), fill=(54, 39, 8, 255))

    crystal = Image.open(GUI / "shop" / "crystal_1.png")
    heart = Image.open(GUI / "interface_game" / "heart.png")
    paste_center(hud, crystal, (6, 4, 22, 15))
    paste_center(hud, heart, (71, 4, 85, 15))
    hud.save(DEST / "hud.png")


def build_sidebar() -> None:
    sidebar = Image.new("RGBA", (48, 272), (0, 0, 0, 255))
    draw = ImageDraw.Draw(sidebar)
    draw_panel(draw, (0, 0, 47, 271))
    draw.rectangle((4, 4, 43, 267), fill=(3, 3, 3, 255))

    for x, y in ((2, 2), (42, 2), (2, 266), (42, 266)):
        draw_gem(draw, x, y)

    for y in (25, 86, 147, 208):
        draw_slot(draw, (4, y, 44, y + 40))
        draw.line((7, y + 43, 41, y + 43), fill=(37, 27, 8, 255))

    sidebar.save(DEST / "sidebar.png")


def build_upgradebar() -> None:
    bar = Image.new("RGBA", (150, 68), (0, 0, 0, 255))
    draw = ImageDraw.Draw(bar)
    draw_panel(draw, (0, 0, 149, 67))
    draw.rectangle((4, 4, 145, 63), fill=(5, 5, 5, 255))
    draw.rectangle((5, 5, 144, 21), fill=(18, 11, 5, 255), outline=(93, 64, 18, 255))

    for x, y in ((2, 2), (144, 2), (2, 62), (144, 62)):
        draw_gem(draw, x, y)

    draw_slot(draw, (24, 24, 64, 64))
    draw_slot(draw, (85, 24, 125, 64))
    bar.save(DEST / "upgradebar.png")


def build_selector() -> None:
    selector = Image.new("RGBA", (38, 38), (0, 0, 0, 0))
    draw = ImageDraw.Draw(selector)
    corner = (235, 201, 62, 255)
    shade = (89, 63, 13, 255)
    metal = (225, 219, 190, 255)

    for x, y, sx, sy in ((0, 0, 1, 1), (37, 0, -1, 1), (0, 37, 1, -1), (37, 37, -1, -1)):
        draw.line((x, y, x + sx * 10, y), fill=shade)
        draw.line((x, y, x, y + sy * 10), fill=shade)
        draw.line((x + sx, y + sy, x + sx * 8, y + sy), fill=corner)
        draw.line((x + sx, y + sy, x + sx, y + sy * 8), fill=corner)
        draw.line((x + sx * 3, y + sy * 3, x + sx * 10, y + sy * 3), fill=metal)
        draw.line((x + sx * 3, y + sy * 3, x + sx * 3, y + sy * 10), fill=metal)
        draw_gem(draw, x + sx * 3 - (3 if sx < 0 else 0), y + sy * 3 - (3 if sy < 0 else 0))

    selector.save(DEST / "selector.png")


def build_command_icon(kind: str, size: tuple[int, int]) -> Image.Image:
    icon = Image.new("RGBA", size, (0, 0, 0, 0))
    inset_x = (size[0] - 32) // 2
    draw = ImageDraw.Draw(icon)
    draw_slot(draw, (inset_x, 0, inset_x + 31, 31))
    draw.rectangle((inset_x + 5, 5, inset_x + 26, 26), fill=(30, 17, 7, 255))

    if kind == "upgrade":
        draw.polygon(((inset_x + 16, 6), (inset_x + 25, 17), (inset_x + 20, 17), (inset_x + 20, 25), (inset_x + 12, 25), (inset_x + 12, 17), (inset_x + 7, 17)), fill=(247, 205, 56, 255))
        draw.line((inset_x + 16, 7, inset_x + 23, 16, inset_x + 19, 16, inset_x + 19, 24), fill=(255, 244, 142, 255))
        draw.line((inset_x + 8, 18, inset_x + 12, 18, inset_x + 12, 25, inset_x + 20, 25), fill=(96, 66, 13, 255))
    else:
        crystal = Image.open(GUI / "shop" / "crystal_1.png")
        paste_center(icon, crystal, (inset_x + 6, 5, inset_x + 25, 24))
        draw.line((inset_x + 8, 26, inset_x + 24, 26), fill=(247, 205, 56, 255))
        draw.line((inset_x + 10, 28, inset_x + 22, 28), fill=(150, 100, 20, 255))

    return icon


def main() -> None:
    build_hud()
    build_sidebar()
    build_upgradebar()
    build_selector()
    build_command_icon("upgrade", (32, 32)).save(DEST / "upgrade.png")
    build_command_icon("sell", (35, 32)).save(DEST / "sell.png")


if __name__ == "__main__":
    main()
