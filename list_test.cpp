#include <iostream>
#include "ulliststr.h"

using namespace std;

void print(const ULListStr& list){
  if(list.size() == 0){
    cout << "List is empty" << endl;
    return;
  }
  for(size_t i = 0;i<list.size()-1;i++){
    cout << list.get(i) << " -> ";
  }
  cout << list.get(list.size()-1) << endl;
}

void temp(ULListStr copy){
  print(copy);
}

void test_copy_constructor(){
  //Why do I need to take out the parenthesis?
  ULListStr list;
  //been tested with 100
  for(int i = 0;i<100;i++)
    list.push_back("Hello" + to_string(i));
  print(list);

  //simple copy test
  ULListStr copy_1(list);
  print(list);

  //calling copy by function
  temp(list);
}

void test_index_access_operator(){
  ULListStr list;
  for(int i = 0;i<10;i++) list.push_back("Hello "+to_string(i));

  //simple printing
  cout << list[4] << " == " << "Hello 4" << endl;

  //changing an element
  list[4] = "Bye 4";
  print(list);

  //checking for out of bounds
  /*
  list[11];
  list[0];
  ULListStr empty;
  cout << empty[0] << endl;
  */
}

void test_assignment_operator(){
  ULListStr list;
  for(int i = 0;i<10;i++) list.push_back("Hello " + to_string(i));
  //basic assignment
  ULListStr a = list;
  ULListStr b = list;
  cout << "a: ";
  print(a);
  cout << "b: ";
  print(b);

  //self-assignment
  a = a;
  cout << "a: ";
  print(a);

  //non-empty assignment
  ULListStr c;
  for(int i = 0;i<10;i++) c.push_back("Bye " + to_string(i));
  cout << "c: ";
  print(c);
  b = c;
  cout << "b: ";
  print(b);
  if(&b != &c){
    cout << "copy successful" << endl;
  }
}

void test_concat_operator(){
  ULListStr a;
  for(int i = 0;i<10;i++){
    a.push_back("Hello " + to_string(i));
  }
  cout << "a: ";
  print(a);
  ULListStr b;
  for(int i =0;i<10;i++){
    b.push_back("Bye " + to_string(i));
  }
  cout << "b: ";
  print(b);

  ULListStr c = a + b;
  cout << "c: ";
  print(c);
}

void test_remove_operator(){
  ULListStr list;
  for(int i = 0;i<10;i++) list.push_back("Hello " + to_string(i));
  cout << "list: ";
  print(list);

  //simple removal
  list-=5;
  cout << "list: ";
  print(list);

  //complete removal
  list-=5;
  cout << "list: ";
  print(list);

  // extra removal
  list-=5;
  cout << "list: ";
  print(list);
}

int main(){
  //test_copy_constructor();
  //test_index_access_operator();
  //test_assignment_operator();
  //test_concat_operator();
  test_remove_operator();
  return 0;
}
