#include <iostream>
#include <stack>
#include <string>

using namespace std;

class StringParser{

public:
  StringParser(const string& data){
    parseData(data);
  }

  string removeSubstr(string word, string substr){
    int index = word.find(substr);
    if(index >= 0 && index+substr.length() <= word.length()) word.replace(index, substr.length(), "");
    return word;
  }

  void parseData(const string& data){
    stack<string> st;
    for(unsigned i = 0;i<data.length();i++){
      if(data[i] == ' ') continue;
      else if(data[i] >= 'a' && data[i] <= 'z'){
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
    string copy = data_;
    return copy;
  }

private:
  string data_;
  bool valid;

};

int main(int argc, char *argv[]){

  StringParser sp("<>((<<mario + >>zelda)- ><samus)"); //
  cout << sp.produceString() << endl;
  return 0;
}
