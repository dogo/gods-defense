#!/usr/bin/env python3
import math
import os

from PIL import Image, ImageDraw, ImageFilter


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RES = os.path.join(ROOT, "PSP Project", "Res", "towers")
SIZE = 32
FRAMES = 4
SCALE = 4
CANVAS = SIZE * SCALE


def c(r, g, b, a=255):
	return (r, g, b, a)


def p(points, ox=0, oy=0):
	return [((x + ox) * SCALE, (y + oy) * SCALE) for x, y in points]


def xy(x, y):
	return (x * SCALE, y * SCALE)


def box(x0, y0, x1, y1):
	return (x0 * SCALE, y0 * SCALE, x1 * SCALE, y1 * SCALE)


def line(draw, points, fill, width=1):
	draw.line([xy(x, y) for x, y in points], fill=fill, width=max(1, width * SCALE), joint="curve")


def glow(base, draw_fn, radius=2, alpha=90):
	layer = Image.new("RGBA", base.size, (0, 0, 0, 0))
	draw = ImageDraw.Draw(layer)
	draw_fn(draw)
	layer = layer.filter(ImageFilter.GaussianBlur(radius * SCALE / 2.0))
	if alpha < 255:
		r, g, b, _ = layer.split()
		a = layer.getchannel("A").point(lambda v: min(v, alpha))
		layer = Image.merge("RGBA", (r, g, b, a))
	base.alpha_composite(layer)


def downsample(img):
	return img.resize((SIZE, SIZE), Image.Resampling.NEAREST)


def outline_paste(dst, src, pos, color=c(12, 10, 9, 190)):
	x, y = pos
	alpha = src.getchannel("A")
	for ox, oy in ((-1, 0), (1, 0), (0, -1), (0, 1)):
		shadow = Image.new("RGBA", src.size, color)
		shadow.putalpha(alpha)
		dst.alpha_composite(shadow, (x + ox, y + oy))
	dst.alpha_composite(src, pos)


def new_frame():
	return Image.new("RGBA", (CANVAS, CANVAS), (0, 0, 0, 0))


def draw_base(img, accent):
	d = ImageDraw.Draw(img)
	d.ellipse(box(5, 22, 27, 31), fill=c(18, 13, 11, 78))
	d.polygon(p([(6, 25), (26, 25), (23, 30), (9, 30)]), fill=c(44, 38, 34))
	d.polygon(p([(7, 24), (25, 24), (22, 28), (10, 28)]), fill=c(122, 111, 94))
	d.rectangle(box(10, 18, 22, 25), fill=c(72, 67, 63))
	d.rectangle(box(11, 17, 21, 20), fill=c(158, 144, 119))
	for x, h in ((9, 4), (15, 5), (21, 4)):
		d.rectangle(box(x, 18 - h, x + 3, 18), fill=c(145, 135, 116))
	d.line([xy(9, 21), xy(23, 21)], fill=c(37, 33, 31), width=SCALE)
	d.line([xy(10, 24), xy(22, 24)], fill=accent, width=SCALE)
	for x in (12, 17, 22):
		d.line([xy(x, 18), xy(x - 1, 25)], fill=c(42, 38, 36, 120), width=SCALE)


def tower_arrow(frame):
	img = new_frame()
	draw_base(img, c(176, 118, 51))
	d = ImageDraw.Draw(img)
	y = 12 + (1 if frame in (1, 2) else 0)
	d.rectangle(box(12, y + 3, 20, y + 9), fill=c(83, 50, 30))
	line(d, [(8, y + 6), (24, y + 6)], c(62, 36, 23), 3)
	line(d, [(10, y + 1), (22, y + 11)], c(147, 92, 48), 2)
	line(d, [(22, y + 1), (10, y + 11)], c(147, 92, 48), 2)
	line(d, [(9, y + 6), (27 - frame, y + 6)], c(215, 204, 166), 1)
	d.polygon(p([(25 - frame, y + 4), (29 - frame, y + 6), (25 - frame, y + 8)]), fill=c(200, 158, 82))
	line(d, [(12, y + 4), (12, y + 8)], c(221, 184, 106), 1)
	return downsample(img)


