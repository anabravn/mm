#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "mm.h"

/**
 * @brief Função auxiliar para multiplicação de matrizes em paralelo
 *
 * Calcula parte das linhas do resultado da multiplicaçãp
 * de duas matrizes. Utilizada em mm_p para dividir a multiplicação entre os 
 * fluxos, atribuindo uma quantidade de linhas a cada fluxo.
 *
 * @param args Um ponteiro para uma estrutura do tipo mm_args
 */
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

/**
 * @brief Multiplicação de matrizes em paralelo
 *
 * Realiza a multiplicação de matrizes em paralelo, dividindo a matriz
 * em blocos com aproximadamente a mesma quantidade de linhas para cada fluxo.
 *
 * As matrizes tem o formato
 * A (m x n) * B (n x p) = C (m x p) 

 * @param a Matriz A de ordem m x n
 * @param b Matriz B de ordem n x p
 * @param c Matriz C resultante, de ordem m x p
 *
 * @param m Número de linhas da matriz A e número de linhas da matriz resultante
 * @param n Número de linhas da matriz B e número de colunas da matriz resultante
 * @param p Número de colunas da matriz B e número  
 *
 * @param f Número de fluxos de execução
*/
void mm_p(double **a, double **b, double **c, int m, int n, int p, int f) {
    pthread_t *id = malloc(sizeof(pthread_t) * f);
    mm_args *args = (mm_args *) malloc(sizeof(mm_args) * f);
    int quociente, resto;

    /* Define a quantidade de linhas para cada fluxo */;
    quociente = m / f;
    resto = m % f;

    /**
     * Preenche um vetor com os argumentos para cada fluxo da função 
     * mm_aux(), definidos pela estrutura mm_args
     */
    for (int i = 0; i < f; i++) {
        /* Endereço das matrizes */
        args[i].a = a;
        args[i].b = b;
        args[i].c = c;

        /* Tamanho das matrizes */
        args[i].m = m;
        args[i].n = n;
        args[i].p = p;

        /* Linha inicial e linha final para cada fluxo */
        args[i].i_start = i * quociente;
        args[i].i_end = args[i].i_start + quociente;

    }

    /* Atribui as linhas restantes para o último fluxo */
    args[f - 1].i_end += resto;

    for (int i = 0; i < f; i++) {
        pthread_create(&(id[i]), NULL, mm_aux, (void *) &(args[i]));
    }

    for (int i = 0; i < f; i++) {
        pthread_join(id[i], NULL);
    }

    free(args);
    free(id);
}

/**
 * @brief Multiplicação de matrizes sequencial
 *
 * Realiza a multiplicação de matrizes sequencialmente, de maneira padrão.
 * As matrizes tem o formato
 * A (m x n) * B (n x p) = C (m x p) 

 * @param a Matriz A de ordem m x n
 * @param b Matriz B de ordem n x p
 * @param c Matriz C resultante, de ordem m x p
 *
 * @param m Número de linhas da matriz A e número de linhas da matriz resultante
 * @param n Número de linhas da matriz B e número de colunas da matriz resultante
 * @param p Número de colunas da matriz B e número  
*/
void mm_s(double **a, double **b, double **c, int m, int n, int p) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) { 
            c[i][j] = 0;

            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
}


/**
 * @brief Cria uma nova matriz
 *
 * Aloca memória para uma matriz de doubles, e retorna um 
 * ponteiro para a nova matriz.
 *
 * @param m Número de linhas
 * @param n Número de colunas
 */
double **create_m(int m, int n) {
    double **matrix = (double **) malloc(sizeof(double *) * m);

    for (int i = 0; i < m; i++) {
        matrix[i] = (double *) malloc(sizeof(double) * n);
    }

    return matrix;
}

/**
 * @brief Deleta uma matriz
 *
 * @param m Número de linhas 
 * @param n Número de colunas
 * @param matrix Ponteiro para a matriz
 */
void free_m(int m, double **matrix) {
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

/**
 * @brief Inicializa uma matriz aleatória
 *
 * Inicializa uma matriz já alocada com números
 * aleatórios entre 0 e 9.
 *
 * @param m Número de linhas
 * @param n Número de colunas
 * @param matrix Ponteiro para a matriz
 */
void init_m(int m, int n, double  **matrix) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

/**
 * @brief Escreve uma matriz na saída padrão
 *
 * @param m Número de linhas
 * @param n Número de colunas
 * @param matrix Ponteiro para a matriz
 */
void print_m(int m, int n, double **matrix) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%0.2f ", matrix[i][j]);
        }
        putchar('\n');
    }

    putchar('\n');
}

/**
 * @brief Comparação de matrizes
 *
 * @param a Matriz A de ordem m x n
 * @param b Matriz B de ordem m x n
 *
 * @param m Número de linhas das matrizes A e B
 * @param n Número de colunas das matrizes A e B
 *
 * @return 1 se as matrizes são iguais, 0 caso contrário
 *
 * @todo Suporte para números de ponto flutuante
 */
int equal_m(double **a, double **b, int m, int n) {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if (a[i][j] != b[i][j])
                return 0;
        }
    }

    return 1;
}


