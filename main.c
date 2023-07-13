#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "mm.h"

int main(int argc, char *argv[]) {
    double **a, **b, **c;
    int f, m, n, p;

    /* 
    tamanho das matrizes 
    A (m x n) * B (n x p) = C (m x p) 
    */
    m = atoi(argv[1]);
    n = atoi(argv[2]); 
    p = atoi(argv[3]);

    f = atoi(argv[4]); // Número de fluxos de execução

    // aloca matrizes
    a = create_m(m, n);
    b = create_m(n, p);
    c = create_m(m, p);

     // inicializa matrizes
    init_m(m, n, a);
    init_m(n, p, b);

    if ((m <= 10) && (n <= 10) && (p <= 10)) {
        print_m(m, n, a);
        print_m(n, p, b);
    }

    mm_p(a, b, c, m, n, p, f);

    if ((m <= 10) && (p <= 10))
        print_m(m, p, c);

    free_m(m, a);
    free_m(n, b);
    free_m(m, c);

    return 0;
}
