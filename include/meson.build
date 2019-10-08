inc = include_directories('.')

mirdefh  = custom_target('cpmirdef',  output: 'mirdef.h', input: 'mirdef.h64',
	  command: [cp, '@INPUT@', '@OUTPUT@' ])
