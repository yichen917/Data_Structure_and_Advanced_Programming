#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

class Ship{
private:
    string id, nation, name;
    int weight;
    bool danger;
public:
    Ship(ifstream &ShipFile);
    string getid();
    int getweight();
    bool getdanger();
    void print();
};

Ship::Ship(ifstream &ShipFile){
    string weight_str, danger_str;
    getline(ShipFile, id, ',');
    getline(ShipFile, weight_str, ',');
    getline(ShipFile, nation, ',');
    getline(ShipFile, name, ',');
    getline(ShipFile, danger_str, '\n');
    weight = stoi(weight_str);
    if(danger_str == "Y") danger = true;
    else danger = false;
}
void Ship::print(){
    cout << id << "," << weight << ","
    << nation << "," << name << "," ;
    if(danger==true) cout << "Y" <<endl;
    else cout << "N" <<endl;
}
string Ship::getid(){
    return id;
}
int Ship::getweight(){
    return weight;
}
bool Ship::getdanger(){
    return danger;
}
class Work{
protected:
    Ship* ship;
    string id, start_time, type, num1, num2;
    int w_time, ship_num;
public:
    Work();
    Work(string id, string start_time, string type, string num1, string num2, Ship** a, int ship_num);
    string getid();
    string getstart();
    int getw_time();
    string gettype();
    string getnum1();
    string getnum2();
    virtual void print();
    Ship* getship();
    void set_w_time(int);
};
Work::Work(){
    ship = NULL;
    id = start_time = type = num1 = num2="";
    ship_num = w_time =0;
}
Work::Work(string id, string start_time, string type, string num1, string num2, Ship** a, int ship_num):
    id(id),start_time(start_time),type(type), num1(num1), num2(num2), ship_num(ship_num){
        //cout << "Only ship hasnn't linked\n";
        //cout << "id = "<<id<<endl;
    for(int i=0;i<ship_num;i++){
        //cout << "start searching\n";
        //cout << "i= "<<i<<endl;
        //a[6]->print();
        //cout << "ship's id = "<< a[i]->getid()<<endl;
        if( a[i]->getid()==id ) {
          //  cout << "Find it!"<<endl;
            ship = a[i];
        }
    }
    w_time =0;
}
string Work::getid(){
    return id;
}
string Work::getstart(){
    return start_time;
}
int Work::getw_time(){
    return w_time;
}
string Work::gettype(){
    return type;
}
string Work::getnum1(){
    return num1;
}
string Work::getnum2(){
    return num2;
}
void Work::print(){
    cout << id << "," << start_time << "," << w_time << "," << type <<
    "," << num1 << "," << num2 <<endl;
}
Ship* Work::getship(){
    return ship;
}
void Work::set_w_time(int pdt_time){
    w_time = pdt_time;
}
class IN: public Work{
public:
    IN(string id, string start_time, string type, string num1, string num2, Ship** a, int ship_num);
    void print();
};
IN::IN(string id, string start_time, string type, string num1, string num2, Ship** a, int ship_num)
        :Work(id, start_time, type, num1, num2, a, ship_num){
}
void IN::print(){
    cout << id << "," << start_time << "," << w_time << "," << type <<
    "," << num1 << "," << num2 <<endl;
}
class OUT: public Work{
public:
    OUT(string id, string start_time, string type, string num1, string num2, Ship** a, int ship_num);
    void print();
};
OUT::OUT(string id, string start_time, string type, string num1, string num2, Ship** a, int ship_num)
        :Work(id, start_time, type, num1, num2, a, ship_num){
}
void OUT::print(){
    cout << id << "," << start_time << "," << w_time << "," << type <<
    "," << num1 << "," << num2 <<endl;
}
class Move: public Work{
public:
    Move(string id, string start_time, string type, string num1, string num2, Ship** a, int ship_num);
    void print();
};
Move::Move(string id, string start_time, string type, string num1, string num2, Ship** a, int ship_num)
        :Work(id, start_time, type, num1, num2, a, ship_num){
}
void Move::print(){
    cout << id << "," << start_time << "," << w_time << "," << type <<
    "," << num1 << "," << num2 <<endl;
}

static double m=0, a0=0, a1=0, a2=0, a3=0, a4=0, b0=0, b1=0, b2=0, b3=0, b4=0,
           c0=0, c1=0, c2=0, c3=0, c4=0, t1=0, t2=0, t3=0;
