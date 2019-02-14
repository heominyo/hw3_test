#include "stackstring.h"

StackString::StackString(){

}

StackString::~StackString(){
  
}

bool StackString::empty() const{
  return (this->list_).size() == 0;
}

size_t StackString::size() const{
  return (this->list_).size();
}

void StackString::push(const std::string& val){
  (this->list_).push_back(val);
}

const std::string& StackString::top() const{
  return (this->list_).get(0);
}

void StackString::pop(){
  (this->list_).pop_front();
}
