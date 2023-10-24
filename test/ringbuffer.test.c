#include "../src/ringbuffer.h"
#include "vendor/unity.h"
#include <stdlib.h>

const int MAX_nbOfElements = 4;
RingBuffer *buffer;

void setUp(void) { buffer = ring_create(MAX_nbOfElements); }

void tearDown(void) { ring_delete(buffer); }

void test_ring_create(void) {
  TEST_ASSERT_NOT_NULL(buffer);

  TEST_MESSAGE("The next test does never fail when in debug mode.");
  TEST_ASSERT_NOT_NULL_MESSAGE(buffer->data, "buffer->data is null");
  for (int i = 0; i < MAX_nbOfElements; i++) {
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, buffer->data[i], "data should be 0");
  }
}

void an_empty_ring_should_have_nbOfElements_0(void) {
  int nbOfElements = buffer->nbOfElements;
  TEST_ASSERT_EQUAL_INT(0, nbOfElements);
}

void it_should_report_the_correct_number_of_elements(void) {
  ring_add(buffer, 1);
  ring_add(buffer, 2);
  ring_add(buffer, 3);
  TEST_ASSERT_EQUAL_INT(3, buffer->nbOfElements);

  int retVal = 0;
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(2, buffer->nbOfElements);
}

void it_should_not_exceed_its_maximum_nbOfElements(void) {
  ring_add(buffer, 1);
  ring_add(buffer, 2);
  ring_add(buffer, 3);
  ring_add(buffer, 4); //last element
  TEST_ASSERT_EQUAL_INT(4, buffer->nbOfElements);
  ring_add(buffer, 5); //exceeding element
  TEST_ASSERT_EQUAL_INT(4, buffer->nbOfElements);
}

void it_should_return_the_before_pushed_values(void) {
  ring_add(buffer, 1);
  ring_add(buffer, 2);
  ring_add(buffer, 3);
  int retVal = 0;
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(1, retVal);
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(2, retVal);
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(3, retVal);
}

void it_should_return_the_before_pushed_values_full_test(void) {
  ring_add(buffer, 1);
  ring_add(buffer, 2);
  ring_add(buffer, 3);
  ring_add(buffer, 4);
  int retVal = 0;
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(1, retVal);
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(2, retVal);
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(3, retVal);
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(4, retVal);
}

void it_should_return_false_when_empty(void) {
  int retVal = 0;
  TEST_ASSERT_FALSE(ring_remove(buffer, &retVal));
}

void it_should_return_true_when_element_was_successfully_returned(void) {
  int retVal = 0;
  ring_add(buffer, 1);
  TEST_ASSERT_TRUE(ring_remove(buffer, &retVal));
}

void it_should_write_in_a_circle_when_old_values_are_read(void) {
  ring_add(buffer, 1);
  ring_add(buffer, 2);
  ring_add(buffer, 3);
  ring_add(buffer, 4);
  int retVal = 0;
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(1, retVal);
  ring_add(buffer, 5);
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(2, retVal);
  ring_add(buffer, 6);
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(3, retVal);
  ring_add(buffer, 7);
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(4, retVal);
  ring_add(buffer, 8);
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(5, retVal);
  ring_add(buffer, 9);
  ring_remove(buffer, &retVal);
  TEST_ASSERT_EQUAL_INT(6, retVal);
}

void it_should_properly_free_the_allocated_space(void){
  return;
  //Just Checking for nullptr, free cannot be checked
  ring_delete(buffer);
  TEST_ASSERT_NULL(buffer);
}


int main(void) {
  UnityBegin("RingBuffer");

  RUN_TEST(test_ring_create);
  RUN_TEST(an_empty_ring_should_have_nbOfElements_0);
  RUN_TEST(it_should_report_the_correct_number_of_elements);
  RUN_TEST(it_should_not_exceed_its_maximum_nbOfElements);
  RUN_TEST(it_should_return_the_before_pushed_values);
  RUN_TEST(it_should_return_false_when_empty);
  RUN_TEST(it_should_return_true_when_element_was_successfully_returned);
  RUN_TEST(it_should_return_the_before_pushed_values_full_test);
  //RUN_TEST(it_should_properly_free_the_allocated_space);
  RUN_TEST(it_should_write_in_a_circle_when_old_values_are_read);

  UnityEnd();
  return 0;
}