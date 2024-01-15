/* 
This assignment primarily involves writing classes and utilizing parent and child classes to make the development process more efficient.

Question:
This assignment involves writing a scheduling program for the arrival and departure of ships at a port. 
It is known that the port has two ports for navigating ships, m piers available for docking within the port, s registered ships, and n ship movement jobs in a day.
Two scheduling algorithms are implemented:  ERT (Earliest Ready Time First) and SPT (Shortest Processing Time First).

Goal: Given the info of ships and jobs, the program should calculate the total delayed time under both algorithms.

*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Ship{
private:
    string id, nation, name;
    int weight;
    bool danger;
public:
    Ship(ifstream &ShipFile);
    string getid();
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
class Work{
protected:
    Ship* ship;
    string id, start_time, type;
    int w_time, num1, num2, ship_num;
public:
    Work();
    Work(string id, string start_time, int w_time, string type, int num1, int num2, Ship** a, int ship_num);
    string getid();
    string getstart();
    int getw_time();
    string gettype();
    int getnum1();
    int getnum2();
    virtual void print()=0;
    Ship* getship();
};
Work::Work(){
    ship = NULL;
    id = start_time = type = "";
    w_time=0, num1=0, num2=0, ship_num=0;
}
Work::Work(string id, string start_time, int w_time, string type, int num1, int num2, Ship** a, int ship_num):
    id(id),start_time(start_time),w_time(w_time),type(type), num1(num1), num2(num2), ship_num(ship_num){
    for(int i=0;i<ship_num;i++)
        if( a[i]->getid()==id ) ship = a[i];
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
int Work::getnum1(){
    return num1;
}
int Work::getnum2(){
    return num2;
}
void Work::print(){
    cout << id << "," << start_time << "," << w_time << "," << type <<
    "," << num1 << "," << num2 <<endl;
}
Ship* Work::getship(){
    return ship;
}
class IN: public Work{
public:
    IN(string id, string start_time, int w_time, string type, int num1, int num2, Ship** a, int ship_num);
    void print();
};
IN::IN(string id, string start_time, int w_time, string type, int num1, int num2, Ship** a, int ship_num)
        :Work(id, start_time, w_time, type, num1, num2, a, ship_num){
}
void IN::print(){
    cout << id << "," << start_time << "," << w_time << "," << type <<
    "," << num1 << "," << num2 <<endl;
}
class OUT: public Work{
public:
    OUT(string id, string start_time, int w_time, string type, int num1, int num2, Ship** a, int ship_num);
    void print();
};
OUT::OUT(string id, string start_time, int w_time, string type, int num1, int num2, Ship** a, int ship_num)
        :Work(id, start_time, w_time, type, num1, num2, a, ship_num){
}
void OUT::print(){
    cout << id << "," << start_time << "," << w_time << "," << type <<
    "," << num1 << "," << num2 <<endl;
}
class Move: public Work{
public:
    Move(string id, string start_time, int w_time, string type, int num1, int num2, Ship** a, int ship_num);
    void print();
};
Move::Move(string id, string start_time, int w_time, string type, int num1, int num2, Ship** a, int ship_num)
        :Work(id, start_time, w_time, type, num1, num2, a, ship_num){
}
void Move::print(){
    cout << id << "," << start_time << "," << w_time << "," << type <<
    "," << num1 << "," << num2 <<endl;
}

int ERT_t(Work**, int, Ship**, int); //to calculate the total time of ERT
int SPT_t(Work**, int, Ship**, int); //to calculate the total time of SPT
void work_reorder_ERT(Work**, int, Ship**, int); //reorder the works by rules of ERT
void work_reorder_SPT(Work**, int, Ship**, int); //reorder the works by rules of SPT
int waiting_time(Work**, int); //calculate the delay time of the passed Work** array

int main(){
    ifstream ShipFile, WorkFile;
    string total = "";
    string id, start_time, w_time_str, type, one, two;
    string sfile_name, wfile_name;
    int w_time, pier_num;
    int ship_num = 0, work_num =0;
    cin >> pier_num >> sfile_name >> wfile_name;
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
        for(int i=0;i<ship_num;i++) a[i] = new Ship(ShipFile);
    }
    // store the data of works into Work* array
    while(!WorkFile.eof()){
        getline(WorkFile, id, ',');
        getline(WorkFile, start_time, ',');
        getline(WorkFile, w_time_str, ',');
        w_time = stoi(w_time_str);
        getline(WorkFile, type, ',');
        getline(WorkFile, one, ',');
        getline(WorkFile, two, '\n');
        if(type=="I"){
            int harbor, pier;
            harbor = stoi(one);
            pier = stoi(two);
            b[num] = new IN(id,start_time,w_time,type,harbor,pier,a,ship_num);
        }else if(type=="O"){
            int harbor, pier;
            harbor = stoi(one);
            pier = stoi(two);
            b[num] = new OUT(id,start_time,w_time,type,harbor,pier,a,ship_num);
        }else{
            int pier1, pier2;
            pier1 = stoi(one);
            pier2 = stoi(two);
            b[num] = new Move(id,start_time,w_time,type,pier1,pier2,a,ship_num);
        }
        num++;
    }
    // cout the delay time of ERT and SPT method respectively
    cout << ERT_t(b, work_num, a, ship_num) << " " << SPT_t(b, work_num, a, ship_num);
    for(int i=0;i<work_num;i++) delete b[i];
    for(int i=0;i<ship_num;i++) delete a[i];
    WorkFile.close();
    ShipFile.close();
    return 0;
}

int ERT_t(Work** w, int work_num, Ship** a, int ship_num){
    int harbor1=0, harbor2=0, h1_delay=0, h2_delay=0;
    // find how many works are done in each harbor respectively
    for(int i=0;i<work_num;i++)
        if( w[i]->gettype()=="I" or w[i]->gettype()=="O"){
            if( w[i]->getnum1()==1) harbor1++;
            else if( w[i]->getnum1()==2) harbor2++;
        }
    // create new work pointer array for each harbor
    Work* h1[harbor1];
    Work* h2[harbor2];
    // separate "IN" and "OUT" objects into two groups
    int one=0, two=0;
    for(int i=0;i<work_num;i++)
        if( w[i]->gettype()!="T")
            if( w[i]->getnum1()==1){
                h1[one] = w[i]; one++;
            }
            else if( w[i]->getnum1()==2 ){
                h2[two] = w[i]; two++;
            }
    // rearrange the order of harbors by ERT method
    work_reorder_ERT(h1,harbor1,a,ship_num);
    work_reorder_ERT(h2,harbor2,a,ship_num);
    // calculate the delay time of two harbors and return their sum
    h1_delay = waiting_time(h1, harbor1);
    h2_delay = waiting_time(h2, harbor2);
    return h1_delay+h2_delay;
}
void work_reorder_ERT(Work** h, int harbor_num, Ship** a, int ship_num){
    int t1=0, t2=0;
    Work* d;
    // first arrange the works by the rule of ERT
    for(int j=harbor_num;j>0;j--)
    for(int i=0;i<j-1;i++){
        t1 = stoi(h[i]->getstart().substr(0,2))*60+stoi(h[i]->getstart().substr(3,2));
        t2 = stoi(h[i+1]->getstart().substr(0,2))*60+stoi(h[i+1]->getstart().substr(3,2));
        if(t2<t1) {
            if( h[i]->gettype()=="I") d = new IN(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
            else if( h[i]->gettype()=="O") d = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
            h[i] = h[i+1];
            h[i+1] = d;
        }else if(t2==t1){
            if( h[i]->getw_time()> h[i+1]->getw_time()){
                if( h[i]->gettype()=="I") d = new IN(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                else if( h[i]->gettype()=="O") d = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                h[i] = h[i+1];
                h[i+1] = d;
            }else if ( h[i]->getw_time()== h[i+1]->getw_time()){
                if( h[i]->getid().compare(h[i+1]->getid())>0 ){
                    if( h[i]->gettype()=="I") d = new IN(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                    else if( h[i]->gettype()=="O") d = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                    h[i] = h[i+1];
                    h[i+1] = d;
                }
            }
        }
    }
    // check them again and deal with the "zero operation time" situation
    int* timeslot[harbor_num];
    for(int i=0;i<harbor_num;i++) timeslot[i] = new int[2];
    int current_time=0, start_time=0, operation_time=0;
    for(int i=0;i<harbor_num;i++){
        start_time=stoi(h[i]->getstart().substr(0,2))*60+stoi(h[i]->getstart().substr(3,2));
        operation_time = h[i]->getw_time();
        if(i==0) current_time = start_time;
        if( operation_time!=0){
            if( current_time >= start_time){
                timeslot[i][0] = current_time;
                timeslot[i][1] = current_time+operation_time;
                current_time += operation_time;
            }
            else{
                current_time = start_time;
                timeslot[i][0] = current_time;
                timeslot[i][1] = current_time+operation_time;
                current_time+=operation_time;
            }
        }else{
            bool isinsert = false;
            for(int j=0;j<i;j++){
                if( timeslot[j][1]>= start_time){
                    isinsert = true;
                    if( h[i]->gettype()=="I") d = new IN(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                    else if( h[i]->gettype()=="O") d = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                    for(int k=i;k>j+1;k--){
                        h[k] = h[k-1];
                        timeslot[k][0] = timeslot[k-1][0];
                        timeslot[k][1] = timeslot[k-1][1];
                    }
                    h[j+1] = d;
                    timeslot[j+1][0] = timeslot[j][1];
                    timeslot[j+1][1] = timeslot[j][1];
                    break;
                }
            }
            if( isinsert==false){
                if( i==0 ){
                    timeslot[i][0] = start_time;
                    timeslot[i][1] = start_time;
                }else{
                    if(timeslot[i-1][1]> start_time) timeslot[i][0] = timeslot[i-1][1];
                    else {
                        timeslot[i][0] = start_time;
                        current_time = start_time;
                    }
                    timeslot[i][1] = timeslot[i][0];
                }
            }
        }
    }
}
int SPT_t(Work** w, int work_num, Ship** a, int ship_num){
    int harbor1=0, harbor2=0, h1_delay=0, h2_delay=0;
    // find how many works are done in each harbor respectively
    for(int i=0;i<work_num;i++)
        if( w[i]->gettype()=="I" or w[i]->gettype()=="O"){
            if( w[i]->getnum1()==1) harbor1++;
            else if( w[i]->getnum1()==2) harbor2++;
        }
    // create new work pointer array for each harbor
    Work* h1[harbor1];
    Work* h2[harbor2];
    // separate "IN" and "OUT" objects into two groups
    int one=0, two=0;
    for(int i=0;i<work_num;i++)
        if( w[i]->gettype()!="T")
            if( w[i]->getnum1()==1){
                h1[one] = w[i]; one++;
            }
            else if( w[i]->getnum1()==2 ){
                h2[two] = w[i]; two++;
            }
    // rearrange the order of two harbors by SPT method
    work_reorder_SPT(h1,harbor1,a,ship_num);
    work_reorder_SPT(h2,harbor2,a,ship_num);
    // calculate the delay time of two harbors and return their sum
    h1_delay = waiting_time(h1, harbor1);
    h2_delay = waiting_time(h2, harbor2);
    return h1_delay+h2_delay;
}
void work_reorder_SPT(Work** h, int harbor_num, Ship** a, int ship_num){
    int t1=0, t2=0;
    Work* c;
    // first arrange the works by SPT rule
    for(int j=harbor_num;j>0;j--)
    for(int i=0;i<j-1;i++){
        if( h[i]->getw_time() > h[i+1]->getw_time()){
            if( h[i]->gettype()=="I") c = new IN(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
            else if( h[i]->gettype()=="O") c = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
            h[i] = h[i+1];
            h[i+1] = c;
        }
        else if( h[i]->getw_time() == h[i+1]->getw_time() ){
            t1 = stoi(h[i]->getstart().substr(0,2))*60+stoi(h[i]->getstart().substr(3,2));
            t2 = stoi(h[i+1]->getstart().substr(0,2))*60+stoi(h[i+1]->getstart().substr(3,2));
            if(t1>t2) {
                if( h[i]->gettype()=="I") c = new IN(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                else if( h[i]->gettype()=="O") c = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                h[i] = h[i+1];
                h[i+1] = c;
            }
            else if(t1==t2){
                if( h[i]->getid().compare(h[i+1]->getid())>0 ){
                    if( h[i]->gettype()=="I") c = new IN(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                    else if( h[i]->gettype()=="O") c = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                    h[i] = h[i+1];
                    h[i+1] = c;
                }
            }
        }
    }
    // check them again, and insert the work into its earliest starting time
    int* timeslot[harbor_num];
    int start_now=0, operation_now=0,  end_now=0;
    for(int i=0;i<harbor_num;i++) timeslot[i] = new int[2];
    bool isinsert = false;
    for(int i=0;i<harbor_num;i++){
        isinsert = false;
        start_now = stoi(h[i]->getstart().substr(0,2))*60+stoi(h[i]->getstart().substr(3,2));
        operation_now = h[i]->getw_time();
        end_now = start_now + h[i]->getw_time();
        if(i==0){
            timeslot[0][0] = start_now;
            timeslot[0][1] = end_now;
        }else{
            for(int j=0;j<i;j++){
                if(j==0){
                    if( end_now <= timeslot[0][0]){
                        if( h[i]->gettype()=="I") c = new IN(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                        else if( h[i]->gettype()=="O") c = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                        for(int k=i;k>j;k--) {
                            timeslot[k][0] = timeslot[k-1][0];
                            timeslot[k][1] = timeslot[k-1][1];
                            h[k] = h[k-1];
                        }
                        h[j] = c;
                        timeslot[0][0] = start_now;
                        timeslot[0][1] = end_now;
                        isinsert = true;
                        break;
                    }
                }else{
                    end_now = timeslot[j][0];
                    if(  timeslot[j-1][1]+operation_now<=timeslot[j][0] and start_now+operation_now<=timeslot[j][0]){
                        if( h[i]->gettype()=="I") c = new IN(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                        else if( h[i]->gettype()=="O") c = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->getw_time(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                        for(int k=i;k>j;k--) {
                            timeslot[k][0] = timeslot[k-1][0];
                            timeslot[k][1] = timeslot[k-1][1];
                            h[k] = h[k-1];
                        }
                        h[j] = c;
                        if(timeslot[j-1][1]>start_now) timeslot[j][0] = timeslot[j-1][1];
                        else timeslot[j][0] = start_now;
                        timeslot[j][1] = timeslot[j][0]+operation_now;
                        isinsert = true;
                        break;
                    }
                }
            }
            if(isinsert==false){
                if(timeslot[i-1][1]>start_now) timeslot[i][0] = timeslot[i-1][1];
                else timeslot[i][0] = start_now;
                timeslot[i][1] = timeslot[i][0]+operation_now;
            }
        }
    }
}
int waiting_time(Work** h, int harbor_num){
    int delay=0;
    if( harbor_num==0) delay=0;
    else{
        int current_t = stoi(h[0]->getstart().substr(0,2))*60 + stoi(h[0]->getstart().substr(3,2));
        for(int i=0;i<harbor_num;i++){
            int start_t = stoi(h[i]->getstart().substr(0,2))*60 + stoi(h[i]->getstart().substr(3,2));
            if( current_t < start_t ){
                current_t = start_t;
            }
            else if( current_t > start_t ){
                delay += ( current_t-start_t);
            }
            current_t += h[i]->getw_time();
        }
    }
    return delay;
}
