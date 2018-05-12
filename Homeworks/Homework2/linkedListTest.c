#include <math.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "cmockaLinkedList.h"

void Invalid_Pointer(void **state)
{ 
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    newInfo = (int8_t *)NULL;
    int mydata = 2;
    my_enum status  =  insert_at_beginning(newInfo, mydata); 
    assert_int_equal(status, NULL_Pointer_passed);
}

void dataInsertedatStart(void **state)
{ 
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    int mydata = 3;
    my_enum status =  insert_at_beginning(newInfo, mydata); 
    assert_int_equal(status, inserted_at_beginning);
}

void dataInsertedatEnd(void **state)
{ 
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    int mydata = 4;
    my_enum status =  insert_at_end(newInfo, mydata); 
    assert_int_equal(status, inserted_at_end);
}

void deletedatStart(void **state)
{ 
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    my_enum status =  delete_at_beginning(newInfo); 
    assert_int_equal(status, deleted_at_beginning);
}

void deletedatEnd(void **state)
{ 
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    my_enum status =  delete_at_end(newInfo); 
    assert_int_equal(status, deleted_at_end);
}

void insertedatMiddle(void **state)
{ 
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    int mydata = 5;
    int position = 3;
    my_enum status =  insertNode_at_position(newInfo, mydata, position); 
    assert_int_equal(status, inserted_in_middle);
}

void deletedFromMiddle(void **state)
{ 
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    int position = 3;
    my_enum status =  delete_from_position(newInfo, mydata, position); 
    assert_int_equal(status, deleted_in_middle);
}

void getSize(void **state)
{ 
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    my_enum status =  size(newInfo); 
    assert_int_equal(status, got_size);
}


int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
  cmocka_unit_test(Invalid_Pointer),
  cmocka_unit_test(dataInsertedatStart),
  cmocka_unit_test(dataInsertedatEnd),
  cmocka_unit_test(deletedatStart),
  cmocka_unit_test(deletedatEnd),
  cmocka_unit_test(insertedatMiddle),
  cmocka_unit_test(deletedFromMiddle),
  cmocka_unit_test(getSize),
  };


  return cmocka_run_group_tests(tests, NULL, NULL);
}