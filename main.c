#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>

#include "mm.h"

double diff_timespec(const struct timespec *time1, const struct timespec *time0) {
  return (time1->tv_sec - time0->tv_sec)
      + (time1->tv_nsec - time0->tv_nsec) / 1000000000.0;
}

int main(int argc, char *argv[]) {
    double **a, **b, **c_p, **c_s;
    int f, m, n, p;
    struct timespec t1, t2;
    double tp, ts;

    if (argc < 5) {
        fprintf(stderr, "Argumentos inválidos.\n");
        return 1;
    }

    // tamanho das matrizes
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

    clock_gettime(CLOCK_MONOTONIC, &t1);
    mm_p(a, b, c_p, m, n, p, f); // Multiplicação em paralelo
    clock_gettime(CLOCK_MONOTONIC, &t2);
    tp = diff_timespec(&t2, &t1);

    clock_gettime(CLOCK_MONOTONIC, &t1);
    mm_s(a, b, c_s, m, n, p); // Multiplicação sequencial
    clock_gettime(CLOCK_MONOTONIC, &t2);
    ts = diff_timespec(&t2, &t1);

    // verifica se o resultado é o mesmo
    assert(equal_m(c_p, c_s, m, p));

    if (m <= 10) {
        printf("Matriz A:\n");
        print_m(m, n, a);

        printf("Matrix B:\n");
        print_m(n, p, b);

        printf("Matriz C = A * B:\n");
        print_m(m, p, c_p);
    } else {
        // saída: número de linhas, número de fluxos,
        // tempo paralelo, tempo sequencial
        printf("%d,%d,%.10f,%.10f\n", m, f, tp, ts);
    }

    free_m(m, a);
    free_m(n, b);
    free_m(m, c_p);
    free_m(m, c_s);

    return 0;
}
