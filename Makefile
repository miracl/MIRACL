#=============================
#JKHOURY@BBN.COM
#	always compiles multi-threaded version
#	disable comba  optimization using flag comba=n
#=============================
top_srcdir = .
prefix = /usr/local
exec_prefix = ${prefix}
bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib
includedir = ${prefix}/include
mandir = ${prefix}/share/man
type=dynamic
curve=bn
comba=y

CC = gcc
CPP = g++
AR = ar
UNAME := $(shell uname) 

HEADERS = mirdef.h miracl.h big.h pairing_3.h zzn.h zzn2.h zzn3.h zzn4.h \
				zzn6.h zzn6a.h zzn8.h zzn12a.h zzn18.h zzn24.h \
				ecn.h ec2.h ecn2.h ecn3.h ecn4.h
DIST=miracl$(curve)
DISTNAME = $(addprefix lib, $(DIST))
CURVEPREFIX=mrpfc
CURVEDIST=$(CURVEPREFIX)$(curve)
CURVEDISTNAME=lib$(CURVEDIST)
TARGETS = copyfiles $(DISTNAME) $(CURVEDISTNAME) pclean
ifeq ($(curve), kss)
	WORDS = 8	 		 
else ifeq ($(curve), mnt)	
	WORDS = 3		
else ifeq ($(curve), cp)
	WORDS = 8	
else ifeq ($(curve), bn)
	WORDS = 4	
else ifeq ($(curve), bls)
	WORDS = 10
else
	TARGETS = exit	
endif

MIRDEF = mirdef.defaultMT
ifeq ($(strip $(comba)), y)
	MIRDEF = mirdef.comba$(WORDS)
	CPPFLAG = -DZZNS=$(WORDS)
	C_COMBA_OBJECT = mrcomba.o
endif

CFLAG = -D_REENTRANT
LDFLAGMT = -lpthread

ifeq ($(strip $(type)), static)
	CFLAGS = $(CFLAG)
	DISTNAME = $(addprefix lib,$(addsuffix .a, $(DIST)))	
	DISTS = $(DISTNAME).a $(CURVEDISTNAME).a
else #dynamic
	CFLAGS = -fPIC $(CFLAG)
ifeq ($(strip $(UNAME)), Darwin)
	DISTS = $(DISTNAME).dylib $(CURVEDISTNAME).dylib
else
	DISTS = $(DISTNAME).so $(CURVEDISTNAME).so
endif
			
endif
 
LDFLAG = -L. -l$(DIST)
LDFLAGS = $(LDFLAG) -l$(CURVEDIST) $(LDFLAGMT)

#TARGETS  = copyfiles $(DISTNAME) libmrpfccp libmrpfcmnt libmrpfcbn libmrpfckss libmrpfcbls libmrpfcss2 pclean

MANUALS  = $(TARGETS:=.1)
HTMLMANS = $(MANUALS:.1=.html)

C_OBJECTS = mrcore.o mrarth0.o mrarth1.o mrarth2.o mralloc.o mrsmall.o mrzzn2.o mrzzn3.o \
		mrio1.o mrio2.o mrjack.o mrgcd.o mrxgcd.o mrarth3.o mrbits.o mrecn2.o mrzzn4.o \
		mrrand.o mrprime.o mrcrt.o mrscrt.o mrmonty.o mrcurve.o mrsroot.o mrzzn2b.o \
		mrpower.o mrfast.o mrshs.o mrshs256.o mraes.o mrlucas.o mrstrong.o mrgcm.o \
		mrflash.o mrfrnd.o mrdouble.o mrround.o mrbuild.o \
		mrflsh1.o mrpi.o mrflsh2.o mrflsh3.o mrflsh4.o \
		mrbrick.o mrebrick.o mrec2m.o mrgf2m.o mrmuldv.o mrshs512.o $(C_COMBA_OBJECT)

