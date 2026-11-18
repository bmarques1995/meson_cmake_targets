meson setup build -Dlibrary_type=shared --prefix="./MinhaLib" --reconfigure
meson compile -C build
meson install -C build