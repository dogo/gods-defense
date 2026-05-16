#!/usr/bin/env python3
from pathlib import Path
import re

from PIL import Image, ImageFilter


ROOT = Path(__file__).resolve().parents[1]
KIT_ROOT = ROOT / "tower-defense-2d-game-kit-v1.1"
ENEMY_ROOT = ROOT / "PSP Project" / "Res" / "enemies"
FRAME_SIZE = 32
FRAME_COUNT = 12


ENEMIES = {
    "cerberus": {
        "source": ("monster-enemy-game-sprites", "4"),
        "file": "cerberus.png",
        "frame_time": 85,
    },
    "cyclops": {
        "source": ("monster-character-2d-sprites", "9"),
        "file": "cyclops.png",
        "frame_time": 110,
    },
    "griffin": {
        "source": ("tower-defense-monster-2d-sprites", "10"),
        "file": "griffin.png",
        "frame_time": 75,
    },
    "hydra": {
        "source": ("2d-monster-sprites", "3"),
        "file": "hydra.png",
        "frame_time": 95,
    },
    "medusa": {
        "source": ("monster-enemy-game-sprites", "5"),
        "file": "medusa.png",
        "frame_time": 90,
    },
    "minions": {
        "source": ("2d-monster-sprites", "9"),
        "file": "MedusaMinions.png",
        "frame_time": 75,
    },
    "minotaur": {
        "source": ("tower-defense-monster-2d-sprites", "6"),
        "file": "minotaur.png",
        "frame_time": 85,
    },
}


def frame_number(path: Path) -> int:
    match = re.search(r"_(\d+)\.png$", path.name)
    return int(match.group(1)) if match else 0


def animation_files(family: str, number: str) -> list[Path]:
    source_dir = KIT_ROOT / family / "PNG" / number
    files = sorted(
        [path for path in source_dir.glob("*.png") if "_walk_" in path.name.lower()],
        key=frame_number,
    )
    if files:
        return files

    files = sorted(
        [path for path in source_dir.glob("*.png") if "_run_" in path.name.lower()],
        key=frame_number,
    )
    if files:
        return files

    raise FileNotFoundError(f"No walk/run frames found in {source_dir}")


def selected_frames(files: list[Path]) -> list[Image.Image]:
    indexes = [
        round(index * (len(files) - 1) / (FRAME_COUNT - 1))
        for index in range(FRAME_COUNT)
    ]
    return [Image.open(files[index]).convert("RGBA") for index in indexes]


def union_alpha_bounds(frames: list[Image.Image]) -> tuple[int, int, int, int]:
    boxes = [frame.getbbox() for frame in frames if frame.getbbox()]
    if not boxes:
        raise ValueError("Source frames are empty")

    return (
        min(box[0] for box in boxes),
        min(box[1] for box in boxes),
        max(box[2] for box in boxes),
        max(box[3] for box in boxes),
    )


def draw_sheet(frames: list[Image.Image]) -> Image.Image:
    bounds = union_alpha_bounds(frames)
    width = bounds[2] - bounds[0]
    height = bounds[3] - bounds[1]
    scale = min(29 / width, 29 / height)
    target_width = max(1, round(width * scale))
    target_height = max(1, round(height * scale))

    sheet = Image.new("RGBA", (FRAME_SIZE * FRAME_COUNT, FRAME_SIZE), (0, 0, 0, 0))
    for index, frame in enumerate(frames):
        small = frame.crop(bounds).resize(
            (target_width, target_height), Image.Resampling.LANCZOS
        )
        alpha = small.getchannel("A")
        outline_alpha = alpha.filter(ImageFilter.MaxFilter(3))
        outline = Image.new("RGBA", small.size, (9, 13, 12, 210))
        outline.putalpha(outline_alpha)

        x = index * FRAME_SIZE + (FRAME_SIZE - target_width) // 2
        y = (FRAME_SIZE - target_height) // 2 + 1
        sheet.alpha_composite(outline, (x, y))
        sheet.alpha_composite(small, (x, y))

    return sheet


def update_enemy_xml(enemy: str, image_file: str, frame_time: int) -> None:
    xml_path = ENEMY_ROOT / enemy / "enemy.xml"
    text = xml_path.read_text()
    pattern = re.compile(
        r'(<EnemyImg\s+File="'
        + re.escape(image_file)
        + r'"\s+Frames=")\d+(")(?:\s+FrameTime="\d+")?'
    )
    text, replacements = pattern.subn(
        rf'\g<1>{FRAME_COUNT}\2 FrameTime="{frame_time}"', text
    )
    if replacements != 1:
        raise ValueError(f"Could not update EnemyImg in {xml_path}")
    xml_path.write_text(text)


def main() -> None:
    if not KIT_ROOT.exists():
        raise FileNotFoundError(f"Missing kit folder: {KIT_ROOT}")

    for enemy, config in ENEMIES.items():
        family, number = config["source"]
        frames = selected_frames(animation_files(family, number))
        sheet = draw_sheet(frames)
        output = ENEMY_ROOT / enemy / config["file"]
        sheet.save(output)
        update_enemy_xml(enemy, config["file"], config["frame_time"])
        print(f"{enemy}: {output.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
