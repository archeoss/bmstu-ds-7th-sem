project('lab_01', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])
src = [ 'Encoder.cpp', 'Enigma.cpp', 'ArchiveReader.cpp' ]
zlib = dependency('zlib', method: 'system')
gtest_proj = subproject('libarchive')
libarchive = dependency('libarchive')
exe = executable('main', 'main.cpp',
  install : true, sources: src, dependencies : [ zlib, libarchive ])

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')
tests_src = [
  'tests/gtest.cpp',
  'tests/enigma.cpp',
  'tests/encoder.cpp','Encoder.cpp', 'Enigma.cpp'
]  
e = executable(
  'gtest-all',
  tests_src,
  dependencies : [
    gtest_dep,
    gmock_dep, ],
)    
test('gtest tests', e)

