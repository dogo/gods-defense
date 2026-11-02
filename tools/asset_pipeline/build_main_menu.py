#!/usr/bin/env python3
"""Build the main menu button sheet from the kit's blank wood/metal button."""
from PIL import Image, ImageEnhance

from build_ingame_ui import DEST, GUI, trim_alpha


def build_buttons() -> Image.Image:
    source = trim_alpha(Image.open(GUI / "difficulty" / "button_empty_2.png"))
    # Keep the metal corners square while fitting six rows on the PSP screen.
    src_x = (0, 36, source.width - 36, source.width)
    src_y = (0, 36, source.height - 36, source.height)
    dst_x = (0, 7, 185, 192)
    dst_y = (0, 7, 21, 28)
    button = Image.new("RGBA", (192, 28))
    for row in range(3):
        for col in range(3):
            piece = source.crop((src_x[col], src_y[row], src_x[col + 1], src_y[row + 1]))
            piece = piece.resize((dst_x[col + 1] - dst_x[col], dst_y[row + 1] - dst_y[row]), Image.Resampling.LANCZOS)
            button.alpha_composite(piece, (dst_x[col], dst_y[row]))

    selected = button.copy()
    pixels = selected.load()
    for y in range(selected.height):
        for x in range(selected.width):
            r, g, b, a = pixels[x, y]
            if max(r, g, b) - min(r, g, b) < 35:
                pixels[x, y] = (r, round(g * 0.83), round(b * 0.45), a)
    sheet = Image.new("RGBA", (384, 28))
    sheet.alpha_composite(ImageEnhance.Brightness(button).enhance(0.72), (0, 0))
    sheet.alpha_composite(selected, (192, 0))
    assert sheet.size == (384, 28) and sheet.getextrema()[3][0] == 0
    assert sheet.crop((0, 0, 192, 28)).tobytes() != sheet.crop((192, 0, 384, 28)).tobytes()
    return sheet


def main() -> None:
    output = DEST / "menu"
    output.mkdir(parents=True, exist_ok=True)
    sheet = build_buttons()
    sheet.save(output / "buttons.png")
    with Image.open(output / "buttons.png") as saved:
        assert saved.mode == "RGBA" and saved.tobytes() == sheet.tobytes()
    print("menu/buttons.png: 384x28, two 192x28 button states")


if __name__ == "__main__":
    main()
