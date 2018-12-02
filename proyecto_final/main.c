#include <stdio.h>	
#include <math.h>
#include <stdlib.h>

void imprime(double **aux, int n);
double **esfera(double **aux, int n, double r, double t, double v);
double limit(double aux, double r);
double crea(double M);
void archivo(double **es1, double **es2, int n, int pos);


int main(){
	
	int N;
	double r_1, r_2, R, vo, h=0.001, T, pos=0;
	N = 100;
	r_1 = 10;
	r_2 = 15;
	R = 50;
	vo=5;
	T=0.01;
	
	double **es1, **es2;
	es1 = (double **) malloc(N*sizeof(double));	
	es2 = (double **) malloc(N*sizeof(double));

	for (int i=0 ; i<N ; i++){
		es1[i] = (double*) malloc (6*sizeof(double));
		es2[i] = (double*) malloc (6*sizeof(double));
	}

	es1 = esfera(es1, N, r_1, 0, vo);
	es2 = esfera(es2, N, r_2, T, vo);

	archivo (es1, es1, N, 123);
	return 0;
}
