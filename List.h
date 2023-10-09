#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    return (first==nullptr)&&(last==nullptr);
  };

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const{
    return leng;
  };

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    if(empty()){ // if the list is empty
      first = new Node{nullptr, nullptr, datum};
      last = first;
    }else{ // if the list is not empty
      Node* temp = new Node{first, nullptr, datum};
      first->prev = temp;
      first = temp;
    }
    leng++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    if(empty()){ // if the list is empty
      last = new Node{nullptr, nullptr, datum};
      first = last;
    }else{ // if the list is not empty
      Node* temp = new Node{nullptr, last, datum};
      last->next = temp;
      last = temp;
    }
    leng++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    assert(!empty());
    //if only one element
    if(leng == 1){
      delete first;
      first = nullptr;
      last = nullptr;
    }
    //if two or more
    else{
      Node* first_old = first;
      first = first->next;
      first->prev = nullptr;
      delete first_old;
    }
    leng--;
  };

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    assert(!empty());
    // if only one element
    if(leng == 1){
      delete last;
      first = nullptr;
      last = nullptr;
    // if two or more
    }else{
      Node* last_old = last;
      last = last->prev;
      last->next = nullptr;
      delete last_old;
    }
    leng--;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    // remove all
    Node* temp = first;
    if(temp == nullptr) return;
    while(temp->next!=nullptr){
      temp = temp->next;
      delete temp->prev;
    }
    delete temp;
    first = nullptr;
    last = nullptr;
    leng = 0;
  }

  List():first(nullptr), last(nullptr), leng(0){
  }

  List(const List<T>& list){
    first = nullptr;
    last = nullptr;
    leng = 0;
    copy_all(list);
  }

  List<T>& operator=(const List<T>& rhs){
//    if(*this == null){
//      first = nullptr;
//      last = nullptr;
//      leng = 0;
//    }
    //assert(empty());
    clear();
    copy_all(rhs);
    return *this;
  }

  ~List(){
    clear();
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    for(Iterator i = other.begin(); i!=other.end(); ++i){
      push_back(*i);
    }
  };

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

  int leng; // records the size of the link list

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.
    friend class List<T>;

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    Iterator& operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    T& operator*() const{
      assert(node_ptr);
      return node_ptr->datum;
    }
    
    bool operator==(const Iterator& i) const{
      return node_ptr == i.node_ptr;
    }

    bool operator!=(const Iterator& i) const{
      return node_ptr != i.node_ptr;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
  
    // construct an Iterator at a specific position
    Iterator(Node *p):
      node_ptr(p){};

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    return Iterator(nullptr);
  };

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
    assert(i.node_ptr);
    if(i==begin()){ // If it is the first element
      pop_front();
    }else if(i == Iterator(last)){
      pop_back();
    }else{
      i.node_ptr->prev->next = i.node_ptr->next;
      i.node_ptr->next->prev = i.node_ptr->prev;
      delete i.node_ptr;
      leng--;
    }
  };

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){
  //  assert(i.node_ptr);
    if(i==begin()){
      push_front(datum);
    }else{
      Node* newNode = new Node{i.node_ptr, i.node_ptr->prev, datum};
      i.node_ptr->prev->next = newNode;
      i.node_ptr->prev = newNode;
      leng++;
    }
  };

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
