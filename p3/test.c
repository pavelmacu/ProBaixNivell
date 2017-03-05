#include "CUnit/Basic.h"

#include "itu.h"
#include "codif.h"
#include "streamencode.h"
#include <stdio.h>

static morse_table_t taula;
morse_table_t itu_table;

static morse_char_t l1,l2,l3;


static FILE *temp_file_in = NULL;
static FILE *temp_file_out = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_modul_codif(void)
{
  empty_morse_table(taula);
  return 0;
}

int init_modul_itu(void)
{
  itu_init();
  return 0;
}

/*int init_modul_streamencode(void)
{
  /*if(NULL == (temp_file = fopen("temp.txt", "w+")))
    return -1;
  else 
    return 0;*
}*/
/*int out_modul_streamencode(void)
{
  if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
}
}*/

/* Simple test of fprintf().
 * Writes test data to the temporary file and checks
 * whether the expected number of bytes were written.
 */
void test_set_translation(void)
{
  set_translation(taula,'F', "..-.");
  set_translation(taula,'G', "--.");
  set_translation(taula,'R', ".-.");
}


void test_to_ascii(void)
{ 
  to_morse(taula,'F',l1);
  to_morse(taula,'G',l2);
  to_morse(taula,'R',l3);
  CU_ASSERT_EQUAL('F', to_ascii(taula,l1));
  CU_ASSERT_EQUAL('G', to_ascii(taula,l2));
  CU_ASSERT_EQUAL('R', to_ascii(taula,l3));
}

void test_to_morse(void)
{
  CU_ASSERT_STRING_EQUAL(l1,"..-.");
  CU_ASSERT_STRING_EQUAL(l2,"--.");
  CU_ASSERT_STRING_EQUAL(l3,".-.");
}

void test_itu_init(void)
{
  CU_ASSERT_EQUAL('A', to_ascii(itu_table,".-"));
  CU_ASSERT_EQUAL('B', to_ascii(itu_table,"-..."));
  CU_ASSERT_EQUAL('Z', to_ascii(itu_table,"--.."));
  CU_ASSERT_EQUAL('0', to_ascii(itu_table,"-----"));
  CU_ASSERT_EQUAL('9', to_ascii(itu_table,"----."));  
}


void test_do_codifica(void){
	temp_file_out = tmpfile();
	temp_file_in = tmpfile();
	char escriure[] = "AB CD\n";
	char llegir[19];
	fputs(escriure,temp_file_in);
	fseek(temp_file_in,0, SEEK_SET);

	do_codifica(temp_file_in,temp_file_out);
	fseek(temp_file_out,0, SEEK_SET);
	fgets(llegir, 19, temp_file_out);
	
	CU_ASSERT_STRING_EQUAL(llegir,".- -...  -.-. -.. ");
	fclose(temp_file_out);
	fclose(temp_file_in); 

	temp_file_out = tmpfile();
	temp_file_in = tmpfile();
	char escriurea[] = "E T\n";
	char llegira[6];
	fputs(escriurea,temp_file_in);
	fseek(temp_file_in,0, SEEK_SET);

	do_codifica(temp_file_in,temp_file_out);
	fseek(temp_file_out,0, SEEK_SET);
	fgets(llegira, 6, temp_file_out);
	
	CU_ASSERT_STRING_EQUAL(llegira,".  - ");
	fclose(temp_file_out);
	fclose(temp_file_in); 

}



void test_do_descodifica(void){


	temp_file_out = tmpfile();
	temp_file_in = tmpfile();
	char escriureB[] = ".- -...  -.-. -..\n";
	char llegirB[6];
	fputs(escriureB,temp_file_in);
	fseek(temp_file_in,0, SEEK_SET);

	do_descodifica(temp_file_in,temp_file_out);
	fseek(temp_file_out,0, SEEK_SET);

	fgets(llegirB, 6, temp_file_out);
	CU_ASSERT_STRING_EQUAL(llegirB,"AB CD");
	fclose(temp_file_out);
	fclose(temp_file_in); 
}




/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite=NULL,pSuite2= NULL,pSuite3=NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Modul codif ", init_modul_codif, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   pSuite2 = CU_add_suite("Modul itu", init_modul_itu, NULL);
   if (NULL == pSuite2) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   pSuite3 = CU_add_suite("Modul streamencode", NULL, NULL);
   if (NULL == pSuite3) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   /* add the tests to the suite */
   /*if ((NULL == CU_add_test(pSuite, "test of set_translation()", test_set_translation)) ||
      (NULL == CU_add_test(pSuite, "test of to_ascii()", test_to_ascii)) ||
      (NULL == CU_add_test(pSuite, "test of to_morse()", test_to_morse)) ||
      (NULL == CU_add_test(pSuite2, "test of itu_init()", test_itu_init))||
      (NULL == CU_add_test(pSuite3, "test of do_codifica()", test_do_codifica))||
      (NULL == CU_add_test(pSuite3, "test of do_descodifica()", test_do_descodifica)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }*/


   CU_ADD_TEST(pSuite, test_set_translation);
   CU_ADD_TEST(pSuite, test_to_ascii);
   CU_ADD_TEST(pSuite, test_to_morse);

   CU_ADD_TEST(pSuite2, test_itu_init);

   CU_ADD_TEST(pSuite3, test_do_codifica);
   CU_ADD_TEST(pSuite3, test_do_descodifica);

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_NORMAL);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

