// Following HW 2-2, in this assignment, update the rules for scheduling the jobs while implementing same algorithms.

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
    bool getdanger();
    string getnation();
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
bool Ship::getdanger(){
    return danger;
}
string Ship::getnation(){
    string rev_nation = nation, new_nation = "";
    while( rev_nation.find(" ")!= string::npos ){
        int space = rev_nation.find(" ");
        if(new_nation=="")
            new_nation = rev_nation.substr(0,1)+rev_nation.substr(space+1,1);
        else
            new_nation += rev_nation.substr(space+1,1);
        rev_nation = rev_nation.substr(space+1, string::npos);
    }
    if (new_nation=="") return nation;
    else return new_nation;
}
class Work{
protected:
    Ship* ship;
    string id, start_time, type;
    int num1, num2, ship_num, score;
    bool priority;
public:
    Work();
    Work(string id, string start_time,string type, int num1, int num2, Ship** a, int ship_num);
    string getid();
    string getstart();
    string gettype();
    int getnum1();
    int getnum2();
    int getscore();
    bool getpriority();
    void setscore(int n);
    void setpriority(bool p);
    virtual void print()=0;
    virtual int get_ope_t1()=0;
    virtual int get_ope_t2()=0;
    virtual int get_ope_t()=0;
    Ship* getship();
};
Work::Work(){
    ship = NULL;
    id = start_time = type = "";
    num1=0, num2=0, ship_num=0, score=0, priority=false;
}
Work::Work(string id, string start_time, string type, int num1, int num2, Ship** a, int ship_num):
    id(id),start_time(start_time),type(type), num1(num1), num2(num2), ship_num(ship_num), score(0),priority(false){
    for(int i=0;i<ship_num;i++)
        if( a[i]->getid()==id ) ship = a[i];
}
string Work::getid(){
    return id;
}
string Work::getstart(){
    return start_time;
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
int Work::getscore(){
    return score;
}
bool Work::getpriority(){
    return priority;
}
void Work::setscore(int n){
    score = n;
}
void Work::setpriority(bool p){
    priority = p;
}
void Work::print(){
    cout << id << "," << start_time <<  "," << type <<
    "," << num1 << "," << num2 <<endl;
}
Ship* Work::getship(){
    return ship;
}
class IN: public Work{
protected:
    int ope_t1, ope_t2;
    int get_ope_t();
public:
    IN(string id, string start_time, int ope_t1, int ope_t2, string type, int num1, int num2, Ship** a, int ship_num);
    int get_ope_t1();
    int get_ope_t2();
    void print();
};
IN::IN(string id, string start_time, int ope_t1, int ope_t2, string type, int num1, int num2, Ship** a, int ship_num)
        :Work(id, start_time, type, num1, num2, a, ship_num),ope_t1(ope_t1), ope_t2(ope_t2){
}
int IN::get_ope_t1(){
    return ope_t1;
}
int IN::get_ope_t2(){
    return ope_t2;
}
int IN::get_ope_t(){
    return -1;
}
void IN::print(){
    cout << id << "," << start_time << "," << ope_t1 << "," << ope_t2 << "," << type <<
    "," << num1 << "," << num2 <<endl;
}
class OUT: public Work{
protected:
    int ope_t1, ope_t2;
    int get_ope_t();
public:
    OUT(string id, string start_time,int ope_t1, int ope_t2, string type, int num1, int num2, Ship** a, int ship_num);
    int get_ope_t1();
    int get_ope_t2();
    void print();
};
OUT::OUT(string id, string start_time, int ope_t1, int ope_t2, string type, int num1, int num2, Ship** a, int ship_num)
        :Work(id, start_time, type, num1, num2, a, ship_num),ope_t1(ope_t1), ope_t2(ope_t2){
}
int OUT::get_ope_t1(){
    return ope_t1;
}
int OUT::get_ope_t2(){
    return ope_t2;
}
int OUT::get_ope_t(){
    return -1;
}
void OUT::print(){
    cout << id << "," << start_time << "," << ope_t1 << "," << ope_t2 << "," << type <<
    "," << num1 << "," << num2 <<endl;
}
class Move: public Work{
protected:
    int ope_t;
    int get_ope_t1();
    int get_ope_t2();
public:
    Move(string id, string start_time, int ope_t, string type, int num1, int num2, Ship** a, int ship_num);
    int get_ope_t();
    void print();
};
Move::Move(string id, string start_time, int ope_t, string type, int num1, int num2, Ship** a, int ship_num)
        :Work(id, start_time, type, num1, num2, a, ship_num){
    ope_t = ope_t;
}
int Move::get_ope_t(){
    return ope_t;
}
int Move::get_ope_t1(){
    return -1;
}
int Move::get_ope_t2(){
    return -1;
}
void Move::print(){
    cout << id << "," << start_time << "," << ope_t << "," << type <<
    "," << num1 << "," << num2 <<endl;
}

void get_t(Work**, int, Ship**, int, string [], int, int&, int&, int&, int&); //to calculate the total time of ERT
void work_reorder(Work** , int , Ship**, int , string [], int , int& , int&); //reorder the works by rules of ERT
//int waiting_time(Work**, int); //calculate the delay time of the passed Work** array
static int m,b1,b2,b3,b4;
int main(){
    ifstream ShipFile, WorkFile, PriorityFile;
    string total = "";
    string id, start_time, ope_t_str,ope_t1_str,ope_t2_str, type, one, two;
    string sfile_name, wfile_name, pfile_name;
    int ope_t,ope_t1,ope_t2, pier_num, num1,num2;
    int ship_num = 0, work_num =0, priority_num = 0;
    string m_str, b1_str, b2_str, b3_str, b4_str;
    getline(cin,m_str,',');
    getline(cin,b1_str,',');
    getline(cin,b2_str,',');
    getline(cin,b3_str,',');
    getline(cin,b4_str,'\n');
    m = stoi(m_str);
    b1 = stoi(b1_str);
    b2 = stoi(b2_str);
    b3 = stoi(b3_str);
    b4 = stoi(b4_str);
    cin >> sfile_name >> wfile_name >> pfile_name;
    WorkFile.open(wfile_name);
    ShipFile.open(sfile_name);
    PriorityFile.open(pfile_name);
    // calculate the number of ships and works respectively
    while(!ShipFile.eof()){
        getline(ShipFile, total, '\n');
        ship_num++;
    }
    while(!WorkFile.eof()){
        getline(WorkFile, total, '\n');
        work_num++;
    }
    while(!PriorityFile.eof()){
        getline(PriorityFile, total, '\n');
        priority_num++;
    }
    WorkFile.close();
    ShipFile.close();
    PriorityFile.close();
    WorkFile.open(wfile_name);
    ShipFile.open(sfile_name);
    PriorityFile.open(pfile_name);
    Ship* a[ship_num];
    Work* b[work_num];
    string p[priority_num];
    int num=0;
    // store the priority list in p
    while(!PriorityFile.eof())
        for(int i=0;i<priority_num;i++)
            getline(PriorityFile,p[i],'\n');
    // store the data of ships into Ship* array
    while(!ShipFile.eof()){
        for(int i=0;i<ship_num;i++) a[i] = new Ship(ShipFile);
    }
    // store the data of works into Work* array
    string sentence;
    int cur_cnt_pos=0, found=0, element_cnt=0;
    while(!WorkFile.eof()){
        cur_cnt_pos = 0, found = 0, element_cnt=0;
        getline(WorkFile, sentence,'\n');
        while(found!=string::npos){
            found = sentence.find(',',cur_cnt_pos);
            cur_cnt_pos = found+1;
            element_cnt++;
        }
        if(element_cnt==7){
            cur_cnt_pos=0;
            found = sentence.find(',',cur_cnt_pos);
            id = sentence.substr(cur_cnt_pos,found);
            cur_cnt_pos = found+1;
            found = sentence.find(',',cur_cnt_pos);
            start_time = sentence.substr(cur_cnt_pos,found-cur_cnt_pos);
            cur_cnt_pos = found+1;
            found = sentence.find(',',cur_cnt_pos);
            ope_t1_str = sentence.substr(cur_cnt_pos,found-cur_cnt_pos);
            cur_cnt_pos = found+1;
            found = sentence.find(',',cur_cnt_pos);
            ope_t2_str= sentence.substr(cur_cnt_pos,found-cur_cnt_pos);
            cur_cnt_pos = found+1;
            found = sentence.find(',',cur_cnt_pos);
            type = sentence.substr(cur_cnt_pos,found-cur_cnt_pos);
            cur_cnt_pos = found+1;
            found = sentence.find(',',cur_cnt_pos);
            one = sentence.substr(cur_cnt_pos,found-cur_cnt_pos);
            cur_cnt_pos = found+1;
            found = sentence.find('\n',cur_cnt_pos);
            two = sentence.substr(cur_cnt_pos,found-cur_cnt_pos);
            ope_t1 = stoi(ope_t1_str);
            ope_t2 = stoi(ope_t2_str);
            num1 = stoi(one);
            num2 = stoi(two);
            if(type=="I") b[num] = new IN(id,start_time,ope_t1,ope_t2,type,num1,num2,a,ship_num);
            else b[num] = new OUT(id,start_time,ope_t1,ope_t2,type,num1,num2,a,ship_num);
        }else{
            cur_cnt_pos=0;
            found = sentence.find(',',cur_cnt_pos);
            id = sentence.substr(cur_cnt_pos,found);
            cur_cnt_pos = found+1;
            found = sentence.find(',',cur_cnt_pos);
            start_time = sentence.substr(cur_cnt_pos,found-cur_cnt_pos);
            cur_cnt_pos = found+1;
            found = sentence.find(',',cur_cnt_pos);
            ope_t_str = sentence.substr(cur_cnt_pos,found-cur_cnt_pos);
            cur_cnt_pos = found+1;
            found = sentence.find(',',cur_cnt_pos);
            type = sentence.substr(cur_cnt_pos,found-cur_cnt_pos);
            cur_cnt_pos = found+1;
            found = sentence.find(',',cur_cnt_pos);
            one = sentence.substr(cur_cnt_pos,found-cur_cnt_pos);
            cur_cnt_pos = found+1;
            found = sentence.find('\n',cur_cnt_pos);
            two = sentence.substr(cur_cnt_pos,found-cur_cnt_pos);
            ope_t = stoi(ope_t_str);
            num1 = stoi(one);
            num2 = stoi(two);
            b[num] = new Move(id,start_time,ope_t,type,num1,num2,a,ship_num);
        }
        num++;
    }
    // cout the delay time of ERT and SPT method respectively
    int delayIN_1=0, delayOUT_1=0, delayIN_2=0, delayOUT_2=0;
    get_t(b, work_num, a, ship_num ,p,priority_num,delayIN_1,delayOUT_1,delayIN_2,delayOUT_2);

    cout << delayIN_1 <<" "<< delayOUT_1 << " " << delayIN_2 << " " << delayOUT_2;
    for(int i=0;i<work_num;i++) delete b[i];
    for(int i=0;i<ship_num;i++) delete a[i];
    WorkFile.close();
    ShipFile.close();
    PriorityFile.close();
    return 0;
}

void get_t(Work** w, int work_num, Ship** a, int ship_num, string p[], int priority_num, int& delayIN_1, int& delayOUT_1, int& delayIN_2, int& delayOUT_2){
    int harbor1=0, harbor2=0;
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
    work_reorder(h1,harbor1,a,ship_num,p,priority_num,delayIN_1,delayOUT_1);
    work_reorder(h2,harbor2,a,ship_num,p,priority_num,delayIN_2,delayOUT_2);
}
void work_reorder(Work** h, int harbor_num, Ship** a, int ship_num, string p[], int priority_num, int& delayIN, int& delayOUT){
    int t1=0, t2=0, s1=0, s2=0, stime1=0, stime2=0, otime1=0, otime2=0;
    string nation1="", nation2 = "";
    bool d1=0,d2=0, p1=0,p2=0;
    Work* d;
    // first arrange the works by the rule of ERT
    for(int j=harbor_num;j>0;j--){
    for(int i=0;i<j-1;i++){
        stime1 = stoi(h[i]->getstart().substr(0,2))*60+stoi(h[i]->getstart().substr(3,2));
        stime2 = stoi(h[i+1]->getstart().substr(0,2))*60+stoi(h[i+1]->getstart().substr(3,2));
        otime1 = h[i]->get_ope_t1()+h[i]->get_ope_t2();
        otime2 = h[i+1]->get_ope_t1()+h[i+1]->get_ope_t2();
        d1 = h[i]->getship()->getdanger();
        d2 = h[i+1]->getship()->getdanger();
        p1 = p2 =false;
        nation1 = h[i]->getship()->getnation();
        nation2 = h[i+1]->getship()->getnation();
        for(int k=0;k<priority_num;k++)
        if (p[k]== nation1){
            p1 = true; break;
        }
        for(int k=0;k<priority_num;k++)
        if(p[k]==nation2){
            p2 = true; break;
        }
        s1 = b1*stime1 + b2*otime1 -b3*d1 -b4*p1;
        s2 = b1*stime2 + b2*otime2 -b3*d2 -b4*p2;
        if(s2<s1) {
            if( h[i]->gettype()=="I") d = new IN(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
            else if( h[i]->gettype()=="O") d = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
            h[i] = h[i+1];
            h[i+1] = d;
        }else if(s2==s1){
            if(d2>d1){
                if( h[i]->gettype()=="I") d = new IN(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                else if( h[i]->gettype()=="O") d = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                h[i] = h[i+1];
                h[i+1] = d;
            }
            else if (d2==d1){
                if (p2>p1){
                    if( h[i]->gettype()=="I") d = new IN(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                    else if( h[i]->gettype()=="O") d = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                    h[i] = h[i+1];
                    h[i+1] = d;
                }
                else if(p2==p1){
                    if( h[i+1]->getid().compare(h[i]->getid())<0){
                        if( h[i]->gettype()=="I") d = new IN(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                        else if( h[i]->gettype()=="O") d = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                        h[i] = h[i+1];
                        h[i+1] = d;
                    }
                }
            }

        }
    }
    }
    for(int i=0;i<harbor_num;i++){
        int st = stoi(h[i]->getstart().substr(0,2))*60+stoi(h[i]->getstart().substr(3,2)), ot = h[i]->get_ope_t1()+h[i]->get_ope_t2();
        bool dt = h[i]->getship()->getdanger(), pt = false;
        string nation = h[i]->getship()->getnation();
        for(int k=0;k<priority_num;k++)
        if (p[k]== nation){
            pt = true; break;
        }
        h[i]->setpriority(pt);
        h[i]->setscore(b1*st+b2*ot-b3*dt-b4*pt);
    }
    // check them again and deal with the "zero operation time" situation
    int* timeslot[harbor_num];
    for(int i=0;i<harbor_num;i++) timeslot[i] = new int[2];
    int current_time=0, start_time=0, operation_time=0;

    for(int i=0;i<harbor_num;i++){
        start_time=stoi(h[i]->getstart().substr(0,2))*60+stoi(h[i]->getstart().substr(3,2));
        if( h[i]->gettype()=="I"){
            operation_time = h[i]->get_ope_t1();
        }else{
            start_time += h[i]->get_ope_t1();
            operation_time = h[i]->get_ope_t2();
        }
        if(i==0) current_time = start_time;
        if( operation_time!=0){
            bool isinsert = false;
            for(int j=0;j<i;j++){
                if( j==0 ){
                    if ( start_time+operation_time <= timeslot[0][0]){
                        isinsert =true;
                        if( h[i]->gettype()=="I") d = new IN(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                        else if( h[i]->gettype()=="O") d = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                        for(int k=i;k>0;k--){
                            h[k] = h[k-1];
                            timeslot[k][0] = timeslot[k-1][0];
                            timeslot[k][1] = timeslot[k-1][1];
                        }
                        h[0] = d;
                        timeslot[0][0] = start_time;
                        timeslot[0][1] = start_time+operation_time;
                        break;
                    }
                }
                else{ //j!=0
                    if ( timeslot[j][0]>= timeslot[j-1][1]+operation_time && timeslot[j][0]>= start_time+operation_time){ //insert to j+1
                        isinsert = true;
                        if( h[i]->gettype()=="I") d = new IN(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                        else if( h[i]->gettype()=="O") d = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                        for(int k=i;k>j;k--){
                            h[k] = h[k-1];
                            timeslot[k][0] = timeslot[k-1][0];
                            timeslot[k][1] = timeslot[k-1][1];
                        }
                        h[j] = d;
                        if( timeslot[j-1][1] >= start_time){
                            timeslot[j][0] = timeslot[j-1][1];
                            timeslot[j][1] = timeslot[j][0]+operation_time;
                        }
                        else{
                            timeslot[j][0] = start_time;
                            timeslot[j][1] = timeslot[j][0]+operation_time;
                        }
                        break;
                    }
                }
            }
            if( !isinsert ){
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
            }
        }else{ //operation time=0
            bool isinsert = false;
            for(int j=0;j<i;j++){
                if( timeslot[j][1]>= start_time){
                    isinsert = true;
                    if( h[i]->gettype()=="I") d = new IN(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
                    else if( h[i]->gettype()=="O") d = new OUT(h[i]->getid(),h[i]->getstart(),h[i]->get_ope_t1(),h[i]->get_ope_t2(),h[i]->gettype(), h[i]->getnum1(),h[i]->getnum2(),a,ship_num);
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
    for(int i=0;i<harbor_num;i++){
        int can_start, diff;
        if( h[i]->gettype()=="I") can_start = stoi(h[i]->getstart().substr(0,2))*60+stoi(h[i]->getstart().substr(3,2));
        else can_start = stoi(h[i]->getstart().substr(0,2))*60+stoi(h[i]->getstart().substr(3,2))+h[i]->get_ope_t1();
        diff = timeslot[i][0]-can_start;
        if(diff>0) {
            if(h[i]->gettype()=="I" ) delayIN+= diff;
            else delayOUT+=diff;
        }
    }

}
