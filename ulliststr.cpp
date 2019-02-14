#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;

}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(NULL == ptr){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(NULL == ptr){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(NULL == ptr){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

void ULListStr::push_back(const std::string& val){
  //If tail is NULL, it is empty, so create a new head and tail
	if(tail_ == NULL){
    Item* toAdd = new Item();
    this->head_ = toAdd;
    this->tail_ = toAdd;
  }
  //grab tail
  Item* tail = this->tail_;
  //if the tail's last is maxed out, we need to create a new tail
  if(tail->last >= (size_t)10){
    //the new tail
    Item* toAdd = new Item();
    //fix pointers of next and prev
    tail->next = toAdd;
    toAdd->prev = tail;
    //set the actual tail to tail
    this->tail_ = toAdd;
    tail = tail->next;
  }
  //by the time we get here, the value can be added to last on tail
  tail->val[(tail->last)++] = val;
  //must increase size
  (this->size_)++;
}

void ULListStr::push_front(const std::string& val){
  //if the head is null, we can assume there is not head or tail so create one
  if(this->head_ == NULL){
    Item* toAdd = new Item();
    this->head_ = toAdd;
    this->tail_ = toAdd;
  }
  //grab the head
  Item* head = this->head_;
  if(head->first == (size_t)0){
    //if both first and last are zero,
    //it's a newly initialized Item, so we can push back like normal
    if(head->last == (size_t)0){
      push_back(val);
      return;
    }
    //otherwise, we have no space to push front, so we have to create a new head
    else{
      //the new head
      Item* toAdd = new Item();
      //fix pointers next and prev
      head->prev = toAdd;
      toAdd->next = head;
      //set the head
      this->head_ = toAdd;
      head = toAdd;
      //This implementation makes the new head node have the first at last,
      //because that way when we only do push_front's, we can get more constant times
      head->first = (size_t)10;
      head->last = (size_t)10;
    }
  }
  //we can always move the value of first and then add it
  head->val[--(head->first)] = val;
  //size is guarunteed to increse
  (this->size_)++;
}

void ULListStr::pop_back(){
  //does nothing on empty list
  if(this->size_ == 0) return;
  //simply ignore the last element and move the pointer of last back one
  Item* tail = this->tail_;
  tail->last-=1;
  //this is to delete the string once it goes out of scope (I know it's unnecessary, but to be extra safe)
  std::string toDelete = "";
  toDelete.swap(tail->val[tail->last]);
  //if the tail item has the same first and last, we can delete the tail
  if(tail->first == tail->last){
    //this means the size is 1 and we just deleted the last one
    //we can delete the entire list
    if(this->head_ == this->tail_){
      this->head_ = NULL;
      this->tail_ = NULL;
    }
    //other wise, we just need to delete the current tail because it's the last one
    else{
      this->tail_ = tail->prev;
      this->tail_->next = NULL;
    }
    delete tail;
  }
  //siez will guaruntee to decrease
  this->size_--;
}

void ULListStr::pop_front(){
  //empty list does nothing
  if(this->size_ == 0) return;
  //grab head
  Item* head = this->head_;
  //this swaps the string data so that it can go out of scope (unnecessary but just in case)
  std::string toDelete = "";
  toDelete.swap(head->val[head->first]);
  //after deletion, we move the pointer
  head->first += 1;
  //if first and last are the same, the current node can be deleted
  if(head->first == head->last){
    //this means the size is one so you can delete the list
    if(this->head_ == this->tail_){
      this->head_ = NULL;
      this->tail_ = NULL;
    }
    //we change the head of the list
    else{
      this->head_ = head->next;
      this->head_->prev = NULL;
    }
    delete head;
  }
  this->size_--;
}

std::string const & ULListStr::front() const{
  //not necessary, but returns NULL
  if(this->size_ == 0) return NULL;
  //the value of the first of head
  return this->head_->val[this->head_->first];
}

std::string const & ULListStr::back() const{
  //not necessary, but returns NULL
  if(this->size_ == 0) return NULL;
  //the value of last of tail
  return this->tail_->val[this->tail_->last-1];
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  //starts from head
  Item* toLook = this->head_;
  //iter will keep track of the elements after traversing through the list
  size_t iter = loc;
  //while is set to true because break was more intuitive to implement
  while(true){
    //if the node is empty, loc is pointing over the size
    if(toLook == NULL) return NULL;
    //if the numOfItems is 0, we return NULL (although my implementation never allows this, it deletes it)
    size_t numItems = toLook->last - toLook->first;
    if(numItems == 0) return NULL;
    //else if the iter index goes past the numItems of the current node,
    //we subtract that max number from iter and move to the next Item
    else if(numItems <= iter){
      iter-=numItems;
      toLook = toLook->next;
    }
    else{
      //we've finally reached the iter size that isn't out of bounds and is within the range of the current Item
      break;
    }
  }
  //first + iter index of val because first is not always 0
  return &(toLook->val[toLook->first+iter]);
}

//hw3

ULListStr::ULListStr (const ULListStr& other){
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
  this->appendContents(other);
}

std::string & ULListStr::operator[] (size_t loc){
  return this->get(loc);
}

std::string const & ULListStr::operator[] (size_t loc) const{
  /*
  //if it doesn't exist, return NULL
  if(this->head_ == NULL) return "";
  //if loc is out of range return NULL
  if(loc < 0 || loc >= this->size()) return "";
  //Grab the node and the num of elements in the node
  Item* node = this->head_;
  size_t numItems = node->last - node->first;
  //cycle through the nodes until loc is within the numItems in node
  while(loc >= numItems){
    loc -= numItems;
    node = node->next;
    numItems = node->last - node->first;
  }
  //loc is now within the node
  return &(node->val[node->first + loc]);
  */
  return this->get(loc);
}

ULListStr& ULListStr::operator= (const ULListStr& other){
  //check if other is the same as this
  if(this != &other){
    //if it isn't delete data of current ULListStr
    while(this->size() > 0) this->pop_back();
    //copy data
    this->head_ = other.head_;
    this->tail_ = other.tail_;
    this->size_ = other.size_;
  }
  return *this;
}

void ULListStr::appendContents(const ULListStr& other){
  //if size is 0, don't do anything
  if(other.size_ == 0) return;
  //grab the node and the index in order to grab the value
  Item* node = other.head_;
  size_t index = node->first;
  while(node != NULL){
    if(index >= node->last){
      //we reached out of bounds, so we move the next node
      node = node->next;
      //next node might be null
      if(node != NULL) index = node->first;
    }else{
      //append the index at the end
      this->push_back(node->val[index++]);
    }
  }
}

ULListStr ULListStr::operator+ (const ULListStr& other) const{
  ULListStr ret;

  //copy the contents of this
  Item* t_node = this->head_;
  size_t index = t_node->first;
  while(t_node != NULL){
    ret.push_back(t_node->val[index++]);
    if(index == t_node->last){
      if(t_node->next == NULL) break;
      t_node = t_node->next;
      index = t_node->first;
    }
  }
  //copy the contents of other
  Item* o_node = other.head_;
  size_t o_index = o_node->first;
  while(o_node != NULL){
    ret.push_back(o_node->val[o_index++]);
    if(o_index == o_node->last){
      if(o_node->next == NULL) break;
      o_node = o_node->next;
      o_index = o_node->first;
    }
  }
  return ret;
}

ULListStr& ULListStr::operator-= (size_t num){
  for(size_t i = 0;i<num;i++) this->pop_back();
  return *this;
}
