#include "dynamic_arrays_test.h"

int main(int argc, char **argv)
{
    Suite *s1 = suite_create("array_test");
    TCase *tc1_1 = tcase_create("array_test");
    SRunner *sr = srunner_create(s1);
    int numFailed;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, dynamicArrTest);

    srunner_run_all(sr, CK_ENV);
    numFailed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return numFailed == 0 ? 0 : 1;     
}
