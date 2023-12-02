project('lab_04', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])
src = [ 'sha1.cpp', 'rsa.cpp' ]
# zlib = dependency('zlib', method: 'system')
# gtest_proj = subproject('libarchive')
# libarchive = dependency('libarchive')
exe = executable('main', 'main.cpp',
  install : true, sources: src)

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')
tests_src = [
  'tests/gtest.cpp',
  'tests/sha1_test.cpp', 'sha1.cpp', 'rsa.cpp'
]  
e = executable(
  'gtest-all',
  tests_src,
  dependencies : [
    gtest_dep,
    gmock_dep, ],
)    
test('gtest tests', e)

