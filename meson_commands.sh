meson setup build -Dlibrary_type=shared --prefix="./install" --reconfigure
meson compile -C build
meson install -C build

pip install -e "<meson_fork>"