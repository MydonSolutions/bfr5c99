# bfr5c99

Use meson to configure the build folder, with the installation prefix specified as a local directory (`pip install meson ninja`):

`meson build -Dprefix=./install`

Compile, test and install from the build folder.

`cd build && ninja && ninja test && ninja install`

# Standing Issues

## [Specifying h5cc](https://github.com/MydonSolutions/bfr5c99/issues/4)
- Create `$HOME/.local/share/meson/native/hdf.ini` with the following content.

  ```
  [binaries]
  h5cc = '/usr/local/bin/h5pcc'
  ```
- `meson setup --native=hdf.ini`
