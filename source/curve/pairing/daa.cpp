/*
   Brickell & Li
   A Pairing-Based DAA scheme Further Reducing TPM  Resources

   Compile with modules as specified below

   For MR_PAIRING_CP curve
   cl /O2 /GX daa.cpp cp_pair.cpp zzn2.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

   For MR_PAIRING_MNT curve
   cl /O2 /GX daa.cpp mnt_pair.cpp zzn6a.cpp ecn3.cpp zzn3.cpp zzn2.cpp big.cpp zzn.cpp ecn.cpp miracl.lib
	
   For MR_PAIRING_BN curve
   cl /O2 /GX daa.cpp bn_pair.cpp zzn12a.cpp ecn2.cpp zzn4.cpp zzn2.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

   For MR_PAIRING_KSS curve
   cl /O2 /GX daa.cpp kss_pair.cpp zzn18.cpp zzn6.cpp ecn3.cpp zzn3.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

   For MR_PAIRING_BLS curve
   cl /O2 /GX daa.cpp bls_pair.cpp zzn24.cpp zzn8.cpp zzn4.cpp zzn2.cpp ecn4.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

*/

#include <iostream>
#include <ctime>

//********* choose just one of these pairs **********
//#define MR_PAIRING_CP      // AES-80 security   
//#define AES_SECURITY 80

//#define MR_PAIRING_MNT	// AES-80 security
//#define AES_SECURITY 80

#define MR_PAIRING_BN    // AES-128 or AES-192 security
#define AES_SECURITY 128
//#define AES_SECURITY 192

//#define MR_PAIRING_KSS    // AES-192 security
//#define AES_SECURITY 192

//#define MR_PAIRING_BLS    // AES-256 security
//#define AES_SECURITY 256
//*********************************************

#include "pairing_3.h"

