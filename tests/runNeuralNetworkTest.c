#include "batches_and_layers_test.h"

int main(int argc, char **argv)
{
    Suite *s1 = suite_create("utilsTest");
    SRunner *sr = srunner_create(s1);
    int numFailed;

    TCase *tc1_1 = tcase_create("batches_and_layers_test");
    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, batches_and_layers_test);

    srunner_run_all(sr, CK_ENV);
    numFailed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return numFailed == 0 ? 0 : 1;
}
