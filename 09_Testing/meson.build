project('buf', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

buf = library('buf', 'buf.c', 'buf.h')

test_names = ['init_free', 'free_null', 'push_index', 'grow_trunc', 'pop']

foreach t : test_names
  test_exe = executable('test_' + t, 'tests' / f'@t@.c', link_with: buf)
  test(t, test_exe)
endforeach
