#!/usr/bin/env python3
"""Render preview sheets of all tiles in each tail of the Tiled tileset.

Each tile is drawn at 96x96 with its tile_id label. Output goes to
tools/asset_pipeline/_debug/{tail}_sheet.png. Use to visually identify
atomic single-object tiles vs composite multi-object tiles.
"""
from __future__ import annotations

from pathlib import Path

from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
TILED = ROOT / "tower-defense-2d-game-kit-v1.1" / "td-tilesets" / "version-for-the-program-Tiled" / "PNG"
DEBUG_DIR = ROOT / "tools" / "asset_pipeline" / "_debug"

TILE_PX = 128
LABEL_H = 22
COLS = 6
PAD = 8
CELL_W = TILE_PX + PAD
CELL_H = TILE_PX + LABEL_H + PAD

TAILS = ("tail_1", "tail_2", "tail_4", "tail_7")


def render_sheet(tail: str) -> None:
    tail_dir = TILED / tail
    tile_files = sorted(tail_dir.glob("*.png"), key=lambda p: int(p.stem))
    if not tile_files:
        print(f"[{tail}] no tiles found")
        return

    rows = (len(tile_files) + COLS - 1) // COLS
    width = COLS * CELL_W + PAD
    height = rows * CELL_H + PAD + 24
    sheet = Image.new("RGBA", (width, height), (28, 28, 32, 255))
    draw = ImageDraw.Draw(sheet)
    draw.text((PAD, 4), f"{tail} ({len(tile_files)} tiles, source 256px → preview {TILE_PX}px)",
              fill=(235, 235, 235, 255))

    for idx, tile_path in enumerate(tile_files):
        col = idx % COLS
        row = idx // COLS
        x0 = PAD + col * CELL_W
        y0 = 24 + PAD + row * CELL_H

        img = Image.open(tile_path).convert("RGBA")
        img.thumbnail((TILE_PX, TILE_PX), Image.Resampling.LANCZOS)

        draw.rectangle(
            (x0, y0, x0 + TILE_PX - 1, y0 + TILE_PX - 1),
            fill=(45, 45, 50, 255),
            outline=(80, 80, 90, 255),
        )
        ox = x0 + (TILE_PX - img.width) // 2
        oy = y0 + (TILE_PX - img.height) // 2
        sheet.alpha_composite(img, (ox, oy))

        label = tile_path.stem
        label_y = y0 + TILE_PX + 2
        draw.text((x0 + 4, label_y), label, fill=(220, 220, 220, 255))

    DEBUG_DIR.mkdir(parents=True, exist_ok=True)
    out = DEBUG_DIR / f"{tail}_sheet.png"
    sheet.save(out)
    print(f"[{tail}] sheet → {out.relative_to(ROOT)} ({len(tile_files)} tiles, {COLS}x{rows})")


def main() -> None:
    for tail in TAILS:
        render_sheet(tail)


if __name__ == "__main__":
    main()
