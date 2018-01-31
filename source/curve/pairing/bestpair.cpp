//
// Program to generate "best" BN, BLS12, BLS24 and BLS48 curves (with modulus p=3 mod 8)
//
// g++ -O2 bestpair.cpp zzn8.cpp zzn4.cpp zzn2.cpp zzn.cpp ecn8.cpp ecn4.cpp ecn2.cpp ecn.cpp big.cpp miracl.a -o bestpair.exe
//
// Further tests may be needed to ensure full satisfaction (e.g. twist security, even x, etc.)
//
// Note that finding curves that are both GT and G2 Strong, can take a while
//
// SUggestions:-
// For AES-128 security: bestpair BLS12 64 3
// For AES-192 security: bestpair BLS24 48 4
// FOr AES-256 security: bestpair BLS48 32 4

// Some possible rational points on y^2=x^3+b (x^3+b is a perfect square)
// b=1, x=0, -1 or 2
// b=2, x=-1
// b=3, x=1
// b=4, x=0
// b=5, x=-1
// b=8, x=-2, 1, 2
// b=9, x=0, 3, 6, 40
// b=10, x=-1
// b=12, x=-2, 13

// b=-1, x=1
// b=-2, x=3;
// b=-4, x=2, 5
// b=-7, x=2, 32
// b=-8, x=2
// b=-11, x=3, 15

// of course these points need to be checked for correct order...

#include <iostream>
#include "big.h"
#include "ecn.h"
#include "ecn2.h"
#include "ecn4.h"
#include "ecn8.h"

#define BN 0
#define BLS12 1
#define BLS24 2
#define BLS48 3

using namespace std;

Miracl precision=500;

// Number of ways of selecting k items from n
Big combo(int n,int k)
{ // calculate n C k
	int i;
	Big c,d;

	d=1;
	for (i=2;i<=k;i++)
		d*=i;

	c=1;
	for (i=n;i>n-k;i--)
		c*=i;

	c/=d;
	return c;
}

// Number of candidates to be searched.
Big count(int b,int h)
{
	Big c=combo(b-h+1,h-1)+combo(b-h+1,h-2);
	c*=pow((Big)2,h);
	return c;
}

// Move to next NAF pattern
int iterate(int *x,int n)
{
	int i,j,k,gotone=0;
	for (i=0;i<n-1;i++)
	{
		if (x[i]==1 && x[i+2]==0)
		{
			gotone=1;
			x[i+1]=1;
			x[i]=0;
			if (x[0]==1) break;
			for (k=1;;k++)
				if (x[k]!=0) break;
			for (j=0;j<i-k;j+=2)
			{
				x[j]=x[j+k];
				x[j+k]=0;
			}
			break;
		}
		
	}
	return gotone;
}

