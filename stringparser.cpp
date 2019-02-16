#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include "stackstring.h"

using namespace std;

class StringParser{

public:
  StringParser(string& data){
    valid = true;
    checkString(data);
    while(data.find(" ")!=string::npos){
      data.replace(data.find(" "), 1, "");
    }
    if(valid)
      parseData(data);
  }

  void checkString(string data){
    //check parenthesis
    int par_count = 0;
    for(char& c: data){
      if(c == '(') par_count ++;
      else if(c == ')') par_count --;
    }
    if(par_count){
      valid = false;
      return;
    }
    //simplify all group of > and < into >
    //simplify all strings to a single 'a'
    //simplify all ">a" into a single a
    //check if andy parenthesis are valid and if they are turn it into another 'a'
    StackString st;
    for(unsigned i = 0;i<data.length();i++){
      if(data[i] == ' ') continue;
      else if(data[i] >= 'a' && data[i] <= 'z'){
        while(data[i] >= 'a' && data[i] <= 'z') i++;
        //transform any ">a" into just a
        while(!st.empty() && st.top().compare(">") == 0) st.pop();
        st.push("a");
        i--;
      }
      else if(data[i] == '<' || data[i] == '>'){
        while(data[i] == '<' || data[i] == '>')i++;
        //multiple ">" means they were separated by a space
        while(!st.empty() && st.top().compare(">") == 0) st.pop();
        st.push(">");
        i--;
      }
      else if(data[i] == ')'){
        StackString parenthesis;
        while(st.top().compare("(") != 0) {
          parenthesis.push(st.top());
          st.pop();
        }
        st.pop();
        int stringCount = 0;
        int plusCount = 0;
        int minusCount = 0;
        int insertionCount = 0;
        while(!parenthesis.empty()){
          if(parenthesis.top().compare("a") == 0){
            //we reached 2 strings(means we reached a space in the middle)
            if(stringCount != plusCount && stringCount != minusCount){
              valid = false;
              return;
            }
            stringCount++;
          }
          else if(parenthesis.top().compare("+") == 0){
            //somehow we hit 2 operators in a row
            if(plusCount >= stringCount || minusCount >= 1){
              valid = false;
              return;
            }
            plusCount++;
          }
          else if(parenthesis.top().compare("-") == 0){
            //we either hit two - or we have too many operators
            if(plusCount >= stringCount || minusCount >= 1 || plusCount >= 1){
              valid = false;
              return;
            }
            minusCount++;
          }
          else{
            if(insertionCount >= stringCount){
              valid = false;
              return;
            }
            insertionCount++;
          }
          parenthesis.pop();
        }
        st.push("a");
      }
      else if(data[i] == '('){
        st.push("(");
      }
      else if(data[i] == '+'){
        st.push("+");
      }
      else if(data[i] == '-'){
        st.push("-");
      }
      else{
        valid = false;
        return;
      }
    }
    if(st.size() != 1 && st.size() != 2) valid = false;
    else if(st.size() == 1) valid = st.top().compare("a") == 0;
    else{
      valid = st.top().compare("a") == 0;
      st.pop();
      valid = valid && st.top().compare(">") == 0;
    }
  }

  string removeSubstr(string word, string substr){
    int index = word.find(substr);
    if(index >= 0 && index+substr.length() <= word.length()) word.replace(index, substr.length(), "");
    return word;
  }

  void parseData(const string& data){
    StackString st;
    //stack<string> st;
    for(unsigned i = 0;i<data.length();i++){
      if(data[i] >= 'a' && data[i] <= 'z'){
        //if it's a letter, start appending the whole word
        string word = "";
        while(i < data.length() && data[i] >= 'a' && data[i] <= 'z') word+=data[i++];
        i--;
        cout << word << " -> ";
        //if there are '<' or '>', remove it right away:
        //this eliminates some prefix complications
        while(!st.empty() && (st.top()[0] == '>' || st.top()[0] == '<')){
          string ops = st.top();
          st.pop();
          for(char& c: ops){
            if(c == '>') word.erase(0, 1);
            else word.erase(word.end()-1);
          }
        }
        cout << word << endl;
        st.push(word);
      }
      else if(data[i] == '>' || data[i] == '<'){
        //append a group of '>' and '<'
        string word = "";
        while(i < data.length() && (data[i] == '<' || data[i] == '>' || data[i] == ' ')){
          if(data[i] == ' '){
            i++;
            continue;
          }
          word+=data[i++];
        }
        i--;
        cout << word << endl;
        st.push(word);
      }
      else if(data[i] == ')'){
        string output = "";
        //op == 1 -> +
        //op == 2 -> -
        int op = 0;
        while(!st.empty()){
          string entity = st.top();
          st.pop();
          //check if it's a + or -
          if(entity[0] == '('){
            //if there are '<' or '>', remove it right away:
            //this eliminates some prefix complications
            while(!st.empty() && (st.top()[0] == '>' || st.top()[0] == '<')){
              string ops = st.top();
              st.pop();
              for(char& c: ops){
                if(c == '>') output.erase(0, 1);
                else output.erase(output.end()-1);
              }
            }
            st.push(output);
            break;
          }
          else if(entity[0] == '+') op = 1;
          else if(entity[0] == '-') op = 2;
          //entity must be a word by here
          else{
            //entity is rhs
            if(op == 0) output = entity; // change output to rhs
            //entity is lhs
            else{
              //op is + so entity + output
              if(op == 1) {
                output = entity + output;
              }
              //op is - so entity - output
              else{
                output = removeSubstr(entity, output);
              }
              op = 0;
            }
          }
        }
      }
      else{
        //if it's not a close parenthesis, it is some operator or '('
        //we will add '(' to find the stop point
        string toAdd = "";
        toAdd += data[i];
        cout << toAdd << endl;
        st.push(toAdd);
      }
    }
    while(!st.empty()){
      data_+=st.top();
      st.pop();
    }
  }

  string produceString(){
    if(!valid) return "Malformed";
    string copy = data_;
    return copy;
  }

private:
  string data_;
  bool valid;

};

int main(int argc, char *argv[]){
  if(argc != 3){
    cout << "incorrect amount of arguments" << endl;
    return -1;
  }
  ifstream input;
  ofstream output;
  input.open(argv[1]);
  output.open(argv[2]);
  string line;
  while(getline(input, line)){
    StringParser stparse(line);
    output << stparse.produceString() << endl;
  }
  return 0;
}
