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

int main(){
  srand(time(NULL));
  ULListStr list;
  for(int i = 0;i<100000;i++){
    if(i%2 == 1) list.push_back(to_string(i));
    else list.pop_front();
  }
  print (list);
  cout << list.size() << endl;
  return 0;
}
