#include <iostream>
#include "stackstring.h"
#include "ulliststr.h"

using namespace std;

void basic_test(){
  StackString st;
  for(int i = 0;i<10000;i++){
    st.push("Hello " + to_string(i));
  }
  cout << "Size: " << st.size() << endl;
  cout << "Is empty: " << (st.empty() ? "True" : "False") << endl;
}

int main(){
  basic_test();

  return 0;
}
