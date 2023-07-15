#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#include "mm.h"

int main(int argc, char *argv[]) {
    double **a, **b, **c_p, **c_s;
    int f, m, n, p;

    m = atoi(argv[1]);
    n = atoi(argv[2]); 
    p = atoi(argv[3]);

    f = atoi(argv[4]); // Número de fluxos de execução

    // aloca matrizes
    a = create_m(m, n);
    b = create_m(n, p);

    c_p = create_m(m, p);
    c_s = create_m(m, p);

     // inicializa matrizes
    init_m(m, n, a);
    init_m(n, p, b);

    if ((m <= 10) && (n <= 10) && (p <= 10)) {
        print_m(m, n, a);
        print_m(n, p, b);
    }

    mm_p(a, b, c_p, m, n, p, f); // Multiplicação em paralelo
    mm_s(a, b, c_s, m, n, p); // Multiplicação sequencial

    if ((m <= 10) && (p <= 10))
        print_m(m, p, c_p);

    // verifica se o resultado é correto
    assert(equal_m(c_p, c_s, m, p));

    free_m(m, a);
    free_m(n, b);
    free_m(m, c_p);
    free_m(m, c_s);

    return 0;
}
