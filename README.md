# bfr5c99

Use meson to configure the build folder, with the installation prefix specified as a local direction (`pip install meson`):
`meson build -Dprefix=./install`

Compile, test and install from the build folder.
`cd build && ninja && ninja test && ninja install`