def tower_fire(frame):
	img = new_frame()
	draw_base(img, c(185, 70, 38))
	d = ImageDraw.Draw(img)
	d.rectangle(box(10, 13, 22, 17), fill=c(58, 47, 39))
	line(d, [(10, 13), (22, 13)], c(181, 128, 74), 2)
	line(d, [(11, 17), (21, 17)], c(34, 29, 27), 1)
	glow(
		img,
		lambda gd: gd.ellipse(box(8, 7, 24, 23), fill=c(210, 65, 35, 110)),
		radius=3,
		alpha=80,
	)
	d.polygon(p([(16, 4 + frame % 2), (22, 14), (18, 20), (13, 20), (10, 14)]), fill=c(183, 45, 29, 235))
	d.polygon(p([(16, 7), (20, 15), (16, 19), (12, 15)]), fill=c(236, 132, 37, 242))
	d.polygon(p([(16, 10), (18, 15), (15, 17), (14, 14)]), fill=c(255, 220, 96, 245))
	return downsample(img)


def tower_ice(frame):
	img = new_frame()
	draw_base(img, c(86, 176, 207))
	d = ImageDraw.Draw(img)
	d.rectangle(box(11, 13, 21, 22), fill=c(166, 171, 174, 150))
	d.polygon(p([(16, 3), (23, 17), (16, 25), (9, 17)]), fill=c(75, 154, 202, 225))
	d.polygon(p([(16, 3), (20, 17), (16, 25)]), fill=c(190, 234, 244, 215))
	d.polygon(p([(16, 3), (12, 17), (16, 25)]), fill=c(52, 96, 154, 215))
	line(d, [(12, 11), (20, 20)], c(238, 252, 255), 1)
	line(d, [(11, 18), (21, 18)], c(35, 64, 92, 80), 1)
	for i in range(3):
		ang = (frame + i) * 1.7
		x = 16 + math.cos(ang) * 10
		y = 15 + math.sin(ang) * 7
		d.ellipse(box(x - 0.8, y - 0.8, x + 0.8, y + 0.8), fill=c(218, 246, 251, 160))
	return downsample(img)


def tower_lightning(frame):
	img = new_frame()
	draw_base(img, c(198, 172, 69))
	d = ImageDraw.Draw(img)
	d.rectangle(box(11, 9, 21, 22), fill=c(95, 88, 96))
	d.rectangle(box(13, 8, 19, 21), fill=c(162, 153, 145))
	line(d, [(11, 10), (21, 10)], c(211, 185, 82), 1)
	d.polygon(p([(16, 3), (20, 8), (12, 8)]), fill=c(221, 193, 83))
	d.ellipse(box(14, 4, 18, 8), fill=c(255, 240, 146))
	for i in range(2):
		y = 7 + i * 5 + frame % 2
		line(d, [(8, y), (12, y + 3)], c(239, 225, 84), 1)
		line(d, [(20, y + 2), (25, y - 2)], c(239, 225, 84), 1)
	return downsample(img)


def projectile_arrow(frame):
	img = new_frame()
	d = ImageDraw.Draw(img)
	line(d, [(5, 16), (24, 16)], c(89, 55, 31), 2)
	d.polygon(p([(23, 12), (29, 16), (23, 20)]), fill=c(184, 137, 69))
	d.polygon(p([(5, 16), (1, 12), (8, 15)]), fill=c(121, 41, 32, 210))
	d.polygon(p([(5, 16), (1, 20), (8, 17)]), fill=c(218, 210, 181, 210))
	line(d, [(6 - frame, 18), (1, 22)], c(229, 197, 119, 70), 1)
	return downsample(img)