CPP_OBJECTS = big.o gf2m4x.o gf2m.o \
		ecn.o ec2.o ecn2.o ecn3.o ecn4.o \
		zzn.o zzn2.o zzn3.o zzn4.o zzn6.o zzn6a.o zzn8.o zzn12a.o zzn18.o zzn24.o \
		cp_pair.o mnt_pair.o bn_pair.o kss_pair.o bls_pair.o ss2_pair.o \
		benchmark.o cpabe.o ipe.o cpabethread.o
		
cp_OBJECTS = cp_pair.o zzn2.o big.o zzn.o ecn.o
mnt_OBJECTS = mnt_pair.o zzn6a.o ecn3.o zzn3.o zzn2.o big.o zzn.o ecn.o
bn_OBJECTS = bn_pair.o zzn12a.o zzn4.o ecn2.o zzn2.o big.o zzn.o ecn.o
kss_OBJECTS = kss_pair.o zzn18.o zzn6.o ecn3.o zzn3.o big.o zzn.o ecn.o
bls_OBJECTS = bls_pair.o zzn24.o zzn8.o zzn4.o zzn2.o ecn4.o big.o zzn.o ecn.o
ss2_OBJECTS = ss2_pair.o ec2.o gf2m4x.o gf2m.o big.o
 
# default target
all: $(TARGETS)

mex: mex.c
	$(CC) -m64 -O2 -o $@ $^

	
copyfiles: mex
	echo "building for OS $(UNAME), curve $(curve)"
	cp $(MIRDEF) mirdef.h
	./mex $(WORDS) amd64 mrcomba
	cp -p mrmuldv.g64 mrmuldv.c
#ifeq ($(strip $(UNAME)), Darwin)
#	cp -p mrmuldv.macs64 mrmuldv.s64
#else #assume Linux
#	cp -p mrmuldv.linuxs64 mrmuldv.s64
#endif


$(DISTNAME): $(C_OBJECTS)
ifeq ($(strip $(type)), static)
	$(AR) r $@ $^
else	
ifeq ($(strip $(UNAME)), Darwin)
	$(CC) -dynamiclib -m64 -O2 -o $(addsuffix .dylib, $@) $^
else #assume Linux
	$(CC) -shared -Wl,-soname,$(addsuffix .so, $@) -m64 -O2 -o $(addsuffix .so, $@) $^
endif
endif

libmrpfccp: $(cp_OBJECTS)
ifeq ($(strip $(type)), static)
	$(AR) r $(addsuffux .a, $@) $^
else	
ifeq ($(strip $(UNAME)), Darwin)
	$(CPP) -dynamiclib -framework JavaVM -m64 -O2 $(CPPFLAG) -o $(addsuffix .dylib, $@) $^ $(LDFLAG)
else #assume Linux
	$(CPP) -shared -Wl,-soname,$(addsuffix .so, $@) -m64 -O2 $(CPPFLAG) -o $(addsuffix .so, $@) $^ $(LDFLAG)
endif
endif

libmrpfcmnt: $(mnt_OBJECTS)
ifeq ($(strip $(type)), static)
	$(AR) r $(addsuffux .a, $@) $^
else	
ifeq ($(strip $(UNAME)), Darwin)
	$(CPP) -dynamiclib -framework JavaVM -m64 -O2 $(CPPFLAG) -o $(addsuffix .dylib, $@) $^ $(LDFLAG)
else #assume Linux
	$(CPP) -shared -Wl,-soname,$(addsuffix .so, $@) -m64 -O2 $(CPPFLAG) -o $(addsuffix .so, $@) $^ $(LDFLAG)
endif
endif

libmrpfcbn: $(bn_OBJECTS)	
ifeq ($(strip $(type)), static)
	$(AR) r $(addsuffux .a, $@) $^
else	
ifeq ($(strip $(UNAME)), Darwin)
	$(CPP) -dynamiclib -framework JavaVM -m64 -O2 $(CPPFLAG) -o $(addsuffix .dylib, $@) $^ $(LDFLAG)
