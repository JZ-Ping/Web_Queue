// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"
#include <string>

using namespace std;

// Add your test cases here

TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_empty) {
    List<int> list;
    list.empty();
    ASSERT_TRUE(list.size() == 0);
}

TEST(test_add_remove) {
    List<int> list;
    list.push_front(1);
    list.push_back(2);
    list.push_front(0);
    list.push_back(3);
    ASSERT_TRUE(list.size() == 4);
    ASSERT_TRUE(list.front() == 0);
    ASSERT_TRUE(list.back() == 3);
    
    list.pop_front();
    ASSERT_TRUE(list.front() == 1);

    list.pop_back();
    ASSERT_TRUE(list.back() == 2);
    ASSERT_TRUE(list.size() == 2);

    list.clear();
    ASSERT_TRUE(list.size() == 0);
}

TEST(test_assign) {
    List<char> list1;
    list1.push_front('b');
    list1.push_back('c');
    list1.push_front('a');
    list1.push_back('d');

    List<char> list2;
    list2 = list1;
    ASSERT_TRUE(list1.front() == list2.front());
    ASSERT_TRUE(list1.back() == list2.back());

    list1.pop_back();
    list1.pop_front();
    list2.pop_back();
    list2.pop_front();
    ASSERT_TRUE(list1.front() == list2.front());
    ASSERT_TRUE(list1.back() == list2.back());

    list1.push_front('a');
    list1.push_back('c');
    list2.push_front('a');
    list2.push_back('c');
    ASSERT_TRUE(list1.front() == list2.front());
    ASSERT_TRUE(list1.back() == list2.back());
}

TEST(test_push_front_empty){
    List<int> empty_list;
    empty_list.push_front(1);
    ASSERT_TRUE(!empty_list.empty());
    ASSERT_TRUE(empty_list.size() == 1);
    ASSERT_TRUE(empty_list.front() == 1);
    ASSERT_TRUE(empty_list.back() == 1);
}

TEST(test_push_back_empty){
    List<int> empty_list;
    empty_list.push_back(1);
    ASSERT_TRUE(!empty_list.empty());
    ASSERT_TRUE(empty_list.size() == 1);
    ASSERT_TRUE(empty_list.front() == 1);
    ASSERT_TRUE(empty_list.back() == 1);
}

TEST(test_clear_empty){
    List<int> empty_list;
    empty_list.clear();
    assert(empty_list.empty());
    assert(empty_list.size() == 0);
}

TEST(test_push_front_back_nonempty){
    List<char> list;
    list.push_front('c');
    list.push_front('b');
    list.push_front('a');
    list.push_back('d');
    list.push_back('e');
    list.push_back('f');
    ASSERT_TRUE(list.size() == 6);
    ASSERT_TRUE(list.front() == 'a');
    ASSERT_TRUE(list.back() == 'f');
}

TEST(test_pop_front_back){
    List<char> list;
    list.push_front('c');
    list.push_front('b');
    list.push_front('a');
    list.push_back('d');
    list.push_back('e');
    list.push_back('f');
    list.pop_front();
    list.pop_back();
    ASSERT_TRUE(list.size() == 4);
    ASSERT_TRUE(list.front() == 'b');
    ASSERT_TRUE(list.back() == 'e');
}

TEST(test_iterator_operations){
    List<std::string> list2;
    list2.push_front("apple");
    list2.push_back("banana");
    list2.push_back("cherry");
    list2.push_front("orange");
    List<std::string>::Iterator it = list2.begin();
    ASSERT_TRUE((*it) == "orange");
    ++it;
    ASSERT_TRUE((*it) == "apple");
    --it;
    ASSERT_TRUE((*it) == "orange");
}

TEST(test_copy_assignment){
    List<int> list1;
    list1.push_front(1);
    list1.push_front(2);
    List<int> list2;
    list2 = list1;
    ASSERT_TRUE(list2.size() == 2);
    ASSERT_TRUE(list2.front() == 2);
    ASSERT_TRUE(list2.back() == 1);
    list1.push_front(3);
    list2.clear();
    list2 = list1;
    ASSERT_TRUE(list2.size() == 3);
    ASSERT_TRUE(list2.front() == 3);
    ASSERT_TRUE(list2.back() == 1);
}

