#include "testcases/batches_and_layers_test.h"
#include "testcases/activation_functions_test.h"
#include "testcases/loss_test.h"
#include "testcases/loss_with_sprial_data_test.h"

int main(int argc, char **argv)
{
    Suite *s1 = suite_create("batches_and_layers_test");
    SRunner *sr = srunner_create(s1);
    int numFailed;

    //TCase *tc1_1 = tcase_create("batches_and_layers_test");
    //suite_add_tcase(s1, tc1_1);
    //tcase_add_test(tc1_1, batches_and_layers_test);

    //TCase *tc1_2 = tcase_create("activation_functions_test");
    //suite_add_tcase(s1, tc1_2);
    //tcase_add_test(tc1_2, activation_functions_test);

    //TCase *tc1_3 = tcase_create("loss_test");
    //suite_add_tcase(s1, tc1_3);
    //tcase_add_test(tc1_3, loss_test);

    TCase *tc1_4 = tcase_create("loss_with_spiral_data_test");
    suite_add_tcase(s1, tc1_4);
    tcase_add_test(tc1_4, loss_with_spiral_data_test);

    srunner_run_all(sr, CK_ENV);
    numFailed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return numFailed == 0 ? 0 : 1;
}
