#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "mm.h"

extern int n;
extern double **a, **b, **c;

int main(int argc, char *argv[]) {
    pthread_t *id;
    int **args;
    int f, q, r;
    
    n = atoi(argv[1]); // tamanho da matriz
    f = atoi(argv[2]); // Número de fluxos de execução

    // vetor de ids de threads
    id = (pthread_t *) malloc(sizeof(pthread_t) * f);

    // argumentos p/ cada thread
    args = (int **) malloc(sizeof(int *) * f);

    // aloca matrizes
    a = createm(n);
    b = createm(n);
    c = createm(n);

     // inicializa matrizes
    initm(n, a);
    initm(n, b);

    printm(n, a); 
    printm(n, b);

    // número de linhas de cada fluxo
    q = n / f; 
    r = n % f;
 
    for (int i = 0; i < f; i++) {
        args[i] = (int *) malloc(sizeof(int) * 2);

        args[i][0] = i * q; // primeira linha
        args[i][1] = q; // número de linhas
    }

    args[0][1] += r;

    for(int i = 0; i < f; i++) {
        pthread_create(&id[i], NULL, mm, (void *) args[i]);
    }


    for (int i = 0; i < f; i++) {
        pthread_join(id[i], NULL);
        free(args[i]);
    }

    printm(n, c);

    free(a);
    free(b);
    free(c);
    free(id);

    return 0;
}
