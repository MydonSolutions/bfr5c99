project('bfr5c99', 'c',
  version: '0.0',
)

src_lst = []
inc_lst = [
	include_directories('include'),
]
dep_lst = [dependency('hdf5')]

subdir('include')
subdir('src')

lib_bfr5c99 = library(
  'bfr5c99',
  src_lst,
  include_directories: inc_lst,
  dependencies: dep_lst,
  install: true,
  install_dir: 'lib'
)

lib_bfr5c99_dep = declare_dependency(
  include_directories: inc_lst,
  dependencies: dep_lst,
  link_with: lib_bfr5c99,
)

subdir('tests')