#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "galaxia.h"

int main(){
	
	int n, N, pos=0, gen;
	double r_1, r_2, R, vo, h, T;
	char dir[70], arch[70];	

	FILE *lee;
	
	lee = fopen("inicio.txt", "r");
	fscanf(lee, "%i", &n);
	fscanf(lee, "%lf", &r_1);
	fscanf(lee, "%i", &N);
	fscanf(lee, "%lf", &r_2);
	fscanf(lee, "%lf", &vo);
	fscanf(lee, "%lf", &R);
	fscanf(lee, "%lf", &T);
	fscanf(lee, "%lf", &h);
	fgets(dir, 70, lee);
	fscanf(lee, "%i", &gen);
	printf("%i \n", gen);
	fgets(arch, 70, lee);
	fclose(lee);
	printf("%s", dir);
	printf("%s", arch);
		
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

	if(gen==1){	
		es1 = esfera(es1, n, r_1, 0, vo);
		es2 = esfera(es2, N, r_2, R, vo);
	}

	if(gen==0){
		FILE *galax;
		char *ex;
		ex = arch;
		galax = fopen(ex, "r");
		fscanf(galax, "%i", &n);
		for(int i=0 ; i<n ; i++){
			for(int j=0 ; j<6 ; j++){
				fscanf(galax, "%lf", &es1[i][j]);
			}	
		}
		fscanf(galax, "%i", &N);
		for(int i=0 ; i<N ; i++){
			for(int j=0 ; j<6 ; j++){
				fscanf(galax, "%lf", &es2[i][j]);
			}	
		}
	}

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
		//archivo(es1, es2, n, N, pos);
		pos++;
	}
	return 0;
}
