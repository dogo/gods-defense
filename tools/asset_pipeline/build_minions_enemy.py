#!/usr/bin/env python3
from __future__ import annotations

import sys

sys.dont_write_bytecode = True

from enemy_assets import ROOT, build_enemy_sheet


SOURCE = ROOT / "tower-defense-2d-game-kit-v1.1" / "2d-monster-sprites" / "PNG" / "1"
DEST = ROOT / "PSP Project" / "Res" / "enemies" / "minions" / "MedusaMinions.png"


def main() -> None:
    build_enemy_sheet(SOURCE, DEST, action="run", max_size=(27, 27))


if __name__ == "__main__":
    main()
