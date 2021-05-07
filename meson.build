project('miracl', 'c', 'cpp')

cp = find_program('cp')

subdir('include')
subdir('source')

pc = import('pkgconfig')
pc.generate(name: 'miracl', description: 'An infinite precision mathematics library.', libraries: [miracl])
