/*
This assignment primarily involves stack data structure and implementation.

Question:
In this question, you will implement the concept of a stack for arithmetic calculations. 
You will be given a mathematical expression containing addition, subtraction, multiplication, and division operations on integers, such as 3 + 5 * 2 - 3 / 2. 
Use a stack to calculate the result. (Note: Division should only keep the quotient.)
*/

#include <iostream>
#include <stack>
using namespace std;

class operators{
private:
    string ope;
public:
    operators();
    operators(const string);
    operators(const char);
    string get_ope();
    void print();
    friend bool operator>(const operators, const operators);
    friend bool operator==(const operators, const operators);
    friend bool operator<(const operators, const operators);
};
operators::operators(){
    ope = "";
}
operators::operators(const string input){
    ope = input;
}
operators::operators(const char input){
    ope = input;
}
void operators::print(){
    cout << ope << endl;
}
string operators::get_ope(){
    return ope;
}
bool operator>(const operators x1, const operators x2){
    bool x1_prior, x2_prior;
    if ( x1.ope=="+" or x1.ope=="-" ) x1_prior = false;
    else x1_prior = true;
    if ( x2.ope=="+" or x2.ope=="-" ) x2_prior = false;
    else x2_prior = true;
    if ( x1_prior > x2_prior ) return true;
    else return false;
}

bool operator==(const operators x1, const operators x2){
    bool x1_prior, x2_prior;
    if ( x1.ope=="+" or x1.ope=="-" ) x1_prior = false;
    else x1_prior = true;
    if ( x2.ope=="+" or x2.ope=="-" ) x2_prior = false;
    else x2_prior = true;
    if ( x1_prior == x2_prior ) return true;
    else return false;
}

bool operator<(const operators x1, const operators x2){
    if ( x1>x2 or x1==x2 )return false;
    else return true;
}

int calculate(const int a1, const int a2, operators ope){
    string ope1 = ope.get_ope();
    if( ope1=="+") return a1+a2;
    else if (ope1=="-") return a1-a2;
    else if (ope1=="*") return a1*a2;
    else if (ope1=="/") return a1/a2;
}
int main(){
    stack<int> num_stack;
    stack<operators> ope_stack;
    string equation;
    cin >> equation;
    int pre_cut = 0, num;
    char ope;
    for(int i=0; i<equation.length(); i++){
        ope = equation[i];
        if (ope== 42 or ope==43 or ope==45 or ope==47){
            num = stoi( equation.substr(pre_cut, i-pre_cut));
            num_stack.push(num);
            // cout << "The top in num stack is " << num_stack.top() <<endl;

            operators putIn(ope), top;
            if ( ope_stack.size()!=0){
                top = ope_stack.top();
                if ( putIn > top )
                    ope_stack.push(putIn);
                else{
                    while( ope_stack.size()!=0 && (ope_stack.top()>putIn or ope_stack.top()==putIn) ){
                        int num2 = num_stack.top();
                        num_stack.pop();
                        int num1 = num_stack.top();
                        num_stack.pop();
                        operators cal = ope_stack.top();
                        ope_stack.pop();
                        // cout << "Calculate " << num1 << cal.get_ope() << num2 <<endl;
                        int new_num = calculate(num1,num2,cal);
                        num_stack.push(new_num);
                        // cout << num_stack.top() << "is pushed\n";
                    }
                    ope_stack.push(putIn);
                }
            }else {
                ope_stack.push(putIn);
            }

            //cout << "The top in ope stack is " ;
            //ope_stack.top().print();
            pre_cut = i+1;

            //cout << "--------------------------" <<endl;
            if ( num_stack.size()==2 ){
                int temp = num_stack.top();
                num_stack.pop();
                cout << num_stack.top() << "," << temp <<endl;
                num_stack.push(temp);
            }
            else if ( num_stack.size()==1)
                cout << num_stack.top()<<endl;

            //cout << "\n-----------------------\n";
        }
        if (i==equation.length()-1){
            num = stoi( equation.substr(pre_cut, i-pre_cut+1));
            num_stack.push(num);
            //cout << "The top in num stack is " << num_stack.top() <<endl;
        }
    }
    while( ope_stack.size()!=0 ){
        int num2 = num_stack.top();
        num_stack.pop();
        int num1 = num_stack.top();
        num_stack.pop();
        operators cal = ope_stack.top();
        ope_stack.pop();
        //cout << "Calculate " << num1 << cal.get_ope() << num2 <<endl;
        int new_num = calculate(num1,num2,cal);
        num_stack.push(new_num);
        //cout << num_stack.top() << "is pushed\n";
    }
    cout << num_stack.top();
    return 0;
}
