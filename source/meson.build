mrmuldv_g64 = 'mrmuldv.g64'
mrmuldv_c = 'mrmuldv.c'

mrmuldvc = custom_target('mrmuldv.c', output: 'mrmuldv.c', input: 'mrmuldv.g64',
	  command: [cp, '@INPUT@', '@OUTPUT@' ])

miracl = static_library('miracl', [ 'mrcore.c', 'mrarth0.c',
	'mrarth1.c', 'mrarth2.c', 'mralloc.c',
	'mrsmall.c', 'mrio1.c', 'mrio2.c',
	'mrgcd.c', 'mrjack.c', 'mrxgcd.c',
	'mrarth3.c', 'mrbits.c', 'mrrand.c',
	'mrprime.c', 'mrcrt.c', 'mrscrt.c',
	'mrmonty.c', 'mrpower.c', 'mrsroot.c',
	'mrcurve.c', 'mrfast.c', 'mrshs.c',
	'mrshs256.c', 'mrshs512.c', 'mrsha3.c',
	'mrfpe.c', 'mraes.c', 'mrgcm.c',
	'mrlucas.c', 'mrzzn2.c', 'mrzzn2b.c',
	'mrzzn3.c', 'mrzzn4.c', 'mrecn2.c',
	'mrstrong.c', 'mrbrick.c', 'mrebrick.c',
	'mrec2m.c', 'mrgf2m.c','mrflash.c',
	'mrfrnd.c', 'mrdouble.c', 'mrround.c',
	'mrbuild.c', 'mrflsh1.c', 'mrpi.c',
	'mrflsh2.c', 'mrflsh3.c', 'mrflsh4.c',
	mrmuldvc, mirdefh
	], include_directories: inc, install: true, install_dir : 'lib')


if get_option('examples')
	executable('hail', [ mirdefh, 'hail.c' ], include_directories: inc, link_with: miracl)
	executable('palin', [ mirdefh, 'palin.c' ], include_directories: inc, link_with: miracl)
	executable('mersenne', [ mirdefh, 'mersenne.c' ], include_directories: inc, link_with: miracl)
	executable('brute', [ mirdefh, 'brute.c' ], include_directories: inc, link_with: miracl)
	executable('brent', [ mirdefh, 'brent.c' ], include_directories: inc, link_with: miracl)
	executable('pollard', [ mirdefh, 'pollard.c' ], include_directories: inc, link_with: miracl)
	executable('williams', [ mirdefh, 'williams.c' ], include_directories: inc, link_with: miracl)
	executable('lenstra', [ mirdefh, 'lenstra.c' ], include_directories: inc, link_with: miracl)
	executable('qsieve', [ mirdefh, 'qsieve.c' ], include_directories: inc, link_with: miracl)
	executable('factor', [ mirdefh, 'factor.c' ], include_directories: inc, link_with: miracl)
	executable('kangaroo', [ mirdefh, 'kangaroo.c' ], include_directories: inc, link_with: miracl)
	executable('genprime', [ mirdefh, 'genprime.c' ], include_directories: inc, link_with: miracl)
	executable('index', [ mirdefh, 'index.c' ], include_directories: inc, link_with: miracl)
	executable('pk-demo', [ mirdefh, 'pk-demo.c' ], include_directories: inc, link_with: miracl)
	executable('bmark', [ mirdefh, 'bmark.c' ], include_directories: inc, link_with: miracl)
	executable('imratio', [ mirdefh, 'imratio.c' ], include_directories: inc, link_with: miracl)
	executable('genkey', [ mirdefh, 'genkey.c' ], include_directories: inc, link_with: miracl)
	executable('encode', [ mirdefh, 'encode.c' ], include_directories: inc, link_with: miracl)
	executable('decode', [ mirdefh, 'decode.c' ], include_directories: inc, link_with: miracl)
	executable('enciph', [ mirdefh, 'enciph.c' ], include_directories: inc, link_with: miracl)
	executable('deciph', [ mirdefh, 'deciph.c' ], include_directories: inc, link_with: miracl)
	executable('dssetup', [ mirdefh, 'dssetup.c' ], include_directories: inc, link_with: miracl)
	executable('limlee', [ mirdefh, 'limlee.c' ], include_directories: inc, link_with: miracl)
	executable('dssgen', [ mirdefh, 'dssgen.c' ], include_directories: inc, link_with: miracl)
	executable('dssign', [ mirdefh, 'dssign.c' ], include_directories: inc, link_with: miracl)
	executable('dssver', [ mirdefh, 'dssver.c' ], include_directories: inc, link_with: miracl)
	executable('ecsgen', [ mirdefh, 'ecsgen.c' ], include_directories: inc, link_with: miracl)
	executable('ecsver', [ mirdefh, 'ecsver.c' ], include_directories: inc, link_with: miracl)
	executable('ecsgen2', [ mirdefh, 'ecsgen2.c' ], include_directories: inc, link_with: miracl)
	executable('ecsver2', [ mirdefh, 'ecsver2.c' ], include_directories: inc, link_with: miracl)
	executable('brick', [ mirdefh, 'brick.c' ], include_directories: inc, link_with: miracl)
	executable('ebrick', [ mirdefh, 'ebrick.c' ], include_directories: inc, link_with: miracl)
	executable('ebrick2', [ mirdefh, 'ebrick2.c' ], include_directories: inc, link_with: miracl)
	executable('identity', [ mirdefh, 'identity.c' ], include_directories: inc, link_with: miracl)
	executable('roots', [ mirdefh, 'roots.c' ], include_directories: inc, link_with: miracl)
	executable('hilbert', [ mirdefh, 'hilbert.c' ], include_directories: inc, link_with: miracl)
	executable('sample', [ mirdefh, 'sample.c' ], include_directories: inc, link_with: miracl)
#	executable('ratcalc', [ mirdefh, 'ratcalc.c' ], include_directories: inc, link_with: miracl)
endif
