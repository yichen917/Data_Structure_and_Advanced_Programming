/*
This assignment primarily involves augmenting path algorithm implementation - BFS (breath-first search) method.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

class Road;
class Node{
private:
    string start, end;
    int capacity;
public:
    Node();
    Node(string const input_start, string const input_end, int const input_capacity);
    string get_start();
    string get_end();
    int get_capacity();
    void print();
friend class Road;
};

Node::Node(){
    start = end = "";
    capacity = 0;
}
Node::Node(string const input_start, string const input_end, int const input_capacity){
    start = input_start;
    end = input_end;
    capacity = input_capacity;
}
string Node::get_start(){
    return start;
}
string Node::get_end(){
    return end;
}
int Node::get_capacity(){
    return capacity;
}
void Node::print(){
    cout << start << "," <<end << ";" << capacity <<endl;
}

class Road{
private:
    vector<string> road;
    int max_capacity;
public:
    Road();
    Road(string const initial_node);
    Road(Road existed_road, string const next_node, int const new_capacity);
    vector<string> get_road();
    string get_tail();
    int get_max_capacity();
    void print();
};
Road::Road(){
    max_capacity = 100;
}
Road::Road(string const initial_node){
    road.push_back(initial_node);
    max_capacity = 100;
}
Road::Road(Road existed_road, string const next_node, int const new_capacity){
    for(int i=0;i<existed_road.get_road().size();i++)
        road.push_back(existed_road.get_road()[i]);
    road.push_back(next_node);
    if( new_capacity < existed_road.get_max_capacity())
        max_capacity = new_capacity;
    else max_capacity = existed_road.get_max_capacity();
}
vector<string> Road::get_road(){
    return road;
}
string Road::get_tail(){
    return road[road.size()-1];
}
int Road::get_max_capacity(){
    return max_capacity;
}
void Road::print(){
    if( road.size()==0)
        cout << "empty;" << max_capacity <<endl;
    else{
        for(int i=0; i< road.size()-1;i++)
            cout << road[i] <<",";
        cout << road[road.size()-1] << ";";
        cout << max_capacity <<endl;
    }
}
int main(){
    int n,m; //n node, m path
    string read;
    getline(cin,read,',');
    n = stoi(read);
    getline(cin,read,'\n');
    m = stoi(read);

    string data[n];
    for(int i=0;i<n-1;i++){
        getline(cin,data[i],',');
    }
    getline(cin,data[n-1],'\n');

    Node nodes[m];
    for(int i=0;i<m;i++){
        string start,end;
        int capacity;
        getline(cin,start,',');
        getline(cin,end,',');
        getline(cin,read,'\n');
        capacity = stoi(read);
        nodes[i] = Node(start,end,capacity);
    }

    vector<Road> path;
    Road augPath;
    string start = data[0], des = data[n-1];
    Road first(start);
    path.push_back(first);
    int current_size = 1, new_size=0, same_start = 0;
    bool finish = false,not_added = false;;
    while( true ){
        new_size = 0;
        // pick up existed path and extend
        for(int k=0;k<current_size;k++){
            Road current_road = path[k];
            string current_end = current_road.get_tail();
            // check if there is a road to extend
            same_start = 0;
            for(int i=0;i<m;i++){
                not_added = false;
                if( nodes[i].get_start()==current_end){
                    string next_node = nodes[i].get_end();
                    for(int z=0;z<current_road.get_road().size();z++){ //check if next node already exists
                        if( next_node== current_road.get_road()[z]){
                            not_added = true;
                        }
                    }
                    if( nodes[i].get_capacity()==0) // check if cap=0
                        not_added = true;
                    if( !not_added ){
                        same_start++;
                        new_size++;
                        Road extend( current_road, next_node, nodes[i].get_capacity());
                        if( same_start==1 ){
                            path.push_back(extend);
                        }
                        else{
                            bool isinsert = false;
                            for(int j=current_size+new_size-same_start;j<current_size+new_size-1;j++){
                                if( path[j].get_max_capacity() < extend.get_max_capacity() ){
                                    path.insert(path.begin()+j, extend);
                                    isinsert = true;
                                    break;
                                }
                                else if (path[j].get_max_capacity() == extend.get_max_capacity()){
                                    if( path[j].get_tail().compare(extend.get_tail())>0){
                                        path.insert(path.begin()+j,extend);
                                        isinsert = true;
                                        break;
                                    }
                                }
                            }

                            if(!isinsert){
                                path.push_back(extend);
                            }
                        }
                        if(extend.get_tail()==des){
                            augPath = extend;
                            finish = true;
                        }
                    }
                }
                if(finish) break;
            }
            if(finish) break;
        }
        for(int i=0;i<current_size;i++){
            path.erase(path.begin());
        }
        current_size = new_size;
        if(finish or path.size()==0) break;
    }
    if(path.back().get_max_capacity()==0 or path.size()==0 or n==1 )
        cout << -1;
    else
        augPath.print();

    return 0;
}


