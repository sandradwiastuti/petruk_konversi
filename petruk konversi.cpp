#include <bits/stdc++.h>
using namespace std;


bool check(char ch, vector<char> range);


vector<string> convertToInfix(string input);


string removeWhitespace(string str);

int main(){
    vector<string> infix;

    string input;
    getline(cin,input);

    infix = convertToInfix(removeWhitespace(input));

    vector<string>::iterator it = infix.begin();

   
    while(it != infix.end()){
        cout << *it << " ";
        it++;
    }
    cout << endl;
}

bool check(char ch, vector<char> range){
    vector<char>::iterator it;
    it = find(range.begin(),range.end(),ch);

    
    return it-range.begin() < (long int) range.size();
}

string removeWhitespace(string str){
   
    vector<char> bilangan = {'1','2','3','4','5','6','7','8','9','0'};
    vector<char> op = {'+','*','/','%'};
    vector<char> kurung = {'(',')'};

    string::iterator i = str.begin();
    string result;

    while(i != str.end()){
        
        if(check(*i,bilangan)){
               result.push_back(*i);    
        
        }else if(check(*i,op) || check(*i,kurung)){
            result.push_back(*i);
        
        }else if(*i == '-'){
            result.push_back(*i);
        }

        i++; 
    }

    return result;
}

vector<string> convertToInfix(string input){
   
    vector<char> bilangan = {'1','2','3','4','5','6','7','8','9','0'};
    vector<char> op = {'+','*','/','%'};
    vector<char> kurung = {'(',')'};

    vector<string> infix;
    string temp;
    string::iterator i = input.begin();

   
    while(i != input.end()){
        
        if(check(*i,bilangan)){
           
            temp.push_back(*i);
            
            if(!check(*(i+1),bilangan)){
                infix.push_back(temp);
                temp.clear();
            }
       
        }else if(check(*i,op) || check(*i,kurung)){
            
            temp.push_back(*i);
            infix.push_back(temp);
            temp.clear();
        
        }else if(*i == '-'){
            
            if(check(*(i-1),op) || *(i-1) == '(' || (i == input.begin() && *(i+1) == '(')){
                
                infix.push_back("-1");
                infix.push_back("*");
            
            }else if((check(*(i+1),bilangan) && check(*(i-1),op)) || i == input.begin()){
               
                temp.push_back('-');
            }else{
                
                infix.push_back("-");
            }
        }

        i++; 
    }

    return infix;
}
int checkPrecedence(string op){
    int result = 0;
    if(op == "%" || op == "*" || op == "/"){
        result = 3;
    }else if(op == "+" || op == "-"){
        result = 4;
    }
    return result;
}

vector<string> convertToPostfix(vector<string> infix){
    vector<string> op = {"+","-","*","/","%"};
    vector<string> kurung = {"(",")"};

    stack<string> result;
    vector<string> postfix;
    vector<string>::iterator i = infix.begin();

    while(i != infix.end()){
        if(*i == "("){
            result.push(*i);
        }else if(*i == ")"){
            while(!result.empty() && result.top() != "("){
                postfix.push_back(result.top());
                result.pop();
            }
            result.pop();
        }else if(checkString(*i,op)){
            if(result.empty() || result.top() == "("){
                result.push(*i);
            }else{
                while(!result.empty() && result.top() != "(" && checkPrecedence(*i) >= checkPrecedence(result.top())){
                    postfix.push_back(result.top());
                    result.pop();
                }
                result.push(*i);
            }
        }else{
            postfix.push_back(*i);
        }

        i++;
    }

    while(!result.empty()){
        postfix.push_back(result.top());
        result.pop();
    }

