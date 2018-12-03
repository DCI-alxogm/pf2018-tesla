#include <stdio.h>	
#include <math.h>
#include <stdlib.h>

void imprime(double **aux, int n);
double **esfera(double **aux, int n, double r, double t, double v);
double limit(double aux, double r);
double crea(double M);
void archivo(double **es1, double **es2, int n, int N, int pos);
double *fuerza(double **es1, double **es2, int mat, int pos, double *pun, int n, int N);


int main(){
	
	int n, N, pos=0;
	double r_1, r_2, R, vo, h=1, T;
	n = 100;	
	N = 200;
	r_1 = 10;
	r_2 = 15;
	R = 50;
	vo=5;
	T=10;
	
	double **es1, **es2, **nes1, **nes2;
	es1 = (double **) malloc(n*sizeof(double));	
	es2 = (double **) malloc(N*sizeof(double));
	nes1 = (double **) malloc(n*sizeof(double));	
	nes2 = (double **) malloc(N*sizeof(double));

	for (int i=0 ; i<n ; i++){
		es1[i] = (double*) malloc (9*sizeof(double));
		nes1[i] = (double*) malloc (9*sizeof(double));
	}
	for (int i=0 ; i<N ; i++){
		es2[i] = (double*) malloc (9*sizeof(double));
		nes2[i] = (double*) malloc (9*sizeof(double));
	}

	es1 = esfera(es1, n, r_1, 0, vo);
	es2 = esfera(es2, N, r_2, R, vo);
	
	for(int i=0 ; i<n ; i++){	
		es1[i] = fuerza(es1, es2, 0, i, es1[i], n, N);
	}
	for(int i=0 ; i<N ; i++){
		es2[i] = fuerza(es1, es2, 1, i, es2[i], n, N);
	}

	archivo(es1, es2, n, N, pos);
	pos++;
	
	for(double i=0 ; i<=T; i+=h){
		for(int j=0 ; j<n ; j++){			
			nes1[j][0] = es1[j][0] + h*es1[j][3] + (1/2)*es1[j][6]*(h*h);
			nes1[j][1] = es1[j][1] + h*es1[j][4] + (1/2)*es1[j][7]*(h*h);
			nes1[j][2] = es1[j][2] + h*es1[j][5] + (1/2)*es1[j][8]*(h*h);
			
			nes1[j] = fuerza(nes1, nes2, 0, j, nes1[j], n, N);

			nes1[j][3] = es1[j][3] + (1/2)*(es1[j][6]+nes1[j][6])*h;
			nes1[j][4] = es1[j][4] + (1/2)*(es1[j][7]+nes1[j][7])*h;
			nes1[j][5] = es1[j][5] + (1/2)*(es1[j][8]+nes1[j][8])*h;	
		}
		for(int j=0 ; j<N ; j++){			
			nes2[j][0] = es2[j][0] + h*es2[j][3] + (1/2)*es2[j][6]*(h*h);
			nes2[j][1] = es2[j][1] + h*es2[j][4] + (1/2)*es2[j][7]*(h*h);
			nes2[j][2] = es2[j][2] + h*es2[j][5] + (1/2)*es2[j][8]*(h*h);
			
			nes2[j] = fuerza(nes1, nes2, 1, j, nes2[j], n, N);

			nes2[j][3] = es2[j][3] + (1/2)*(es2[j][6]+nes2[j][6])*h;
			nes2[j][4] = es2[j][4] + (1/2)*(es2[j][7]+nes2[j][7])*h;
			nes2[j][5] = es2[j][5] + (1/2)*(es2[j][8]+nes2[j][8])*h;	
		}
		es1 = nes1;
		es2 = nes2;
		archivo(es1, es2, n, N, pos);
		pos++;
	}
	return 0;
}
