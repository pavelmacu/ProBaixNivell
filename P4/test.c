#include "CUnit/Basic.h"
 
#include "gpio_device.h"
#include "semaphore.h"
#include "controlsem.h"
#include "serial_device.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>


static pin_t PORT;
static pin_t PORT2;


/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */

int init_modul_semaphore(void)
{
  semaphore_init();
  return 0;
}
 
int init_modul_controlsem(void)
{
  controlsem_init();
  return 0;
}

int init_modul_serial_device(void)
{
  serial_init();
  return 0;
}
 

/* Simple test of fprintf().
 * Writes test data to the temporary file and checks
 * whether the expected number of bytes were written.
 */
void test_pin_create(void)
{
  PORT=pin_create(&PORTD, 3, Output);
  PORT2=pin_create(&PORTB, 3, Input);
  CU_ASSERT_EQUAL(PORT.port,PORTD);
  CU_ASSERT_EQUAL(PORT2.port,PORTB);
  CU_ASSERT_EQUAL(PORT.pin, 3);
}
 
 
void test_pin_w(void)
{
  pin_w(PORT, false);
  CU_ASSERT_EQUAL((*PORT.port & 0b00001000), 0b00000000);
  pin_w(PORT,true);
  CU_ASSERT_EQUAL((*PORT.port & 0b00001000), 0b00001000);
}
 
void test_pin_r(void)
{
  pin_w(PORT2, false);
  CU_ASSERT_EQUAL(pin_r(PORT2), false);
  pin_w(PORT2, true);
  CU_ASSERT_EQUAL(pin_r(PORT2), true);  
}
 
void test_pin_toggle(void)
{
  pinw(PORT2,false);
  CU_ASSERT_EQUAL(pin_toggle(PORT2), true);
  pinw(PORT2,true);
  CU_ASSERT_EQUAL(pin_toggle(PORT2), false);
  CU_ASSERT_EQUAL(pin_toggle(PORT2), true);
}
 
 
void test_semaphore_next(void){
  semaphore_set(2);
  CU_ASSERT_EQUAL(pin_r(LED_VERD), true);
  CU_ASSERT_EQUAL(pin_r(LED_GROC), false);
  CU_ASSERT_EQUAL(pin_r(LED_VERMELL), false);
  semaphore_next();
  CU_ASSERT_EQUAL(pin_r(LED_VERD), false);
  CU_ASSERT_EQUAL(pin_r(LED_GROC), true);
  CU_ASSERT_EQUAL(pin_r(LED_VERMELL), false);
  semaphore_next();
  CU_ASSERT_EQUAL(pin_r(LED_VERD), false);
  CU_ASSERT_EQUAL(pin_r(LED_GROC), false);
  CU_ASSERT_EQUAL(pin_r(LED_VERMELL), true);
  semaphore_next();
  CU_ASSERT_EQUAL(pin_r(LED_VERD), true);
  CU_ASSERT_EQUAL(pin_r(LED_GROC), false);
  CU_ASSERT_EQUAL(pin_r(LED_VERMELL), false);
}
  
void test_semaphore_set(void){
  semaphore_set(0);
  CU_ASSERT_EQUAL(pin_r(LED_VERD), false);
  CU_ASSERT_EQUAL(pin_r(LED_GROC), false);
  CU_ASSERT_EQUAL(pin_r(LED_VERMELL), false);
  semaphore_set(2);
  CU_ASSERT_EQUAL(pin_r(LED_VERD), true);
  CU_ASSERT_EQUAL(pin_r(LED_GROC), false);
  CU_ASSERT_EQUAL(pin_r(LED_VERMELL), false);
  semaphore_set(3);
  CU_ASSERT_EQUAL(pin_r(LED_VERD), false);
  CU_ASSERT_EQUAL(pin_r(LED_GROC), true);
  CU_ASSERT_EQUAL(pin_r(LED_VERMELL), false);
  semaphore_set(4);
  CU_ASSERT_EQUAL(pin_r(LED_VERD), false);
  CU_ASSERT_EQUAL(pin_r(LED_GROC), false);
  CU_ASSERT_EQUAL(pin_r(LED_VERMELL), true);
}

void test_tick_monitor(void)
{

}
 
void test_tick_semaphore(void)
{

}
 
 
void test_serial_get(void){

}
 

void test_serial_put(void){

}
 
void test_serial_can_read(void){

}
  
 
/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite=NULL,pSuite2= NULL,pSuite3=NULL, pSuite4=NULL;
 
   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();
 
   /* add a suite to the registry */
   pSuite = CU_add_suite("Modul gpio_device ", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   pSuite2 = CU_add_suite("Modul semaphore", init_modul_semaphore, NULL);
   if (NULL == pSuite2) {
      CU_cleanup_registry();
      return CU_get_error();
   }
 
   pSuite3 = CU_add_suite("Modul controlsem", init_modul_controlsem, NULL);
   if (NULL == pSuite3) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   pSuite4 = CU_add_suite("Modul serial_device", init_modul_serial_device, NULL);
   if (NULL == pSuite4) {
      CU_cleanup_registry();
      return CU_get_error();
   }
 
   CU_ADD_TEST(pSuite, test_pin_create);
   CU_ADD_TEST(pSuite, test_pin_w);
   CU_ADD_TEST(pSuite, test_pin_r);
   CU_ADD_TEST(pSUite, test_pin_toggle);
 
   CU_ADD_TEST(pSuite2, test_semaphore_init);
   CU_ADD_TEST(pSuite2, test_semaphore_next);
   CU_ADD_TEST(pSuite2, test_semaphore_set);
 
 
   CU_ADD_TEST(pSuite3, test_controlsem_init);
   CU_ADD_TEST(pSuite3, test_tick_monitor);
   CU_ADD_TEST(pSuite3, test_tick_semaphore);

   CU_ADD_TEST(pSuite4, test_serial_init);
   CU_ADD_TEST(pSuite4, test_serial_get);
   CU_ADD_TEST(pSuite4, test_serial_put);
   CU_ADD_TEST(pSuite4, test_serial_can_read);     
 
   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_NORMAL);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}