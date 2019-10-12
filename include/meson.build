inc = include_directories('.')

mirdefh  = custom_target('cpmirdef',  output: 'mirdef.h', input: 'mirdef.h64',
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
