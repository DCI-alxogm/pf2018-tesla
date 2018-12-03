#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Esta función imprime la matriz
void imprime(double **aux, int n){
	for(int i=0 ; i<n ; i++){
		for(int j=0 ; j<9 ; j++){
			printf("%0.3lf \t", aux[i][j]);
		}	
		printf("\n");
	}
}

//Esta función crea números aleatorios postivos o negativos, con 3 decimales, no mas grandes o mas pequeños que un valor M
double crea(double M){
	int pos = rand();
	pos%=2;
	double num = rand();
	int rest = num/(M*100);
	num -= rest*(M*100);
	num /=100;
	if(pos==0){
		return num*-1;
	}
	if(pos==1){
		return num;	
	}
}

//Esta función crea esferas de radio r, n puntos y con un desplazamiento "t" en el eje "x", con velocidad max "v"
double **esfera(double **aux, int n, double r, double t, double v){
	double count =0;
	for (int i=0 ; i<n ; i++){
		for(int j=0 ; j<6 ; j++){
			if(j<3){		
				aux[i][j] = crea(r);
			}
			if(j>=3){
				aux[i][j] = crea(v);	
			}
			if(j==3){				
				count = sqrt(aux[i][0]*aux[i][0]+aux[i][1]*aux[i][1]+aux[i][2]*aux[i][2]);
				if(count >r){
					j=0;				
				}
			}
		}
		aux[i][0]+=t;		
	}
	return aux;
}

//Esta función guarda los puntos en un archivo de texto
void archivo(double **es1, double **es2, int n, int N, int pos){
	if(pos>1000){
		return;
	}	
	//char total[] = "pf2018-tesla/proyecto_final/puntos/";	
	char name[7] = {'0', '0', '0', '.', 't', 'x', 't'};
	name[0]=(pos/100)+'0';
	pos%=100;
	name[1]=(pos/10)+'0';
	pos%=10;
	name[2]=pos+'0';

	//printf("%s \n", total);
	char *sup;
	sup = name;

	FILE *crea;

	crea = fopen(sup, "w");

	fprintf(crea, "%i \n", n);
	for(int i=0 ; i<n ; i++){
		for(int j=0 ; j<6 ; j++){
			fprintf(crea, "%0.2lf \t", es1[i][j]);
		}	
		fprintf(crea, "\n");
	}
	fprintf(crea, "\n");

	fprintf(crea, "%i \n", N);
	for(int i=0 ; i<N ; i++){
		for(int j=0 ; j<6 ; j++){
			fprintf(crea, "%0.2lf \t", es2[i][j]);
		}	
		fprintf(crea, "\n");
	}
	fprintf(crea, "\n");
	fclose(crea);
	return;
}


double *fuerza(double **es1, double **es2, int mat, int pos, double *pun, int n, int N){
	double x, y, z, G, r;
	G = -4*(3.14159265359)*(3.14159265359);
	pun[6]=0;
	pun[7]=0;
	pun[8]=0;
	x = pun[0];
	y = pun[1];
	z = pun[2];
	for(int i=0 ; i<n ; i++){
		if(i != pos || mat==1){
			r = sqrt((x-es1[i][0])*(x-es1[i][0])+(y-es1[i][1])*(y-es1[i][1])+(z-es1[i][2])*(z-es1[i][2]));			
			pun[6] += (G*(x-es1[i][0]))/(r*r*r);
			pun[7] += (G*(y-es1[i][1]))/(r*r*r);
			pun[8] += (G*(z-es1[i][2]))/(r*r*r);
		}	
	}
	for(int i=0 ; i<N ; i++){
		if(i != pos || mat==0){			
			r = sqrt((x-es2[i][0])*(x-es2[i][0])+(y-es2[i][1])*(y-es2[i][1])+(z-es2[i][2])*(z-es2[i][2]));			
			pun[6] += (G*(x-es2[i][0]))/(r*r*r);
			pun[7] += (G*(y-es2[i][1]))/(r*r*r);
			pun[8] += (G*(z-es2[i][2]))/(r*r*r);	
		}
	}
	return pun;
}

