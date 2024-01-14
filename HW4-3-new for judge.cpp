#include <iostream>
#include <stack>
#include <string>
#include <vector>
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

class Poly{
private:
    //string order[4];
    int numerator[4]; // stored in the order of a,b,c,d,d=num
    int denominator[4];
    string added;
public:
    Poly();
    Poly(const string input);
    //Poly(Poly &p);
    void set_numerator(const int number, const string variable);
    void set_denominator(const int number, const string variable);
    void add_added(const string variable);
    string g_added();
    int g_numerator(const string variable);
    int g_denominator(const string variable);
    void operator=(Poly after);
    Poly operator+(Poly after);
    Poly operator-(Poly after);
    Poly operator*(Poly after);
    Poly operator/(Poly after);
    void print();
};
Poly::Poly(){
    for(int i=0;i<4;i++){
        numerator[i] = 0;
        denominator[i] = 1;
    }
    added = "";
}
Poly::Poly(const string input){
    for(int i=0;i<4;i++){
        numerator[i] = 0;
        denominator[i] = 1;
    }
    added = "";
    if (input == "a"){
        numerator[0] = 1;
        added += "a";
    }else if (input=="b"){
        numerator[1] = 1;
        added += "b";
    }else if (input=="c"){
        numerator[2] = 1;
        added += "c";
    }else{
        numerator[3] = stoi(input);
        added += "d";
    }
}

void Poly::operator=(Poly after){
    this->added = after.g_added();
    for(int i=0;i<4;i++){
        string variable;
        if (i==0) variable = "a";
        else if (i==1) variable = "b";
        else if (i==2) variable = "c";
        else variable = "d";
        this->numerator[i] = after.g_numerator(variable);
        this->denominator[i] = after.g_denominator(variable);
    }
}

