all:
	meson setup build --wipe
	ninja -C build
