#ifndef MM_H
#define MM_H

typedef struct mm_args {
    int m, n, p;
    double **a, **b, **c;
    int i_start, i_end; // primeira e última linha 
} mm_args;

void mm_p(double **a, double **b, double **c, int m, int n, int p, int f);
void *mm_aux(void *args);

double **create_m(int m, int n);
void free_m(int m, double **matrix);

void init_m(int m, int n, double **matrix);

void print_m(int m, int n, double **matrix);

#endif