void Poly::set_numerator(const int number, const string variable){
    if (variable=="a")
        numerator[0] = number;
    else if (variable=="b")
        numerator[1] = number;
    else if (variable=="c")
        numerator[2] = number;
    else
        numerator[3] = number;
    if (added.find(variable)==string::npos)
        added += variable;
}
void Poly::set_denominator(const int number, const string variable){
    if (variable=="a")
        denominator[0] = number;
    else if (variable=="b")
        denominator[1] = number;
    else if (variable=="c")
        denominator[2] = number;
    else
        denominator[3] = number;
    if (added.find(variable)==string::npos)
        added += variable;
}
void Poly::add_added(const string variable){
    added += variable;
}
string Poly::g_added(){
    return added;
}
int Poly::g_numerator(const string variable){
    if (variable=="a")
        return numerator[0];
    else if (variable=="b")
        return numerator[1];
    else if( variable=="c")
        return numerator[2];
    else
        return numerator[3];
}
int Poly::g_denominator(const string variable){
    if (variable=="a")
        return denominator[0];
    else if( variable=="b")
        return denominator[1];
    else if (variable=="c")
        return denominator[2];
    else
        return denominator[3];
}
Poly Poly::operator+(Poly after){
    Poly newPoly ;
    newPoly = *this;
    int after_numerator, after_denominator, now_numerator, now_denominator;
    string variable;
    //cout << "this's added = " << this->g_added()<<endl;
    //cout << "after's added = " << after.g_added()<<endl;
    if  ( newPoly.g_added().find(after.g_added())==string::npos )
        newPoly.add_added(after.g_added());
    if ( after.g_added().length() == 1 ){
        variable = after.g_added();
        after_numerator = after.g_numerator(variable);
        after_denominator = after.g_denominator(variable);
    }//else
        //cout << "Something is wrong when added two Poly\n";
    //cout << "after numerator = " << after_numerator <<endl;
    //cout << "after denominator = " << after_denominator <<endl;
    now_numerator = this->g_numerator(variable);
    now_denominator = this->g_denominator(variable);
    //cout << "now numerator = " << now_numerator <<endl;
    //cout << "now denominator = " << now_denominator <<endl;
    int new_num, new_den;
    if( now_numerator==0){
        new_num = after_numerator;
        new_den = after_denominator;
    }else if (now_denominator==after_denominator){
        new_num = now_numerator+after_numerator;
        new_den = now_denominator;
    }else if (now_denominator==1 && after_denominator!=1){// consider integer+fraction
        new_num = now_denominator*after_denominator+after_numerator;
        new_den = after_denominator;
    }else if (now_denominator!=1 && after_denominator==1){
        new_num = after_numerator*now_denominator+now_numerator;
        new_den = now_denominator;
    }else{
        new_num = after_numerator*now_denominator+now_numerator*after_denominator;
        new_den = after_numerator*now_denominator;
        int start = 0;
        if (new_num > new_den) //可能需要約分
            start = new_den;
        else start = new_num;
        for(int i=start;i>1;i--)
            if (new_num%i==0 && new_den%i==0){
                new_num /= i;
                new_den /= i;
            }
    }
    //cout << "new numerator = " << new_num <<endl;
    //cout << "new denominator = " << new_den <<endl;
    newPoly.set_numerator(new_num,variable);
    newPoly.set_denominator(new_den,variable);
    //cout << "new added = " << newPoly.g_added()<<endl;
    //cout << "this's added = " << this->g_added()<<endl;
    return newPoly;
}
Poly Poly::operator-(Poly after){
    Poly new_after = after;
    string variable = after.g_added();
    int ori_num = after.g_numerator(variable);
    new_after.set_numerator(-ori_num,variable);
    return *this+new_after;
}
Poly Poly::operator*(Poly after){
    Poly newPoly;
    if ( after.g_added()== "d"){ // 一堆變數 * 數字
        newPoly = *this;
        int mul_num = after.g_numerator("d");
        int mul_den = after.g_denominator("d");
        if (mul_den==1){
            for(int i=0;i<newPoly.g_added().length();i++){
                const char* v_char = &newPoly.g_added()[i];
                const string variable(v_char);
                int ori_num = newPoly.g_numerator(variable);
                newPoly.set_numerator(ori_num*mul_num,variable);
                int new_num = newPoly.g_numerator(variable);
                int new_den = newPoly.g_denominator(variable);
                int start = 0;
                bool need = false;
                if (new_num > new_den) //需要約分
                    start = new_den;
                else start = new_num;
                for(int i=start;i>1;i--){
                    if (new_num%i==0 && new_den%i==0){
                        need = true;
                        new_num /= i;
                        new_den /= i;
                    }
                }
                if (need){
                    newPoly.set_numerator(new_num,variable);
                    newPoly.set_denominator(new_den,variable);
                }
            }

        }//else{
            //cout << "sth wrong when multiply two Poly"<<endl;
        //}
    }else{ // 數字*變數
        newPoly = after;
        string variable = after.g_added();
        int mul_num = this->g_numerator("d");
        int mul_den = this->g_denominator("d");
        //cout << "mul num = " << mul_num <<endl;
        //cout << "mul den = " << mul_den <<endl;
        newPoly.set_numerator(mul_num,variable);
        newPoly.set_denominator(mul_den,variable);
    }
    return newPoly;
}
Poly Poly::operator/(Poly after){
    Poly newPoly = *this;
    int division = after.g_numerator("d");
//變數/數字
    string this_var = this->g_added();
    for(int i=0;i<this_var.length();i++){
        string cur_var = this_var.substr(i,1);
        if (cur_var == "d"){
            newPoly.set_numerator(this->g_numerator("d")/division,"d");
        }else{
            newPoly.set_denominator(this->g_denominator(cur_var)*division,cur_var);
            int new_num = newPoly.g_numerator(cur_var);
            int new_den = newPoly.g_denominator(cur_var);
            int start = 0;
            bool need = false;
            if (new_num > new_den) //需要約分
                start = new_den;
            else start = new_num;
            for(int i=start;i>1;i--){
                if (new_num%i==0 && new_den%i==0){
                    need = true;
                    new_num /= i;
                    new_den /= i;
                }
            }
            if (need){
                newPoly.set_numerator(new_num,cur_var);
                newPoly.set_denominator(new_den,cur_var);
            }
        }
    }
    return newPoly;
}
void Poly::print(){
    for(int i=0;i<added.length();i++){
        int index;
        if (added[i]=='a') index = 0;
        else if (added[i]=='b') index = 1;
        else if (added[i]=='c') index = 2;
        else index = 3;
        if (numerator[index]==0)
            continue;
        else{
            if (i>0 && numerator[index]>0)
                cout << "+";

            if (added[i]=='d'){
                cout << numerator[index];
                if(denominator[index]!=1)
                    cout << "/" << denominator[index];
            }else{
                if (numerator[index]==1)
                    cout << added[i];
                else if (numerator[index]==-1)
                    cout << "-" << added[i];
                else{
                    cout << numerator[index] << added[i];
                }
                if (denominator[index]!=1)
                    cout << "/" << denominator[index];
            }
        }
    }
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

Poly calculate(Poly a1, Poly a2, operators ope){
    string ope1 = ope.get_ope();
    if( ope1=="+") return a1+a2;
    else if (ope1=="-") return a1-a2;
    else if (ope1=="*") return a1*a2;
    else if (ope1=="/") return a1/a2;
}
int main(){
    stack<Poly> poly_stack;
    stack<operators> ope_stack;
    string equation;
    cin >> equation;
    int pre_cut = 0;
    Poly current;
    char ope;
    for(int i=0; i<equation.length(); i++){
        ope = equation[i];
        if (ope== 42 or ope==43 or ope==45 or ope==47){
            current = Poly(equation.substr(pre_cut, i-pre_cut));
            poly_stack.push(current);
            //cout << "The top in num stack is " ;
            //poly_stack.top().print();
            //cout << endl;

            operators putIn(ope), top;
            if ( ope_stack.size()!=0){
                top = ope_stack.top();
                if ( putIn > top )
                    ope_stack.push(putIn);
                else{
                    while( ope_stack.size()!=0 && (ope_stack.top()>putIn or ope_stack.top()==putIn) ){
                        Poly poly2 = poly_stack.top();
                        poly_stack.pop();
                        Poly poly1 = poly_stack.top();
                        poly_stack.pop();
                        operators cal = ope_stack.top();
                        ope_stack.pop();
                        //cout << "Calculate " <<endl;
                        Poly new_poly = calculate(poly1,poly2,cal);
                        poly_stack.push(new_poly);
                        //poly_stack.top().print();
                        //cout << "is pushed\n";
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
            if ( poly_stack.size()==2 ){
                Poly temp = poly_stack.top();
                poly_stack.pop();
                poly_stack.top().print();
                cout << "," ;
                temp.print();
                cout << endl;
                poly_stack.push(temp);
            }
            else if ( poly_stack.size()==1){
                poly_stack.top().print();
                cout << endl;
            }
            //cout << "-----------------------\n";
        }
        if (i==equation.length()-1){
            current = Poly( equation.substr(pre_cut, i-pre_cut+1));
            poly_stack.push(current);
            //cout << "The top in num stack is " ;
            //poly_stack.top().print();
        }
    }
    while( ope_stack.size()!=0 ){
        Poly poly2 = poly_stack.top();
        poly_stack.pop();
        Poly poly1 = poly_stack.top();
        poly_stack.pop();
        operators cal = ope_stack.top();
        ope_stack.pop();
        //cout << "Calculate " ;
        //poly1.print() ;
        //cout << cal.get_ope() ;
        //poly2.print();
        Poly new_poly = calculate(poly1,poly2,cal);
        poly_stack.push(new_poly);
        //poly_stack.top().print();
        //cout << "is pushed\n";
    }
    poly_stack.top().print();
    return 0;
}