int predicted_time(Work* work)throw(logic_error);
int main(){
    string input;
    getline(cin,input,',');
    m = stod(input);
    getline(cin,input,',');
    a0 = stod(input);
    getline(cin,input,',');
    a1 = stod(input);
    getline(cin,input,',');
    a2 = stod(input);
    getline(cin,input,',');
    a3 = stod(input);
    getline(cin,input,',');
    a4 = stod(input);
    getline(cin,input,',');
    b0 = stod(input);
    getline(cin,input,',');
    b1 = stod(input);
    getline(cin,input,',');
    b2 = stod(input);
    getline(cin,input,',');
    b3 = stod(input);
    getline(cin,input,',');
    b4 = stod(input);
    getline(cin,input,',');
    c0 = stod(input);
    getline(cin,input,',');
    c1 = stod(input);
    getline(cin,input,',');
    c2 = stod(input);
    getline(cin,input,',');
    c3 = stod(input);
    getline(cin,input,',');
    c4 = stod(input);
    getline(cin,input,',');
    t1 = stod(input);
    getline(cin,input,',');
    t2 = stod(input);
    getline(cin,input,'\n');
    t3 = stod(input);
    ifstream ShipFile, WorkFile;
    string total = "";
    string id, start_time, type, one, two;
    string sfile_name, wfile_name;
    int w_time;
    int ship_num = 0, work_num =0;
    cin >> sfile_name >> wfile_name;
    WorkFile.open(wfile_name);
    ShipFile.open(sfile_name);
    // calculate the number of ships and works respectively
    while(!ShipFile.eof()){
        getline(ShipFile, total, '\n');
        ship_num++;
    }
    while(!WorkFile.eof()){
        getline(WorkFile, total, '\n');
        work_num++;
    }
    WorkFile.close();
    ShipFile.close();
    WorkFile.open(wfile_name);
    ShipFile.open(sfile_name);
    Ship* a[ship_num];
    Work* b[work_num];
    int num=0;
    // store the data of ships into Ship* array
    while(!ShipFile.eof()){
        for(int i=0;i<ship_num;i++) {
            a[i] = new Ship(ShipFile);
        }
    }
    // store the data of works into Work* array
    int pdt_time, invalid = 0;
    while(!WorkFile.eof()){
        getline(WorkFile, id, ',');
        getline(WorkFile, start_time, ',');
        getline(WorkFile, type, ',');
        getline(WorkFile, one, ',');
        getline(WorkFile, two, '\n');
        if(type=="I"){
            b[num] = new IN(id,start_time,type,one,two,a,ship_num);
        }else if(type=="O"){
            b[num] = new OUT(id,start_time,type,one,two,a,ship_num);
        }else if(type=="T"){
            b[num] = new Move(id,start_time,type,one,two,a,ship_num);
        }else{
            b[num] = new Work(id,start_time,type,one,two,a,ship_num);
        }
        try{
            pdt_time = predicted_time(b[num]);
            b[num]->set_w_time(pdt_time);
        }
        catch(logic_error e){
            invalid++;
            b[num]->set_w_time(-1);
        }
        num++;
    }
    for(int i=0;i<work_num;i++) {
        cout << b[i]->getw_time();
        if(i!=work_num-1) cout << ",";
    }
    cout << "\n"<<invalid;
    for(int i=0;i<work_num;i++) delete b[i];
    for(int i=0;i<ship_num;i++) delete a[i];
    WorkFile.close();
    ShipFile.close();
    return 0;
}

int predicted_time(Work* work)throw(logic_error){
    if( work->getstart()=="" || work->gettype()=="" || work->getnum1()=="" || work->getnum2()==""){
        throw logic_error("Invalid");
    }
    string type = work->gettype();
    int MovingDST=0, pdt_time=0;
    int ShipWeight= work->getship()->getweight();
    bool Danger = work->getship()->getdanger();
    bool Night;
    int start_time = stoi(work->getstart().substr(0,2))*60+stoi(work->getstart().substr(3,2));
    if(start_time>=1080 || start_time<=360) Night=true;
    else Night=false;
    if(type=="T"){
        int pier1 = stoi(work->getnum1()), pier2 = stoi( work->getnum2());
        if(pier1<pier2){
            int temp = pier1;
            pier1 = pier2;
            pier2 = temp;
        }
        int diff = pier1-pier2;
        if(diff%2==0)
            MovingDST = diff/2*t2;
        else{
            int newpier;
            if(pier1%2==0){
                newpier = pier1-1;
                diff = newpier-pier2;
            }
            else{
                newpier = pier2-1;
                diff = pier1-newpier;
            }
            MovingDST = diff/2*t2 + t3;
        }
    }else{
        int harbor = stoi(work->getnum1()), pier = stoi(work->getnum2());
        if( harbor==2)
            if(pier%2==0)
                pier = m-pier+2;
            else
                pier = m-pier;
        if( pier%2==0 )
            MovingDST = t1+t3+pier/2*t2;
        else
            MovingDST = t1+(pier+1)/2*t2;
    }
    if(work->gettype()=="I"){
        pdt_time = a0 + a1*MovingDST +a2*ShipWeight +  a3*Danger + a4*Night;
    }else if(work->gettype()=="O"){
        pdt_time = b0 + b1*MovingDST +b2*ShipWeight +  b3*Danger + b4*Night;
    }else{
        pdt_time = c0 + c1*MovingDST +c2*ShipWeight +  c3*Danger + c4*Night;
    }
    return pdt_time;
}
