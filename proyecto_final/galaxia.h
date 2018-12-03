#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void imprime(double **aux, int n);
double **esfera(double **aux, int n, double r, double t, double v);
double limit(double aux, double r);
double crea(double M);
void archivo(double **es1, double **es2, int n, int N, int pos);
double *fuerza(double **es1, double **es2, int mat, int pos, double *pun, int n, int N);

