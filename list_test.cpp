#include <iostream>
#include "ulliststr.h"

using namespace std;

void print(const ULListStr& list){
  if(list.size() == 0){
    cout << "List is empty" << endl;
    return;
  }
  for(size_t i = 0;i<list.size()-1;i++){
    cout << list[i] << " -> ";
  }
  cout << list[list.size()-1] << endl;
}

void temp(ULListStr copy){
  print(copy);
}

void test_copy_constructor(){
  //Why do I need to take out the parenthesis?
  ULListStr list;
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
  
}

int main(){
  test_copy_constructor();
  return 0;
}