int main(int argc, char *argv[])
{
	int HW,BITS,S,type,xm8,xm3,xm24,percent,pc;
	Big cnt,odds,total;
    int i,j,k,m,jj,bt,hw,twist,pb,nb,b,cb[40],ip;
	int xb[256];
	BOOL G2,GT,gotH,gotB,gotT,progress;
    Big msb,c,r,m1,n,p,q,t,x,y,w,X,Y,cof,cof2,coft,tau[9];
    Big PP,TT,FF;
	Big xp[10];
	int pw[10];
    miracl *mip=&precision;
    ECn P;

	argc--; argv++;

    if (argc<1)
    {
       cout << "Missing arguments" << endl;
	   cout << "Program to find best pairing-friendly curves" << endl;
       cout << "bestpair type bits Hamming-weight" << endl;
	   cout << "where type is the curve (BN, BLS12, BLS24, BLS48)" << endl;
	   cout << "where bits is number of bits in curve x parameter (>30 and <200)" << endl;
       cout << "and hamming-weight is the number of non-zero bits (>1 and <10)" << endl;
       cout << "e.g. bestpair BLS12 77 3" << endl;
	   cout << "Use flag /GT for GT-Strong curves" << endl;
	   cout << "Use flag /G2 for G2-Strong curves" << endl;
	   cout << "Use flag /P to show progress" << endl;

       exit(0);
    }

	ip=0; HW=0; BITS=0; 
	G2=GT=gotB=gotH=gotT=progress=FALSE;

	while (ip<argc)
	{
		if (!gotT && strcmp(argv[ip],"BN")==0)
		{
			ip++;
			gotT=TRUE;
			type=BN;
		}
		if (!gotT && strcmp(argv[ip],"BLS12")==0)
		{
			ip++;
			gotT=TRUE;
			type=BLS12;
		}
		if (!gotT && strcmp(argv[ip],"BLS24")==0)
		{
			ip++;
			gotT=TRUE;
			type=BLS24;
		}
		if (!gotT && strcmp(argv[ip],"BLS48")==0)
		{
			ip++;
			gotT=TRUE;
			type=BLS48;
		}
		if (!G2 && strcmp(argv[ip],"/G2")==0)
		{
			ip++;
			G2=TRUE;
			continue;
		}
		if (!GT && strcmp(argv[ip],"/GT")==0)
		{
			ip++;
			GT=TRUE;
			continue;
		}
		if (!progress && strcmp(argv[ip],"/P")==0)
		{
			ip++;
			progress=TRUE;
			continue;
		}
		if (!gotB)
		{
			BITS=atoi(argv[ip++]);
			gotB=TRUE;
			continue;
		}

		if (!gotH)
		{
			HW=atoi(argv[ip++]);
			gotH=TRUE;
			continue;
		}

        cout << "Error in command line" << endl;
        return 0;

	}
    if (!gotH || !gotB || !gotT || HW>9 || HW<2 || BITS>=200 || BITS<30)
    {
        cout << "Error in command line" << endl;
        return 0;
    }

	hw=HW-1;
	msb=pow((Big)2,BITS);

	for (i=0;i<=BITS;i++)
		xb[i]=0;

	for (i=0;i<hw;i++)
		xb[2*i]=1;

	S=0;

	total=count(BITS,HW);
	cout << "search " << total << " candidates" << endl;

// very approximate estimate of odds of success. Assumes primes are not correlated (but they are!)
	if (type==BN)
	{
		odds = (7*(4*BITS+5)/10)*(7*(4*BITS+5)/10);
		if (G2)
			odds*=(7*(4*BITS+5)/10);
		if (GT)
			odds*=(7*(12*BITS+16)/10);
	}
	if (type==BLS12)
	{
		odds = ((7*4*BITS)/10)*((7*6*BITS)/10);
		if (G2)
			odds*=(7*(8*BITS)/10);
		if (GT)
			odds*=(7*(20*BITS)/10);
	}
	if (type==BLS24)
	{
		odds = ((7*8*BITS)/10)*((7*10*BITS)/10);
		if (G2)
			odds*=(7*(32*BITS)/10);
		if (GT)
			odds*=(7*(72*BITS)/10);
	}
	if (type==BLS48)
	{
		odds = ((7*16*BITS)/10)*((7*18*BITS)/10);
		if (G2)
			odds*=(7*(128*BITS)/10);
		if (GT)
			odds*=(7*(272*BITS)/10);
	}

	odds/=8;  // frig factor
	cout << "one in " << odds << " expected to be OK" << endl;

//	gprime(1000);
	percent=-1;
	cnt=0;
	for (;;)
	{
		if (cnt>0 && !iterate(xb,BITS)) break;
		for (i=j=0;i<BITS;i++)
		{ // assign values to set bits
			if (xb[i]==1)
			{
				xp[j]=pow((Big)2,i);
				pw[j]=i;
				j++;
			}
		}
		xp[j]=msb;
		pw[j]=BITS;
		j++;

		// iterate through all combinations of + and - terms
		for (i=0;i<(1<<j);i++)
		{
			cnt+=1; 
			if (progress)
			{
				pc=toint((100*cnt)/total);

				if (percent<pc)
				{
					percent=pc;
					cout << pc << "\%" << endl;
				}
			}
			x=0;
			bt=1;
			//cout << "x= ";
			for (k=0;k<j;k++)
			{
				if ((bt&i)!=0) {x+=xp[k]; /*cout << "+2^" << pw[k];*/}
				else {x-=xp[k]; /*cout << "-2^" << pw[k];*/}
				bt<<=1;
			}

			if (type==BLS12)
			{
				xm24=x%24;
				if (x<0) xm24+=24;
				xm24%=24;
				xm3=xm24%3;
				if (xm3!=1) continue;   // quick exit for p%3=0
				xm8=xm24%8;
				if (xm8!=0 && xm8!=7) continue;  // quick exit for p=3 mod 8 condition

				q=pow(x,4)-x*x+1;
				p=q*(((x-1)*(x-1))/3)+x;

				t=x+1;
				n=p+1-t;

			}
			if (type==BLS24)
			{
				xm24=x%24;
				if (x<0) xm24+=24;
				xm24%=24;
				xm3=xm24%3;
				if (xm3!=1) continue;   // quick exit for p%3=0
				xm8=xm24%8;
				if (xm8!=0 && xm8!=7) continue;  // quick exit for p=3 mod 8 condition

				q=pow(x,8)-pow(x,4)+1;
				p=q*(((x-1)*(x-1))/3)+x;

				t=x+1;
				n=p+1-t;
				
			}

			if (type==BLS48)
			{
				xm24=x%24;
				if (x<0) xm24+=24;
				xm24%=24;
				xm3=xm24%3;
				if (xm3!=1) continue;   // quick exit for p%3=0
				xm8=xm24%8;
				if (xm8!=0 && xm8!=7) continue;  // quick exit for p=3 mod 8 condition

				q=pow(x,16)-pow(x,8)+1;
				p=q*(((x-1)*(x-1))/3)+x;
		
				t=x+1;
				n=p+1-t;
				
			}

			if (type==BN)
			{
				xm8=x%8;
				if (x<0) xm8+=8;
				xm8%=8;
				if (xm8!=3 && xm8!=7) continue;  // quick exit for p=3 mod 8 condition

				p=36*pow(x,4)+36*pow(x,3)+24*x*x+6*x+1;
				t=6*x*x+1;
				n=p+1-t;
				q=n;
			}

			if (p%8!=3) continue;                           // restriction here could be eased

			if (small_factors(q)) continue;
			if (small_factors(p)) continue;

			cof=n/q;

			if (type==BLS24)
			{
				coft=(pow(p,8)-pow(p,4)+1)/q;
			}

			if (type==BLS48)
			{
				coft=(pow(p,16)-pow(p,8)+1)/q;
			}

			if (type==BLS12 || type==BN)
			{
				coft=(pow(p,4)-p*p+1)/q;
			}

			if (GT)
			{
				if (small_factors(coft)) continue;
			}

			if (type==BLS12)
			{
				TT=t*t-2*p;
				PP=p*p;
				FF=t*(2*x*x*x-2*x*x-x+1)/3;
				m1=PP+1-(-3*FF+TT)/2;
			}

			if (type==BLS24)
			{
				TT=t*t*t*t-4*p*t*t+2*p*p;
				PP=pow(p,4);
				FF=sqrt((4*PP-TT*TT)/3);
				m1=PP+1-(3*FF+TT)/2;
			}
			if (type==BLS48)
			{
				tau[0]=2;  // count points on twist over extension p^8
				tau[1]=t;
				for (jj=1;jj<8;jj++ ) tau[jj+1]=t*tau[jj]-p*tau[jj-1];

				TT=tau[8];

				PP=pow(p,8);
				FF=sqrt((4*PP-TT*TT)/3);
				m1=PP+1-(3*FF+TT)/2;  //?
			}
			if (type==BN)
			{
				TT=t*t-2*p;
				PP=p*p;
				FF=sqrt((4*PP-TT*TT)/3);
				m1=PP+1-(3*FF+TT)/2;
			}
			cof2=m1/q;

			if (G2)
			{
				if (small_factors(cof2)) continue;
			}

			if (!prime(q)) continue;
			if (!prime(p)) continue;
			modulo(p);

			ZZn2 xi;

			xi.set(1,1);                // for p=3 mod 8
		
// make sure its irreducible
			if (pow(xi,(p*p-1)/2)==1)
				continue;
		
			if (pow(xi,(p*p-1)/3)==1) 
				continue;  // make sure that x^6-c is irreducible

			if (G2)
			{
				if (!prime(cof2)) continue;
			}

			if (GT)
			{
				if (!prime(coft)) continue;
			}

			
// we have a solution
// Find curve b parameter - uses first positive one found (but collect some other possibilities)
			pb=0;
			b=0;
			m=0;
			while (pb<=20 || b==0)
			{
				pb+=1;
				ecurve(0,pb,p,MR_AFFINE);
				while (!P.set(rand(p))) ;
				P*=cof;
				if ((q*P).iszero())
				{
					if (b==0) b=pb;
					else cb[m++]=pb;
				}

			}
			nb=0;
			while (nb>=-20)
			{
				nb-=1;
				ecurve(0,nb,p,MR_AFFINE);
				while (!P.set(rand(p))) ;
				P*=cof;
				if ((q*P).iszero())
					cb[m++]=nb;
			}

			ecurve(0,b,p,MR_AFFINE);
// find number of points on sextic twist..
			twist=MR_SEXTIC_D;
			mip->TWIST=MR_SEXTIC_D;

			if (type==BLS12 || type==BN)
			{
				ECn2 Q;
				ZZn2 rr;

				do
				{
					rr=randn2();
				} while (!Q.set(rr));
        
				Q*=cof2;
				if (!(n*Q).iszero()) 
				{
					twist=MR_SEXTIC_M;
					mip->TWIST=MR_SEXTIC_M;
					do
					{
						rr=randn2();
					} while (!Q.set(rr));
        
					Q*=cof2;
					if (!(n*Q).iszero()) 
					{
						cout << "Never Happens" << endl;
						continue;
					}
				}
			}
			if (type==BLS24)
			{
				ECn4 Q;
				ZZn4 rr;
				do
				{
					rr=randn4();
				} while (!Q.set(rr));

				Q*=cof2;
				if (!(n*Q).iszero()) 
				{
					twist=MR_SEXTIC_M;
					mip->TWIST=MR_SEXTIC_M;
					do
					{
						rr=randn4();
					} while (!Q.set(rr));
        
					Q*=cof2;
					if (!(n*Q).iszero()) 
					{
						cout << "Never Happens" << endl;
						continue;
					}
				}
			}
			if (type==BLS48)
			{
				ECn8 Q;
				ZZn8 rr;
				do
				{
					rr=randn8();
				} while (!Q.set(rr));

				Q*=cof2;
				if (!(n*Q).iszero()) 
				{
					twist=MR_SEXTIC_M;
					mip->TWIST=MR_SEXTIC_M;
					do
					{
						rr=randn8();
					} while (!Q.set(rr));
        
					Q*=cof2;
					if (!(n*Q).iszero()) 
					{
						cout << "Never Happens" << endl;
						continue;
					}
				}
			}
			S++;
			cout << endl;
			cout << "Solution " << S << endl;
			x=0;
			bt=1;
			mip->IOBASE=16;

			cout << "x= ";
			for (k=0;k<j;k++)
			{
				if ((bt&i)!=0) {x+=xp[k]; cout << "+2^" << pw[k];}
				else {x-=xp[k]; cout << "-2^" << pw[k];}
				bt<<=1;
			}
			cout << " = " << x << endl;
			cout << "Curve is y^2=x^3+" << b << endl;
			if (m>0)
			{
				cout << "(or) ";
				for (jj=0;jj<m;jj++)
					cout << cb[jj] << " ";
			}
			cout << "\np= " << p << " (" << bits(p) << " bits)";
			if (twist==MR_SEXTIC_D) cout << " D-Type" << endl;
			if (twist==MR_SEXTIC_M) cout << " M-Type" << endl;
			if (progress) cout << endl;
			mip->IOBASE=10;
		//	cout << "twist= " << p+1+t << endl;
		}
	}

	cout << endl;
	cout << cnt << " solutions searched" << endl;

	if (S==0)
	{
		cout << "No solutions found" << endl;
		return 0;
	}
	if (S==1)
	{
		cout << "One solution found" << endl;
		return 0;
	}
	cout << S << " solutions found" << endl;
	return 0;
}
