#include "CUnit/Basic.h"

#include "codif.h"



static morse_table_t tm;


/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_modul_codif(void)
{
  empty_morse_table(tm);
  return 0;
}

/* Simple test of fprintf().
 * Writes test data to the temporary file and checks
 * whether the expected number of bytes were written.
 */
void test_set_translation(void)
{
  set_translation(tm,'F', "-..");
  set_translation(tm,'G', "-..");
  set_translation(tm,'A', ".");
}


void test_to_ascii(void)
{
  CU_ASSERT_EQUAL('G', to_ascii(tm,"-.."));
  CU_ASSERT_EQUAL('A', to_ascii(tm,"."));
  CU_ASSERT_EQUAL('@', to_ascii(tm,".-"));
}


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Modul codif", init_modul_codif, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   CU_ADD_TEST(pSuite, test_set_translation);
   CU_ADD_TEST(pSuite, test_to_ascii);

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

