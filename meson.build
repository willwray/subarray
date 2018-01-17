project('subarray', 'cpp', default_options : 'cpp_std=c++1z')

test('test subarray',
  executable('test_subarray', 'test_subarray.cpp', cpp_args : '-fconcepts')
)

subarray_dep = declare_dependency(
  include_directories : include_directories('.')
)