else #assume Linux
	$(CPP) -shared -Wl,-soname,$(addsuffix .so, $@) -m64 -O2 $(CPPFLAG) -o $(addsuffix .so, $@) $^ $(LDFLAG)
endif
endif

libmrpfckss: $(kss_OBJECTS)
ifeq ($(strip $(type)), static)
	$(AR) r $(addsuffux .a, $@) $^
else	
ifeq ($(strip $(UNAME)), Darwin)
	$(CPP) -dynamiclib -framework JavaVM -m64 -O2 $(CPPFLAG) -o $(addsuffix .dylib, $@) $^ $(LDFLAG)
else #assume Linux
	$(CPP) -shared -Wl,-soname,$(addsuffix .so, $@) -m64 -O2 $(CPPFLAG) -o $(addsuffix .so, $@) $^ $(LDFLAG)
endif
endif

libmrpfcbls: $(bls_OBJECTS)
ifeq ($(strip $(type)), static)
	$(AR) r $(addsuffux .a, $@) $^
else	
ifeq ($(strip $(UNAME)), Darwin)
	$(CPP) -dynamiclib -framework JavaVM -m64 -O2 $(CPPFLAG) -o $(addsuffix .dylib, $@) $^ $(LDFLAG)
else #assume Linux
	$(CPP) -shared -Wl,-soname,$(addsuffix .so, $@) -m64 -O2 $(CPPFLAG) -o $(addsuffix .so, $@) $^ $(LDFLAG)
endif
endif

libmrpfcss2: $(ss2_OBJECTS)
ifeq ($(strip $(type)), static)
	$(AR) r $(addsuffux .a, $@) $^
else	
ifeq ($(strip $(UNAME)), Darwin)
	$(CPP) -dynamiclib -framework JavaVM -m64 -O2 $(CPPFLAG) -o $(addsuffix .dylib, $@) $^ $(LDFLAG)
else #assume Linux
	$(CPP) -shared -Wl,-soname,$(addsuffix .so, $@) -m64 -O2 $(CPPFLAG) -o $(addsuffix .so, $@) $^ $(LDFLAG)
endif
endif		

benchmarkthread cpabethread:
	$(CPP) -m64 -O2 $(CPPFLAG) -o $@ $(addsuffix .cpp, $@) $(LDFLAGS)

$(CPP_OBJECTS):		
	$(CPP) -Wall -c -m64 -O2 $(CFLAGS) $(CPPFLAG) -o $@ $(subst .o,.cpp,$@)
	
mrcomba.o:
	$(CC) -Wall -c -m64 -O2 $(CFLAGS) -o $@ mrcomba.c

%.o: %.c	
ifeq ($(strip $(wildcard $<)),)
	$(CC) -Wall -c -m64 -O2 $(CFLAGS) -o $@ $<
else
	$(CPP) -c -m64 -O2 $(CFLAGS) $(CPPFLAG) -o $@ $(addsuffix pp, $<)
endif

exit:
	echo "You need to specify a correct curve: make curve=<curve> where curve=cp|mnt|bn|kss|bls"

pclean:
	rm *.o

# installation
install: $(DISTS) $(HEADERS)
	mkdir -p $(libdir)
	mkdir -p $(includedir)
	$(top_srcdir)/install-sh -m 755 $(DISTS) $(libdir)
	$(top_srcdir)/install-sh -m 644  $(HEADERS) $(includedir)
	
uninstall:
	for HEADER in $(HEADERS); \
	do \
	  /bin/rm -f $(includedir)/$$HEADER; \
	done
	for LIB in $(DISTS); \
	do \
	  /bin/rm -f $(libdir)/$$LIB; \
	done
	
# cleanup

# remove everything an installing user can rebuild
clean: pclean
	rm -f $(DISTS) *.tar.gz  *~ 
