copy mirdef.mgw mirdef.h
gcc -c  -O2 mrcore.c
gcc -c  -O2 mrarth0.c
gcc -c  -O2 mrarth1.c
gcc -c  -O2 mrarth2.c
gcc -c  -O2 mralloc.c
gcc -c  -O2 mrsmall.c
gcc -c  -O2 mrio1.c
gcc -c  -O2 mrio2.c
gcc -c  -O2 mrgcd.c
gcc -c  -O2 mrjack.c
gcc -c  -O2 mrxgcd.c
gcc -c  -O2 mrarth3.c
gcc -c  -O2 mrbits.c
gcc -c  -O2 mrrand.c
gcc -c  -O2 mrprime.c
gcc -c  -O2 mrcrt.c
gcc -c  -O2 mrscrt.c
gcc -c  -O2 mrmonty.c
gcc -c  -O2 mrpower.c
gcc -c  -O2 mrsroot.c
gcc -c  -O2 mrcurve.c
gcc -c  -O2 mrfast.c
gcc -c  -O2 mrshs.c
gcc -c  -O2 mrshs256.c
gcc -c  -O2 mrshs512.c
gcc -c  -O2 mrsha3.c
gcc -c  -O2 mrfpe.c
gcc -c  -O2 mraes.c
gcc -c  -O2 mrgcm.c
gcc -c  -O2 mrlucas.c
gcc -c  -O2 mrzzn2.c
gcc -c  -O2 mrzzn2b.c
gcc -c  -O2 mrzzn3.c
gcc -c  -O2 mrzzn4.c
gcc -c  -O2 mrecn2.c
gcc -c  -O2 mrstrong.c
gcc -c  -O2 mrbrick.c
gcc -c  -O2 mrebrick.c
gcc -c  -O2 mrec2m.c
gcc -c  -O2 mrgf2m.c
gcc -c -O2 mrflash.c
gcc -c -O2 mrfrnd.c
gcc -c -O2 mrdouble.c
gcc -c -O2 mrround.c
gcc -c -O2 mrbuild.c
gcc -c -O2 mrflsh1.c
gcc -c -O2 mrpi.c
gcc -c -O2 mrflsh2.c
gcc -c -O2 mrflsh3.c
gcc -c -O2 mrflsh4.c
copy mrmuldv.g64 mrmuldv.c
gcc -c  -O2 mrmuldv.c
ar rc miracl.a mrcore.o mrarth0.o mrarth1.o mrarth2.o mralloc.o mrsmall.o mrzzn2.o mrzzn3.o
ar r miracl.a mrio1.o mrio2.o mrjack.o mrgcd.o mrxgcd.o mrarth3.o mrbits.o mrecn2.o mrzzn4.o
ar r miracl.a mrrand.o mrprime.o mrcrt.o mrscrt.o mrmonty.o mrcurve.o mrsroot.o mrzzn2b.o
ar r miracl.a mrpower.o mrfast.o mrshs.o mrshs256.o mraes.o mrlucas.o mrstrong.o mrgcm.o 
ar r miracl.a mrbrick.o mrebrick.o mrec2m.o mrgf2m.o mrmuldv.o mrshs512.o mrsha3.o mrfpe.o
ar r miracl.a mrdouble.o mrround.o mrbuild.o mrflsh1.o mrpi.o mrflsh2.o mrflsh3.o mrflsh4.o mrflash.o mrfrnd.o

