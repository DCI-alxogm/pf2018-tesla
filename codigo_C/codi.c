#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main(){

double ***mat;
int n=10;

mat = (double ***) malloc(n  * sizeof(double*));

for (int r=0;r<n;r++){
	mat[r]= (double **) malloc(n * sizeof(double)); 

		for (int j=0;r<n;r++){
			mat[j]= (double *) malloc(n * sizeof(double)); 
			             }		

		     }


for (int i = 0; i < n; i++) {
	        for (int j = 0; j < n; j++) {
	            	for (int k = 0; k < n; k++) {
	            
				mat[i][j][k] = 0;
						    }
					    }



}

for (int i = 0; i < n; i++) {
	        for (int j = 0; j < n; j++) {
	            	for (int k = 0; k < n; k++) {
	            
				printf("%f", mat[i][j][k]);
						    }
					    }



}

}
