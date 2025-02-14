#include "suites/test.h"

int main() {
  int failed_count = 0;
  SRunner *sr = (void *)0;

  sr = srunner_create(NULL);

  srunner_add_suite(sr, SmartCalc_suite());
  srunner_add_suite(sr, BankCalc_suite());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  failed_count = srunner_ntests_failed(sr);

  srunner_free(sr);

  return !failed_count ? EXIT_SUCCESS : EXIT_FAILURE;
}
