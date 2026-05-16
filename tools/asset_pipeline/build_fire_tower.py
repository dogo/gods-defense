#!/usr/bin/env python3
from __future__ import annotations

import sys
from pathlib import Path

from PIL import Image

sys.dont_write_bytecode = True

from build_arrow_tower import fit_on_canvas, make_sheet, resize_gui_icon


ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "tower-defense-2d-game-kit-v1.1" / "magic-tower-game-assets" / "PNG"
GUI_INTERFACE = ROOT / "tower-defense-2d-game-kit-v1.1" / "td-gui" / "PNG" / "interface_game"
DEST = ROOT / "PSP Project" / "Res" / "towers" / "fire"


def build_tower() -> None:
    source = Image.open(SOURCE / "4.png")
    frame = fit_on_canvas(source, (32, 32), (31, 31), bottom_align=True)
    frames = [frame.copy() for _ in range(4)]
    make_sheet(frames).save(DEST / "tower.png")

    resize_gui_icon(Image.open(GUI_INTERFACE / "ico_1.png")).save(DEST / "icon.png")


def build_projectile() -> None:
    source = Image.open(SOURCE / "14.png")
    sizes = [(12, 12), (14, 14), (16, 16), (14, 14)]
    frames = [
        fit_on_canvas(source.copy(), (32, 32), size)
        for size in sizes
    ]
    make_sheet(frames).save(DEST / "ST_Fire.png")


def main() -> None:
    build_tower()
    build_projectile()


if __name__ == "__main__":
    main()
