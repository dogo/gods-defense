from __future__ import annotations

from pathlib import Path

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]


def trim_alpha(image: Image.Image) -> Image.Image:
    image = image.convert("RGBA")
    bbox = image.getbbox()
    if bbox is None:
        return image
    return image.crop(bbox)


def fit_on_canvas(
    image: Image.Image,
    size: tuple[int, int] = (32, 32),
    max_size: tuple[int, int] = (29, 29),
    *,
    bottom_align: bool = True,
    offset: tuple[int, int] = (0, 0),
) -> Image.Image:
    image = trim_alpha(image)
    image.thumbnail(max_size, Image.Resampling.LANCZOS)

    canvas = Image.new("RGBA", size, (0, 0, 0, 0))
    x = (size[0] - image.width) // 2 + offset[0]
    if bottom_align:
        y = size[1] - image.height + offset[1]
    else:
        y = (size[1] - image.height) // 2 + offset[1]
    canvas.alpha_composite(image, (x, y))
    return canvas


def frame_paths(source_dir: Path, action: str, count: int = 12) -> list[Path]:
    candidates = sorted(source_dir.glob(f"*_{action}_*.png"))
    if len(candidates) < count:
        candidates = sorted(source_dir.glob(f"*_{action.upper()}_*.png"))
    if len(candidates) < count:
        raise RuntimeError(f"Expected at least {count} {action} frames in {source_dir}")
    return candidates[:count]


def build_enemy_sheet(
    source_dir: Path,
    destination: Path,
    *,
    action: str = "run",
    max_size: tuple[int, int] = (29, 29),
    offset: tuple[int, int] = (0, 0),
) -> None:
    frames = [
        fit_on_canvas(Image.open(path), max_size=max_size, offset=offset)
        for path in frame_paths(source_dir, action)
    ]
    sheet = Image.new("RGBA", (32 * len(frames), 32), (0, 0, 0, 0))
    for index, frame in enumerate(frames):
        sheet.alpha_composite(frame, (index * 32, 0))
    sheet.save(destination)
