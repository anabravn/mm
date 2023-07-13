#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "mm.h"

void mm_p(double **a, double **b, double **c, int m, int n, int p, int f) {
    pthread_t *id = malloc(sizeof(pthread_t) * f);
    mm_args *args = (mm_args *) malloc(sizeof(mm_args) * f);
    int q, r;

    q = m / f;
    r = m % f;

    for (int i = 0; i < f; i++) {
        args[i].a = a;
        args[i].b = b;
        args[i].c = c;

        args[i].m = m;
        args[i].n = n;
        args[i].p = p;

        args[i].i_start = i * q;
        args[i].i_end = args[i].i_start + q;

    }

    args[f - 1].i_end += r; // resto

    for (int i = 0; i < f; i++) {
        pthread_create(&(id[i]), NULL, mm_aux, (void *) &(args[i]));
    }

    for (int i = 0; i < f; i++) {
        pthread_join(id[i], NULL);
    }

    free(args);
    free(id);
}

void *mm_aux(void *args) {
    mm_args *arg = (mm_args *) args;
    double **a, **b, **c;

    a = arg->a;
    b = arg->b;
    c = arg->c;


    for (int i = arg->i_start; i < arg->i_end; i++) {
        for (int j = 0; j < arg->p; j++) { 
            c[i][j] = 0;

            for (int k = 0; k < arg->n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }

    return NULL;
}

double **create_m(int m, int n) {
    double **matrix = (double **) malloc(sizeof(double *) * m);

    for (int i = 0; i < m; i++) {
        matrix[i] = (double *) malloc(sizeof(double) * n);
    }

    return matrix;
}

void free_m(int m, double **matrix) {
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

void init_m(int m, int n, double  **matrix) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void print_m(int m, int n, double **matrix) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%0.2f ", matrix[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}
