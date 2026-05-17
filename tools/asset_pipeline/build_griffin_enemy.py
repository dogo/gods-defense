#!/usr/bin/env python3
from __future__ import annotations

import sys

sys.dont_write_bytecode = True

from enemy_assets import ROOT, build_enemy_sheet


SOURCE = ROOT / "tower-defense-2d-game-kit-v1.1" / "tower-defense-monster-2d-sprites" / "PNG" / "10"
DEST = ROOT / "PSP Project" / "Res" / "enemies" / "griffin" / "griffin.png"


def main() -> None:
    build_enemy_sheet(SOURCE, DEST, action="WALK", max_size=(28, 24), bottom_align=False)


if __name__ == "__main__":
    main()