int main()
{   
	PFC pfc(AES_SECURITY);  // initialise pairing-friendly curve
	miracl* mip=get_mip();

	time_t seed;

	int i,j;
	G1 g1,h1,h2;
	G2 g2,w;
	GT t1,t2,t3,t4;
	Big gamma;

	time(&seed);
    irand((long)seed);

// setup	
	cout << "Setup" << endl;

	Big order=pfc.order();

	pfc.random(g1);
	pfc.random(g2);
	pfc.random(gamma);
	pfc.random(h1);
	pfc.random(h2);
	w=pfc.mult(g2,gamma);

	t1=pfc.pairing(g2,g1); t2=pfc.pairing(g2,h1); t3=pfc.pairing(g2,h2); t4=pfc.pairing(w,h2);

	pfc.precomp_for_mult(g1);
	pfc.precomp_for_mult(g2);
	pfc.precomp_for_mult(h1);
	pfc.precomp_for_mult(h2);
	pfc.precomp_for_mult(w);
	pfc.precomp_for_pairing(g2);
	pfc.precomp_for_power(t1);
	pfc.precomp_for_power(t2);
	pfc.precomp_for_power(t3);
	pfc.precomp_for_power(t4);


// join
	cout << "Join" << endl;

	Big ni,f,sk,rf,c,sf,x,ci;
	G1 F,R;
// Issuer does..
	pfc.random(ni);  // random nonce

// TPM does..
	pfc.random(f);   // should be H(DAASeed||cnt||KI)
	sk=f;
	pfc.random(rf);
	F=pfc.mult(h1,f);
	R=pfc.mult(h1,rf);
	pfc.start_hash();
	pfc.add_to_hash(order); pfc.add_to_hash(g1); pfc.add_to_hash(h1), pfc.add_to_hash(h2); pfc.add_to_hash(g2); pfc.add_to_hash(w);
	pfc.add_to_hash(ni); pfc.add_to_hash(F); pfc.add_to_hash(R); c=pfc.finish_hash_to_group();
	sf=(rf+modmult(c,f,order))%order;
// TPM sends comm={F,c,sf,ni} to Issuer

// Issuer does..
// Issuer should check ni is the same, and that F is not revoked
	G1 Rc,A;
	Rc=pfc.mult(h1,sf)+pfc.mult(F,-c);
	pfc.start_hash();
	pfc.add_to_hash(order); pfc.add_to_hash(g1); pfc.add_to_hash(h1), pfc.add_to_hash(h2); pfc.add_to_hash(g2); pfc.add_to_hash(w);
	pfc.add_to_hash(ni); pfc.add_to_hash(F); pfc.add_to_hash(Rc); ci=pfc.finish_hash_to_group();
	if (ci!=c)
	{
		cout << "Verification fails, aborting.. " << endl;
		exit(0);
	}
	pfc.random(x);
	A=pfc.mult(g1+F,inverse(x+gamma,order));
// Issuer sends credential cre={A,x} to TPM
// TPM forwards F and cre to Host
// Host does..
	
	G2 wxg2=w+pfc.mult(g2,x);
	G1 g1f=-(F+g1);

	G1 *gf1[2];
	G2 *gf2[2];
	gf1[0]=&A; gf1[1]=&g1f;
	gf2[0]=&wxg2; gf2[1]=&g2;

	if (pfc.multi_pairing(2,gf2,gf1)!=1)
	{
		cout << "Verification fails, aborting.. " << endl;
		exit(0);
	}

// sign
	cout << "Sign" << endl;

	G1 B,K,R1,R2t,nv;
// Verifier does..
	pfc.random(nv);

// TPM does..
	pfc.hash_and_map(B,(char *)"bsn");

	pfc.random(rf);
	K=pfc.mult(B,f);
	R1=pfc.mult(B,rf);
	R2t=pfc.mult(h1,rf);
// TPM sends B, K, R1, R2t to Host
// Host does..
	G1 T;
	GT R2;
	Big a,b,rx,ra,rb,ch,nt;
	pfc.random(a);
	b=modmult(a,x,order);
	T=A+pfc.mult(h2,a);
	pfc.random(rx);
	pfc.random(ra);
	pfc.random(rb);

	R2=pfc.pairing(g2,R2t+pfc.mult(T,-rx)+pfc.mult(h2,rb))*pfc.power(t4,ra);

	pfc.start_hash();
	pfc.add_to_hash(order); pfc.add_to_hash(g1); pfc.add_to_hash(h1), pfc.add_to_hash(h2); pfc.add_to_hash(g2); pfc.add_to_hash(w);
	pfc.add_to_hash(B); pfc.add_to_hash(K); pfc.add_to_hash(T); pfc.add_to_hash(R1); pfc.add_to_hash(R2); pfc.add_to_hash(nv);
	ch=pfc.finish_hash_to_group();
// ch is sent to TPM

// TPM does..
	pfc.random(nt);
	pfc.start_hash(); pfc.add_to_hash(ch); pfc.add_to_hash(nt); pfc.add_to_hash((char *)"Test message to be signed");
	c=pfc.finish_hash_to_group();
	sf=(rf+modmult(c,f,order))%order;
// {c,nt,sf) sent to Host
	rf=0; // rf is erased

// Host does
	Big sx,sa,sb;
	sx=(rx+modmult(c,x,order))%order;
	sa=(ra+modmult(c,a,order))%order;
	sb=(rb+modmult(c,b,order))%order;
// Host outputs signature {B,K,T,c,nt,sf,sx,sa,sb}

// verify
	cout << "Verify" << endl;

	G1 R1c;
	GT R2c;
	Big cc;
	R1c=pfc.mult(B,sf)+pfc.mult(K,-c);

	R2c=pfc.pairing(pfc.mult(g2,-sx)+pfc.mult(w,-c),T)*pfc.power(t1,c)*pfc.power(t2,sf)*pfc.power(t3,sb)*pfc.power(t4,sa);

	pfc.start_hash();
	pfc.add_to_hash(order); pfc.add_to_hash(g1); pfc.add_to_hash(h1), pfc.add_to_hash(h2); pfc.add_to_hash(g2); pfc.add_to_hash(w);
	pfc.add_to_hash(B); pfc.add_to_hash(K); pfc.add_to_hash(T); pfc.add_to_hash(R1c); pfc.add_to_hash(R2c); pfc.add_to_hash(nv);
	ch=pfc.finish_hash_to_group();
	pfc.start_hash(); pfc.add_to_hash(ch); pfc.add_to_hash(nt); pfc.add_to_hash((char *)"Test message to be signed");
	cc=pfc.finish_hash_to_group();

	if (cc==c)
		cout << "Verification succeeds! " << endl;
	else
		cout << "Verification fails, aborting.. " << endl;

    return 0;
}
