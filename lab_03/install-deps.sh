mkdir -p subprojects
meson wrap install gtest
meson wrap install libarchive
meson setup --reconfigure build