def projectile_fire(frame):
	img = new_frame()
	d = ImageDraw.Draw(img)
	glow(img, lambda gd: gd.ellipse(box(6, 6, 27, 26), fill=c(203, 60, 32, 135)), radius=4, alpha=105)
	d.ellipse(box(9, 8, 26, 25), fill=c(168, 38, 25, 220))
	d.ellipse(box(13, 10, 24, 21), fill=c(231, 117, 33, 230))
	d.ellipse(box(18, 12, 22, 16), fill=c(255, 220, 91, 240))
	d.polygon(p([(11, 16), (2, 11 + frame), (7, 17), (2, 21 - frame)]), fill=c(218, 72, 35, 120))
	line(d, [(11, 20), (20, 11)], c(92, 40, 28, 95), 1)
	return downsample(img)


def projectile_ice(frame):
	img = new_frame()
	d = ImageDraw.Draw(img)
	d.polygon(p([(25, 16), (12, 9), (5, 16), (12, 23)]), fill=c(70, 159, 207, 225))
	d.polygon(p([(25, 16), (13, 12), (13, 20)]), fill=c(218, 245, 250, 210))
	line(d, [(8, 16), (24, 16)], c(248, 255, 255), 1)
	for i in range(3):
		x = 5 - frame - i * 2
		y = 12 + i * 4
		d.ellipse(box(x - 0.8, y - 0.8, x + 0.8, y + 0.8), fill=c(188, 230, 239, 150))
	return downsample(img)


def projectile_lightning(frame):
	img = new_frame()
	d = ImageDraw.Draw(img)
	pts = [(18, 2), (11, 13), (16, 13), (10, 30), (24, 11), (18, 12)]
	glow(img, lambda gd: line(gd, pts, c(235, 211, 72, 190), 4), radius=2, alpha=100)
	line(d, pts, c(235, 211, 72, 230), 3)
	line(d, pts, c(255, 247, 194, 245), 1)
	d.ellipse(box(7 - frame * 0.4, 7 - frame * 0.4, 25 + frame * 0.4, 25 + frame * 0.4), outline=c(91, 143, 203, 50), width=SCALE)
	return downsample(img)


def make_icon(frame):
	icon = Image.new("RGBA", (SIZE, SIZE), c(6, 5, 4, 255))
	d = ImageDraw.Draw(icon)
	d.rectangle((0, 0, 31, 31), fill=c(6, 5, 4, 255))
	d.rectangle((1, 1, 30, 30), outline=c(126, 91, 34), width=2)
	d.rectangle((3, 3, 28, 28), outline=c(44, 31, 16), width=1)
	for x, y in ((4, 4), (27, 4), (4, 27), (27, 27)):
		d.rectangle((x - 1, y - 1, x + 1, y + 1), fill=c(130, 28, 22))
		d.point((x, y), fill=c(218, 58, 43))
	outline_paste(icon, frame, (0, 0))
	return icon


def make_sheet(frames):
	sheet = Image.new("RGBA", (SIZE * FRAMES, SIZE), (0, 0, 0, 0))
	for i, frame in enumerate(frames):
		sheet.alpha_composite(frame, (i * SIZE, 0))
	return sheet


def save_png(path, image):
	image.save(path, optimize=True)


def make(name, tower_fn, projectile_fn):
	outdir = os.path.join(RES, name)
	tower_frames = [tower_fn(frame) for frame in range(FRAMES)]
	projectile_frames = [projectile_fn(frame) for frame in range(FRAMES)]
	save_png(os.path.join(outdir, "tower.png"), make_sheet(tower_frames))
	save_png(os.path.join(outdir, "icon.png"), make_icon(tower_frames[0]))
	save_png(os.path.join(outdir, "ST_%s.png" % ("Arrow" if name == "arrow" else name.capitalize())), make_sheet(projectile_frames))


def main():
	make("arrow", tower_arrow, projectile_arrow)
	make("fire", tower_fire, projectile_fire)
	make("ice", tower_ice, projectile_ice)
	make("lightning", tower_lightning, projectile_lightning)


if __name__ == "__main__":
	main()
