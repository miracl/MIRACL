inc = include_directories('.')

if host_machine.cpu_family() == 'x86_64'
	infile = files('mirdef.h64')
endif

if host_machine.cpu_family() == 'x86'
	infile = files('mirdef.h32')
endif

if host_machine.cpu_family() == 'arm'
	infile = files('mirdef.arm')
endif

mirdefh  = custom_target('cpmirdef',  output: 'mirdef.h', input: infile,
	  command: [cp, '@INPUT@', '@OUTPUT@' ])

install_headers([
	'big.h',
	'brick.h',
	'crt.h',
	'ebrick.h',
	'ebrick2.h',
	'ec2.h',
	'ecn.h',
	'ecnzzn.h',
	'flash.h',
	'floating.h',
	'gf2m.h',
	'miracl.h',
	'zzn.h'])
