#ifndef MM_H
#define MM_H

/**
 * Estrutura utilizada para passar argumentos para a função
 * mm_aux(), que realiza a multiplicação de matrizes.
 */
typedef struct mm_args { 
    int m, n, p;
    double **a, **b, **c;

    /** Primeira linha */
    int i_start;

    /** Última linha (não incluida) */
    int i_end;
} mm_args;

void mm_p(double **a, double **b, double **c, int m, int n, int p, int f);
void *mm_aux(void *args);

double **create_m(int m, int n);
void free_m(int m, double **matrix);

void init_m(int m, int n, double **matrix);

void print_m(int m, int n, double **matrix);

#endif
