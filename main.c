#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>

#include "mm.h"

/**
 * Utilizada para calcular o tempo decorrido entre a execução
 * das funções
 *
 * @return Tempo real (monotônico) em segundos
 */
static inline double timer(void) {
    struct timespec tp;
    clockid_t id = CLOCK_MONOTONIC;

    clock_gettime(id, &tp);

    return (float) tp.tv_sec + ((float) tp.tv_nsec) * 10E-9;
}

int main(int argc, char *argv[]) {
    double **a, **b, **c_p, **c_s;
    int f, m, n, p;
    double t1, t2;

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

    t1 = timer();
    mm_p(a, b, c_p, m, n, p, f); // Multiplicação em paralelo
    t1 = timer() - t1; 

    t2 = timer();
    mm_s(a, b, c_s, m, n, p); // Multiplicação sequencial
    t2 = timer() - t2;

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
        printf("%d,%d,%f,%f\n", m, f, t1, t2);
    }

    free_m(m, a);
    free_m(n, b);
    free_m(m, c_p);
    free_m(m, c_s);

    return 0;
}
