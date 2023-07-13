#include <check.h>
#include <stdlib.h>

#include "mm.h"

void assert_equal_m(double **a, double **b, int m, int n) {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            ck_assert_double_eq_tol(a[i][j], b[i][j], 10E-6);
        }
    }
}

START_TEST (check_mm_odd)
{
    double **a, **b, **c, **result;
    int n = 3;

    a = create_m(n, n); 
    b = create_m(n, n); 
    c = create_m(n, n);

    result = create_m(n, n);

    a[0][0] = 3;
    a[0][1] = 2;
    a[0][2] = 10;
    a[1][0] = 1;
    a[1][1] = 8;
    a[1][2] = 10;
    a[2][0] = 2;
    a[2][1] = 1;
    a[2][2] = 4;

    b[0][0] = 2;
    b[0][1] = 6;
    b[0][2] = 5;
    b[1][0] = 7;
    b[1][1] = 6;
    b[1][2] = 9;
    b[2][0] = 2;
    b[2][1] = 0;
    b[2][2] = 7;

    result[0][0] = 40;
    result[0][1] = 30;
    result[0][2] = 103;
    result[1][0] = 78;
    result[1][1] = 54;
    result[1][2] = 147;
    result[2][0] = 19;
    result[2][1] = 18;
    result[2][2] = 47;

    mm_p(a, b, c, n, n, n, 3);

    assert_equal_m(c, result, n, n); 

    free_m(n, a);
    free_m(n, b);
    free_m(n, c);
    free_m(n, result);
}

START_TEST (check_mm_even)
{
    double **a, **b, **c, **result;
    int n = 2;

    a = create_m(n, n); 
    b = create_m(n, n); 
    c = create_m(n, n);

    result = create_m(n, n);

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

    mm_p(a, b, c, n, n, n, 2);

    assert_equal_m(c, result, n, n); 

    free_m(n, a);
    free_m(n, b);
    free_m(n, c);
    free_m(n, result);
}

START_TEST (check_mm_rect)
{
    double **a, **b, **c, **result;
    int m = 3, n = 4, p = 2;

    a = create_m(m, n); 
    b = create_m(n, p); 
    c = create_m(m, p);

    result = create_m(m, p);

    a[0][0] = 5;
    a[0][1] = 7;
    a[0][2] = 8;
    a[0][3] = 2;
    a[1][0] = 7;
    a[1][1] = 4;
    a[1][2] = 6;
    a[1][3] = 7;
    a[2][0] = 10;
    a[2][1] = 8;
    a[2][2] = 7;
    a[2][3] = 9;

    b[0][0] = 7;
    b[0][1] = 9;
    b[1][0] = 6;
    b[1][1] = 3;
    b[2][0] = 5;
    b[2][1] = 2;
    b[3][0] = 8;
    b[3][1] = 3;

    result[0][0] = 133;
    result[0][1] = 88;
    result[1][0] = 159;
    result[1][1] = 108;
    result[2][0] = 225;
    result[2][1] = 155;

    mm_p(a, b, c, m, n, p, 2);

    assert_equal_m(c, result, m, p); 

    free_m(m, a);
    free_m(n, b);
    free_m(m, c);
    free_m(m, result);
}
END_TEST


Suite *mm_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Matrix Multiplication");
  tc_core = tcase_create("mm");

  tcase_add_test(tc_core, check_mm_even);
  tcase_add_test(tc_core, check_mm_odd);
  tcase_add_test(tc_core, check_mm_rect);
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
