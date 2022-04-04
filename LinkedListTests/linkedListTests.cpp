//
//  linkedListTests.cpp
//  LinkedListTests
//
//  Created by Ion Caus on 04.04.2022.
//

#include <gtest/gtest.h>

extern "C" {
    #include "linkedList.h"
}

linkedList_t _sut;
class LinkedListTests : public ::testing::Test {

protected:
    void SetUp() override {
        _sut = linkedList_create();
    }
    
    void TearDown() override {}
};


TEST_F(LinkedListTests, LinkedList_can_be_created) {
    ASSERT_FALSE(NULL == _sut);
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_can_be_destroyed) {
    linkedList_destroy(&_sut);
    ASSERT_TRUE(NULL == _sut);
}

TEST_F(LinkedListTests, LinkedList_can_push_node) {
    int item = 10;
    
    ASSERT_EQ(
              LINKED_LIST_OK,
              linkedList_push(_sut, &item)
              );
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_can_pull_head_node) {
    int item = 10;
    linkedList_push(_sut, &item);
    
    // act
    int* result = (int *)linkedList_pull(_sut);
    
    // assert
    ASSERT_EQ(0, linkedList_length(_sut));
    ASSERT_EQ(10, *result);
    
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_pull_when_listLinked_empty) {
    // act
    int* result = (int *)linkedList_pull(_sut);
    
    // assert
    ASSERT_TRUE(NULL == result);
}

TEST_F(LinkedListTests, LinkedList_can_peak_node) {
    int item1 = 10;
    linkedList_push(_sut, &item1);
    int item2 = 20;
    linkedList_push(_sut, &item2);
    
    // act
    int* resultAt0 = (int *)linkedList_peekItemByIndex(_sut, 0);
    int* resultAt1 = (int *)linkedList_peekItemByIndex(_sut, 1);
    
    // assert
    ASSERT_EQ(20, *resultAt0);
    ASSERT_EQ(10, *resultAt1);
    
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_when_peak_empty_list) {
    
    // act
    int* result = (int *)linkedList_peekItemByIndex(_sut, 2);
    
    // assert
    ASSERT_TRUE(NULL == result);
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_when_peak_outOfBound) {
    int item1 = 10;
    linkedList_push(_sut, &item1);
    
    // act
    int* result = (int *)linkedList_peekItemByIndex(_sut, 1);
    
    // assert
    ASSERT_TRUE(NULL == result);
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_contains_item) {
    int item1 = 10;
    linkedList_push(_sut, &item1);
    
    int item2 = 20;
    linkedList_push(_sut, &item2);
    
    int item3 = 30;
    linkedList_push(_sut, &item3);
    
    // act
    linkedList_return_codes_t result = linkedList_containsItem(_sut, &item1);
    
    // assert
    ASSERT_EQ(LINKED_LIST_FOUND, result);
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_not_contains_item) {
    int item1 = 10;
    linkedList_push(_sut, &item1);
    
    int item2 = 20;
    linkedList_push(_sut, &item2);
    
    int item3 = 30;
    
    // act
    linkedList_return_codes_t result = linkedList_containsItem(_sut, &item3);
    
    // assert
    ASSERT_EQ(LINKED_LIST_NOT_FOUND, result);
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_not_contains_item_when_empty_list) {
    int item1 = 10;
    
    // act
    linkedList_return_codes_t result = linkedList_containsItem(_sut, &item1);
    
    // assert
    ASSERT_EQ(LINKED_LIST_EMPTY, result);
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_can_clear_list) {
    int item1 = 10;
    linkedList_push(_sut, &item1);
    
    int item2 = 20;
    linkedList_push(_sut, &item2);
    
    int item3 = 30;
    linkedList_push(_sut, &item3);
    
    // act
    linkedList_clear(_sut);
    
    // assert
    ASSERT_FALSE(NULL == _sut);
    ASSERT_EQ(0, linkedList_length(_sut));
    
    ASSERT_TRUE(NULL == linkedList_pull(_sut));
    
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_can_remove_middle_node) {
    int item1 = 10;
    linkedList_push(_sut, &item1);
    
    int item2 = 20;
    linkedList_push(_sut, &item2);
    
    int item3 = 30;
    linkedList_push(_sut, &item3);
    
    // act
    linkedList_return_codes_t status =  linkedList_removeItem(_sut, &item2);
    
    // assert
    ASSERT_FALSE(NULL == _sut);
    ASSERT_EQ(2, linkedList_length(_sut));
    ASSERT_EQ(LINKED_LIST_OK, status);
    
    int* resultAt0 = (int *)linkedList_peekItemByIndex(_sut, 0);
    int* resultAt1 = (int *)linkedList_peekItemByIndex(_sut, 1);

    ASSERT_EQ(30, *resultAt0);
    ASSERT_EQ(10, *resultAt1);
              
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_can_remove_first_node) {
    int item1 = 10;
    linkedList_push(_sut, &item1);
    
    int item2 = 20;
    linkedList_push(_sut, &item2);
    
    int item3 = 30;
    linkedList_push(_sut, &item3);
    
    // act
    linkedList_return_codes_t status =  linkedList_removeItem(_sut, &item3);
    
    // assert
    ASSERT_FALSE(NULL == _sut);
    ASSERT_EQ(2, linkedList_length(_sut));
    ASSERT_EQ(LINKED_LIST_OK, status);
    
    int* resultAt0 = (int *)linkedList_peekItemByIndex(_sut, 0);
    int* resultAt1 = (int *)linkedList_peekItemByIndex(_sut, 1);

    ASSERT_EQ(20, *resultAt0);
    ASSERT_EQ(10, *resultAt1);
              
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_can_remove_last_node) {
    int item1 = 10;
    linkedList_push(_sut, &item1);
    
    int item2 = 20;
    linkedList_push(_sut, &item2);
    
    int item3 = 30;
    linkedList_push(_sut, &item3);
    
    // act
    linkedList_return_codes_t status =  linkedList_removeItem(_sut, &item1);
    
    // assert
    ASSERT_FALSE(NULL == _sut);
    ASSERT_EQ(2, linkedList_length(_sut));
    ASSERT_EQ(LINKED_LIST_OK, status);
    
    int* resultAt0 = (int *)linkedList_peekItemByIndex(_sut, 0);
    int* resultAt1 = (int *)linkedList_peekItemByIndex(_sut, 1);

    ASSERT_EQ(30, *resultAt0);
    ASSERT_EQ(20, *resultAt1);
              
    linkedList_destroy(&_sut);
}

TEST_F(LinkedListTests, LinkedList_remove_when_not_found) {
    int item1 = 10;
    linkedList_push(_sut, &item1);
    
    int item2 = 20;
    linkedList_push(_sut, &item2);
    
    int item3 = 30;
    
    // act
    linkedList_return_codes_t status =  linkedList_removeItem(_sut, &item3);
    
    // assert
    ASSERT_FALSE(NULL == _sut);
    ASSERT_EQ(2, linkedList_length(_sut));
    ASSERT_EQ(LINKED_LIST_NOT_FOUND, status);
              
    linkedList_destroy(&_sut);
}
