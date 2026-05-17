#!/usr/bin/env python3
from __future__ import annotations

import sys

sys.dont_write_bytecode = True

from enemy_assets import ROOT, build_enemy_sheet


SOURCE = ROOT / "tower-defense-2d-game-kit-v1.1" / "monster-character-2d-sprites" / "PNG" / "3"
DEST = ROOT / "PSP Project" / "Res" / "enemies" / "hydra" / "hydra.png"


def main() -> None:
    build_enemy_sheet(SOURCE, DEST, action="RUN", max_size=(30, 30))


if __name__ == "__main__":
    main()
