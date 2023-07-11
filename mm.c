#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "mm.h"

int n;
double **a, **b, **c;

void *mm(void *args) {
    int *arr = (int *) args;
    int i = arr[0], x = i + arr[1];

    while(i < x) {
        for (int j = 0; j < n; j++) { 
            c[i][j] = 0;
            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
       i++; 
    }
}

double **createm(int n) {
    double **matrix = (double **) malloc(sizeof(double *) * n);

    for (int i = 0; i < n; i++) {
        matrix[i] = (double *) malloc(sizeof(double) * n);
    }

    return matrix;
}

void initm(int n, double  **matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void printm(int n, double **matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%0.2f ", matrix[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}
