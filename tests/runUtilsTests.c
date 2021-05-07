#include "dynamic_arrays_test.h"
#include "dynamic_matrix_test.h"

int main(int argc, char **argv)
{
    Suite *s1 = suite_create("utilsTest");
    SRunner *sr = srunner_create(s1);
    int numFailed;

    TCase *tc1_1 = tcase_create("array_test");
    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, dynamicArrTest);

    TCase *tc1_2 = tcase_create("matrix_test");
    suite_add_tcase(s1, tc1_2);
    tcase_add_test(tc1_1, dynamicMatrixTest);

    srunner_run_all(sr, CK_ENV);
    numFailed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return numFailed == 0 ? 0 : 1;
}
