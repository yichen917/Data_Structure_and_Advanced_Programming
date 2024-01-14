#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

int process_to(const int next_time, int quantum[], bool add);
void new_addition();

class process{
private:
    string name;
    int appearing_time, process_time, original_process_time;
public:
    process();
    process(string name, int appearing_time, int process_time);
    string get_name();
    string get_name() const;
    int get_appearing_time()const;
    int get_process_time()const;
    int get_original_process_time()const;
    void reducing_time(const int reduce);
    bool isFinished();
    void print();
};
process::process(){
    name = "";
    appearing_time = process_time = original_process_time = 0;
}
process::process(string name, int appearing_time, int process_time){
    this->name = name;
    this->appearing_time = appearing_time;
    this->process_time = process_time;
    this->original_process_time = process_time;
}
string process::get_name(){ return name;}
string process::get_name() const { return name;}
int process::get_appearing_time()const{ return appearing_time; }
int process::get_process_time() const{ return process_time; }
int process::get_original_process_time() const{ return original_process_time;}
void process::reducing_time(const int reduce){
    this->process_time -= reduce;
}
bool process::isFinished(){
    if (process_time == 0)
        return true;
    else
        return false;
}
void process::print(){
    cout << name << " " << process_time << endl;
}

class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (process& lhs, process&rhs)
  {
    if (reverse) {
        if ( lhs.get_original_process_time() < rhs.get_original_process_time())
            return true;
        else return false;
    }else {
        if (lhs.get_original_process_time() > rhs.get_original_process_time() )
            return true;
        else return false;
    }
  }
};

queue<process>* q;
static int current_time = 0;
static int current_queue_index = 0;
static int queue_num =0 ;
vector<process> all_process;
typedef priority_queue<process, vector<process>, mycomparison > pq;
pq p;
int main(){
    cin >> queue_num;

    int quantum[queue_num-1];
    for(int i=0;i<queue_num-1;i++){
        cin >> quantum[i];
    }
    q = new queue<process>[queue_num-1];
    string name, read;
    int appearing_time, process_time, next_time, space, space2;
    cin.ignore();
    while ( getline(cin,read,'\n') ){
        //cout << "New line is " << read <<endl;
        //cout << read.substr( read.length()-2,2 )<<endl;
        if ( read.substr( read.length()-2,2 )== "ps"){
            //cout << "Need to print!" <<endl;
            space = read.find(' ');
            next_time = stoi(read.substr(0,space));
            process_to(next_time,quantum,false);
            for(int i=0;i<all_process.size();i++)
                all_process[i].print();
        }else{
            //cout << "New process has been added!" <<endl;
            space = read.find(' ');
            appearing_time = stoi(read.substr(0,space));
            space2 = read.find(' ',space+1);
            name = read.substr(space+1, space2-space-1);
            space = space2;
            space2 = read.find('\n',space+1);
            process_time = stoi( read.substr(space+1, space2-space-1));
            process added = process(name,appearing_time,process_time);
            bool renumber = true;
            for(int i=0;i<all_process.size();i++){
                if ( all_process[i].get_process_time()!=0 )
                    renumber = false;
            }
            if (all_process.empty() or renumber)
                current_time = added.get_appearing_time();
            all_process.push_back(added);
            process_to( appearing_time, quantum, true);
            q[0].push(added);
        }

    }

    delete [] q;
    return 0;
}

int process_to(const int next_time, int quantum[], bool add){
    //cout << "------------------------------------------\n";
    //cout << "start process to " <<endl;
    static int unfinished;
    int process_time, to_do,i=0;
    bool end = false, pause;
    // pause = true -> 不用pop 只做到一半
    if (current_time < next_time){
        while(i<queue_num){
           // cout << "------------------- i=" << i << "---------------\n";
            bool non_empty;
            if ( i!= queue_num-1 )
                if ( q[i].empty() ) non_empty = false;
                else non_empty = true;
            else
                if ( p.empty()) non_empty = false;
                else non_empty = true;
            //cout << "non empty = " << non_empty<<endl;
            while ( non_empty ){
                process first;
                if ( i!= queue_num-1)
                    first = q[i].front();
                else
                    first = p.top();
                //cout << "first name is " << first.get_name() <<endl;
                if (unfinished !=0 )
                    to_do = unfinished;
                else
                    if ( i!= queue_num-1 )
                        to_do = quantum[i];
                    else
                        to_do = INT_MAX;
                //cout << "first process time is " << first.get_process_time() <<endl;
                if (first.get_process_time() < to_do)
                    to_do = first.get_process_time();
                //cout << "to_do = " << to_do <<endl;
                if (current_time + to_do > next_time){
                    process_time = next_time - current_time;
                    unfinished = to_do - process_time;
                    pause = true;
                    end = true;
                }else{
                    if (current_time + to_do == next_time)
                        end = true;
                    process_time = to_do;
                    unfinished = 0;
                    pause = false;
                }
                if ( i < queue_num-1){
                    q[i].front().reducing_time(process_time);
                    first = q[i].front();
                }
                else{
                    process temp(p.top().get_name(),p.top().get_appearing_time(),p.top().get_process_time()-process_time);
                    p.pop();
                    p.push(temp);
                    first = p.top();
                    //cout << "the top of p is " << p.top().get_name()<<endl;
                }

                //cout << "reduce q\n";
                for(int k=0;k<all_process.size();k++){
                    if ( all_process[k].get_name() == first.get_name())
                        all_process[k].reducing_time(process_time);
                }
                //cout << first.get_name() << " has been reduced " << process_time <<endl;
                if ( !pause ){ // 做完一回
                    if ( first.get_process_time() !=0 ){
                        if ( i < queue_num-2){
                            q[i+1].push( first);
                            //cout << first.get_name() << "is pushed into queue " << i+1<< endl;
                        }else { //be pushed into a priority queue
                            p.push(first);
                            //cout << first.get_name() << "is pushed into queue " << i+1<< endl;
                        }
                    }
                    //cout << first.get_name() << "has been popped" << endl;
                    if ( i < queue_num-1 )
                        q[i].pop();
                    else
                        p.pop();
                }else{
                    if (add && i!=0){
                        if ( i < queue_num-1 ){
                            q[i].push(first);
                            //cout << first.get_name() << "is pushed into queue " << i<< endl;
                            //cout << first.get_name() << "has been popped" << endl;
                            q[i].pop();
                        }else{
                            p.push(first);
                            //cout << first.get_name() << "is pushed into queue " << i<< endl;
                            //cout << first.get_name() << "has been popped" << endl;
                            p.pop();
                        }
                        unfinished = 0;
                    }
                }
                current_time += process_time;
                //cout << "current time becomes " << current_time<<endl;
                if ( i!= queue_num-1 )
                    if ( q[i].empty() ) non_empty = false;
                    else non_empty = true;
                else
                    if ( p.empty()) non_empty = false;
                    else non_empty = true;
                if ( end )
                    break;
            }
            if ( end )
                break;
            //cout << "unfinished = " << unfinished <<endl;
            i++;
        }
    }
    //cout << "---------------------------------\n" ;
    return unfinished;
}
