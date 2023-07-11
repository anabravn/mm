#ifndef MM_H
#define MM_H

extern int n;
extern double **a, **b, **c;

void *mm(void *args);

double **createm(int n);
void initm(int n, double **matrix);

void printm(int n, double **matrix);

#endif
