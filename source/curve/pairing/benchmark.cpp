/*
	Quick Benchmark utility 
	jkhoury@bbn.com
	

*/
#include "miracl_wrapper.h"

#include <iostream>
#include <string>
#include <ctime>

int main(int argc, char* argv[])
{   
	const int NUM_GROUPS = 4, NUM_TIMES=11;
	int i,j=0, n=20;
	double t[NUM_TIMES], elapsed;
	clock_t start;
	

	PFC pfc(AES_SECURITY);  // initialise pairing-friendly curve
	miracl* mip=get_mip();

	time_t seed;
	
	if(argc == 2)
		n = atoi(argv[1]);
	
	string group_names[NUM_GROUPS ] = {"G1","G2","GT","Zp"};
	string headers[NUM_TIMES] = {"avg pairing time (ms): ", "one more multi_pairing (ms)",
								"avg pairing precomp time (ms): ", "avg pairing w/ precomp time (ms): ",  "one more multi_pairing x2 w/precomp (ms)", "one more multi_pairing x3 w/precomp (ms)",
								"avg multiply_G1 time (ms): ", "avg multiply_GT time (ms): ",
								"avg exp time (ms): ", "avg exp precomp time (ms): ", "avg exp w/ precomp time (ms): "
								};
	G1 g1[n], h1[n], H1[n], l1[n], r1[n], P1[n];
	G1 *mg1 [2];
	G1* mmg1[3];
	GROUP_NAME g2[n], h2[n], r2[n];
	GROUP_NAME *mg2[2];
	GROUP_NAME *mmg2[3];
	GT *L = new GT[n];
	GT *ML = new GT[n];
	GT *R = new GT[n];
	GT *MR = new GT[n];
	Big b1[n], b2[n];

	time(&seed);
    irand((long)seed);

	Big order=pfc.order();
	for(int i=0; i< NUM_TIMES; i++){
		t[i] = 0;
	}
	cout << "Starting pairing and multiplication benchmark, n=" << n << " iterations" << endl;
	for(int i=0; i<n; i++){
		pfc.random(g1[i]);
		pfc.random(g2[i]);
		pfc.random(l1[i]);
		pfc.random(r1[i]);
		pfc.random(r2[i]);
		pfc.random(h1[i]);
		pfc.random(b1[i]);
		pfc.random(b2[i]);	
	}
	
	//time to do pairing
	start = clock();
	for(int i=0; i<n; i++){
		L[i] = pfc.pairing(g2[i],g1[i]);
	}
	t[j++] = (clock()-start)/(double)CLOCKS_PER_SEC;

	//multi_pairing without preprocessing
	start = clock();
	for(int i=0; i<n; i++){
		int j=i+1;
		if(j == n) j=0;
		mg1[0] = &g1[i];
		mg1[1] = &g1[j];
		mg2[0] = &g2[i];
		mg2[1] = &g2[j];
		ML[i] = pfc.multi_pairing(2,mg2,mg1);
	}
	//this is measuring the incremental time needed to multi-pair
	t[j++] = (clock()-start)/(double)CLOCKS_PER_SEC - t[j-1];

	//do some validation
	for(int i=0; i<n; i++){
		int j=i+1;
		if(j == n) j=0;
		if(ML[i] != (L[i]*L[j])){
			cout << "multi_pairing ML[i] != (L[i]*L[j]) not working as expected!" << endl;
			exit(0);
		}
	}
		
	start = clock();
	for(int i=0; i<n; i++){
	//time to precomp for pairing
		pfc.precomp_for_pairing(g2[i]);
	}
	t[j++] = (clock()-start)/(double)CLOCKS_PER_SEC;
	
	start = clock();
	for(int i=0; i<n; i++){
		//time to pair with precomputation
		R[i] = pfc.pairing(g2[i],r1[i]);

	}
	t[j++] = (clock()-start)/(double)CLOCKS_PER_SEC;

	//multi_pairing with preprocessing
	start = clock();
	for(int i=0; i<n; i++){
		int j=i+1;
		if(j == n) j=0;
		mg1[0] = &r1[i];
		mg1[1] = &r1[j];
		mg2[0] = &g2[i];
		mg2[1] = &g2[j];
		MR[i] = pfc.multi_pairing(2,mg2,mg1);
	}
	//this is measuring the incremental time needed to multi-pair
	t[j++] = (clock()-start)/(double)CLOCKS_PER_SEC - t[j-1];

	//do some validation
	for(int i=0; i<n; i++){
		int j=i+1;
		if(j == n) j=0;
		if(MR[i] != (R[i]*R[j])){
			cout << "multi_pairing MR[i] != (R[i]*R[j]) not working as expected!" << endl;
			exit(0);
		}
	}
	cout << "Starting 3x multi_pair " << endl;
	//multi_pairing for 3 elements with preprocessing
	start = clock();
	for(int i=0; i<n; i++){
		int j=i+1;
		if(j==n) j=0;
		int k = j+1;
		if(k == n) k=0;
		mmg1[0] = &r1[i];
		mmg1[1] = &r1[j];
		mmg1[2] = &r1[k];
		mmg2[0] = &g2[i];
		mmg2[1] = &g2[j];
		mmg2[2] = &g2[k];
		pfc.multi_pairing(3,mmg2,mmg1);
	}
	//this is measuring the incremental time needed to multi-pair
	t[j++] = (clock()-start)/(double)CLOCKS_PER_SEC - t[j-2];


	//*********multiplication****************
	cout << "Starting group multiplication benchmark" << endl;
	//time to multiply in G1
	start = clock();
	for(int i=0; i<n; i++){
		P1[i] = l1[i] + r1[i]; //multiplication in the group
	}
	t[j++] = (clock()-start)/(double)CLOCKS_PER_SEC;

	//time to multiply in GT
	start = clock();
	for(int i=0; i<n; i++){
		GT t=L[i]*R[i]; //multiplication in the group
	}
	t[j++] = (clock()-start)/(double)CLOCKS_PER_SEC;





	//*********exponentiation****************
	cout << "Starting exponentiation benchmark" << endl;
	
	start = clock();
	for(int i=0; i<n; i++){
		//time to do exponentiation
		H1[i] = pfc.mult(h1[i],b1[i]);
	}
	//cout << "pairing time: " << elapsed << endl;
	t[j++] = (clock()-start)/(double)CLOCKS_PER_SEC;
	
	start = clock();
	for(int i=0; i<n; i++){	
		//time to precomp for exp
		pfc.precomp_for_mult(H1[i]);
	}
	t[j++] = (clock()-start)/(double)CLOCKS_PER_SEC;
	//cout << "precomp time: " << elapsed << endl;

	start = clock();
	for(int i=0; i<n; i++){
		//time to exp w/precomp
		pfc.mult(H1[i],b2[i]);
	}
	//cout << "pairing w/ precomp time: " << elapsed << endl;
	t[j++] = (clock()-start)/(double)CLOCKS_PER_SEC;
	
	for(int i=0; i< NUM_TIMES; i++){
		t[i] = 1000.0*t[i]/n;
		cout << headers[i];
		printf(" %8.3f\n", t[i]);
	}



	
	
	cout << "Completed" << endl;

    return 0;
}
