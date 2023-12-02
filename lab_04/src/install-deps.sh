mkdir -p subprojects
meson wrap install gtest
meson setup --reconfigure build
