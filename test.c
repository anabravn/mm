#include <check.h>
#include <stdlib.h>

#include "mm.h"

extern int n;
extern double **a, **b, **c;

START_TEST (mm_test)
{
    double **result;
    int args[2] = {0, 2};

    n = 2;

    a = createm(2); 
    b = createm(2); 
    c = createm(2);

    result = createm(2);

    result[0][0] = 8;
    result[0][1] = 9;
    result[1][0] = 20;
    result[1][1] = 21;

    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    a[1][1] = 4;

    b[0][0] = 4;
    b[0][1] = 3;
    b[1][0] = 2;
    b[1][1] = 3;

    mm((void *) args);

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            ck_assert_double_eq_tol(c[i][j], result[i][j], 10E-6);
        }
    }

   
    free(c);
}
END_TEST

Suite *mm_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Matrix Multiplication");
  tc_core = tcase_create("mm");

  tcase_add_test(tc_core, mm_test);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int no_failed = 0;                   
  Suite *s;                            
  SRunner *runner;                     

  s = mm_suite();                   
  runner = srunner_create(s);          

  srunner_run_all(runner, CK_NORMAL);  
  no_failed = srunner_ntests_failed(runner); 
  srunner_free(runner);                      
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}
