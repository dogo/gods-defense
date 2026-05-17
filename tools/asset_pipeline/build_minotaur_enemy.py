#!/usr/bin/env python3
from __future__ import annotations

import sys

sys.dont_write_bytecode = True

from enemy_assets import ROOT, build_enemy_sheet


SOURCE = ROOT / "tower-defense-2d-game-kit-v1.1" / "tower-defense-monster-2d-sprites" / "PNG" / "7"
DEST = ROOT / "PSP Project" / "Res" / "enemies" / "minotaur" / "minotaur.png"


def main() -> None:
    build_enemy_sheet(SOURCE, DEST, action="RUN", max_size=(29, 29))


if __name__ == "__main__":
    main()