TEST(test_insert_empty){
    List<char> list;
    List<char>::Iterator i = list.begin();
    list.insert(i, 'c');
    ASSERT_TRUE(list.front() == 'c');
    ASSERT_TRUE(list.back() == 'c');
    ASSERT_TRUE(list.size() == 1);
    List<char>::Iterator i2 = list.begin();
    list.erase(i2);
    ASSERT_TRUE(list.empty());
}

TEST(test_insert_erase){
    List<double> list;
    list.push_front(1.5);
    list.push_front(2.3);
    list.push_front(4.7);
    List<double>::Iterator i = list.begin();
    ++i;
    list.insert(i, 4.1);
    --i;
    ASSERT_ALMOST_EQUAL(*i, 4.1, 0.01);
    ASSERT_TRUE(list.size() == 4);
    List<double>::Iterator j = list.begin();
    list.erase(j);
    ASSERT_ALMOST_EQUAL(list.front(), 4.1, 0.01);
    ASSERT_ALMOST_EQUAL(list.back(), 1.5, 0.01);
}

TEST(test_iterator_equal){
    List<string> list;
    list.push_back("elem1");
    list.push_back("elem2");
    list.push_back("elem3");
    List<string>::Iterator i = list.begin();
    ++i;
    ++i;
    List<string>::Iterator j = list.begin();
    ++j;
    ++j;
    --j;
    ASSERT_TRUE(i!=j);
    ++j;
    ASSERT_TRUE(i==j);
    ++i;
    ASSERT_TRUE(i==list.end());    
}

TEST(test_copy_assignment_empty){
    List<int> list1;
    List<int> list2;
    list1 = list2;
    ASSERT_TRUE(list1.empty());
    ASSERT_TRUE(list2.empty());
    List<int> list3(list2);
    ASSERT_TRUE(list3.empty());
}

TEST(test_big_three){
    List<int> list1;
    list1.push_back(7);
    list1.push_back(2);
    list1.push_back(5);
    List<int> list2 = list1;
    list2.push_back(4);
    ASSERT_TRUE(list1.front() == 7);
    ASSERT_TRUE(list1.back() == 5);
    ASSERT_TRUE(list1.size() == 3);
    ASSERT_TRUE(list2.front() == 7);
    ASSERT_TRUE(list2.back() == 4);
    ASSERT_TRUE(list2.size() == 4);
    list2.pop_back();
    list2.pop_front();
    List<int> list3(list2);
    ASSERT_TRUE(list2.front() == 2);
    ASSERT_TRUE(list2.back() == 5);
    ASSERT_TRUE(list2.size() == 2);
}

TEST(test_assigment){
    List<int> list5;
    list5.push_front(4);
    list5.push_front(5);
    List<int> list6(list5);
    assert(list6.size() == 2);
    assert(list6.front() == 5);
    assert(list6.back() == 4);
    list5.push_front(6);
    list6 = list5;
    assert(list6.size() == 3);
    assert(list6.front() == 6);
    assert(list6.back() == 4);
}

TEST(test_end){
    List<int> list8;
    list8.push_front(1);
    list8.push_back(2);
    list8.push_back(3);
    List<int>::Iterator it1 = list8.begin();
    ++it1;
    ++it1;
    ++it1;
    List<int>::Iterator it2 = list8.end();
    assert(it1 == it2);
}

TEST(test_iterator_equality){
    List<int> list7;
    list7.push_front(1);
    list7.push_front(2);
    list7.push_front(3);
    List<int>::Iterator it1 = list7.begin();
    List<int>::Iterator it2 = list7.begin();
    assert(it1 == it2);
    ++it1;
    assert(it1 != it2);
    it2 = list7.end();
    assert(it1 != it2);
    //--it2;
    assert(it1 != it2);
    ++it1;
    //assert(it1 == it2);
    assert(*it1 == 1);
    //assert(*(--it2) == 1);
}


TEST_MAIN()
