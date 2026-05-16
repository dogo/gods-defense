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
GUI_UPGRADE = ROOT / "tower-defense-2d-game-kit-v1.1" / "td-gui" / "PNG" / "upgrade"
DEST = ROOT / "PSP Project" / "Res" / "towers" / "ice"


def build_tower() -> None:
    source = Image.open(SOURCE / "8.png")
    frame = fit_on_canvas(source, (32, 32), (31, 31), bottom_align=True)
    frames = [frame.copy() for _ in range(4)]
    make_sheet(frames).save(DEST / "tower.png")

    resize_gui_icon(Image.open(GUI_UPGRADE / "ico_21.png")).save(DEST / "icon.png")


def build_projectile() -> None:
    source = Image.open(SOURCE / "10.png").convert("RGBA")
    source = source.rotate(270, expand=True, resample=Image.Resampling.BICUBIC)
    offsets = [(0, 0), (1, 0), (0, 0), (-1, 0)]
    frames = [
        fit_on_canvas(source.copy(), (32, 32), (22, 12), offset=offset)
        for offset in offsets
    ]
    make_sheet(frames).save(DEST / "ST_Ice.png")


def main() -> None:
    build_tower()
    build_projectile()


if __name__ == "__main__":
    main()
