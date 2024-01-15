/*
This assignment primarily involves augmenting path algorithm implementation - BFS (breath-first search) method.
Following HW3-2, after identifying an augmenting path, use it and modify the residual network. 
Repeat the process until the optimal solution (maximum flow) is found.
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
    void revise_cap(int new_num);
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
void Node::revise_cap(int new_num){
    this->capacity = new_num;
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

class Network{
private:
    Node* nodes;
    int n;
public:
    Network();
    Network(int n, string const data[]);
    void revise_network(Node revised_node);
    void revise_network(string const start, string const end, int const cap);
    int get_cap(string const start, string const end);
    void print();
};
Network::Network(){
    nodes = nullptr;
    n = 0;
}
Network::Network(int num, string const data[]){
    this->n = num;
    nodes = new Node[n*n];
    for(int i=0;i<n;i++){
        string start = data[i];
        for(int j=0;j<n;j++){
            string des = data[j];
            nodes[i*n+j] = Node(start,des,0);
        }
    }
}
void Network::revise_network(Node revised_node){
    string start = revised_node.get_start();
    string end = revised_node.get_end();
    int new_cap = revised_node.get_capacity();
    bool notfound = true;
    int order = 0;
    Node current_node;
    while(notfound){
        current_node = this->nodes[order];
        if(current_node.get_start()==start && current_node.get_end()==end){
            nodes[order].revise_cap(new_cap);
            break;
        }
        else order++;
    }
}
void Network::revise_network(string const start, string const end, int const cap){
    Node rNode(start,end,cap);
    revise_network(rNode);
}
int Network::get_cap(string const start, string const end){
    for(int i=0;i<n*n;i++){
        Node current_node = this->nodes[i];
        if(current_node.get_start()==start && current_node.get_end()==end)
            return current_node.get_capacity();
    }
    return -1;
}
void Network::print(){
    if(n==0)
        cout << "empty\n";
    else
        for(int i=0;i<n*n;i++)
            cout << nodes[i].get_start() <<","<<nodes[i].get_end()<<","<<nodes[i].get_capacity()<<endl;
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

    Network CapNet(n,data);

    for(int i=0;i<m;i++){
        string start,end;
        int capacity;
        getline(cin,start,',');
        getline(cin,end,',');
        getline(cin,read,'\n');
        capacity = stoi(read);
        Node rNode = Node(start,end,capacity);
        CapNet.revise_network(rNode);
    }

    vector<Road> path;
    string start = data[0], des = data[n-1];
    Road first(start);
    path.push_back(first);
    int current_size = 1, new_size=0, same_start = 0, total_cap=0;
    bool not_added = false, find_augPath = false;
    vector<Road> AllAugPath;
    while( true ){
        find_augPath = false;
        new_size = 0;
        // pick up existed path and extend
        for(int k=0;k<current_size;k++){
            Road current_road = path[k];
            string current_end = current_road.get_tail();
            // check if there is a road to extend
            same_start = 0;
            for(int i=0;i<n;i++){
                not_added = false;
                if( CapNet.get_cap(current_end,data[i])>0){
                    string next_node = data[i];
                    for(int z=0;z<current_road.get_road().size();z++){ //check if next node already exists
                        if( next_node== current_road.get_road()[z]){
                            not_added = true;
                        }
                    }
                    string toAdd = data[i];
                    int toAddCap = CapNet.get_cap(current_end,toAdd);
                    Road extend( current_road, toAdd, toAddCap);
                    if(extend.get_tail()==des){
                        not_added = true;
                        int max_cap = extend.get_max_capacity();
                        total_cap += max_cap;
                        AllAugPath.push_back(extend);
                        vector<string> AugPath = extend.get_road();
                        int pathLen = AugPath.size();
                        for(int p=0;p<pathLen-1;p++){
                            string s = AugPath[p], t = AugPath[p+1];
                            int current_cap = CapNet.get_cap(s,t);
                            CapNet.revise_network(s,t,current_cap-max_cap);
                        }
                        for(int p=pathLen-1;p>0;p--){
                            string s = AugPath[p], t = AugPath[p-1];
                            int current_cap = CapNet.get_cap(s,t);
                            CapNet.revise_network(s,t,current_cap+max_cap);
                        }
                        path.clear();
                        path.push_back(first);
                        current_size=1, new_size=0;
                        find_augPath = true;
                    }

                    if( !not_added ){
                        same_start++;
                        new_size++;
                        if( same_start==1 ){
                            path.push_back(extend);
                        }
                        else{
                            bool isinsert = false;
                            for(int j=current_size+new_size-same_start;j<current_size+new_size-1;j++){vector<string> tocompared = path[j].get_road();
                                vector<string> extend_road = extend.get_road();
                                int t_size = tocompared.size(), e_size = extend_road.size();
                                if( CapNet.get_cap(tocompared[t_size-2],tocompared[t_size-1]) < CapNet.get_cap(extend_road[e_size-2],extend_road[e_size-1]) ){
                                    path.insert(path.begin()+j, extend);
                                    isinsert = true;
                                    break;
                                }
                                else if (CapNet.get_cap(tocompared[t_size-2],tocompared[t_size-1])==CapNet.get_cap(extend_road[e_size-2],extend_road[e_size-1])){
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
                    }
                }
                if(find_augPath) break;
            }
            if(find_augPath) break;
        }
        if(!find_augPath){
            for(int i=0;i<current_size;i++){
                path.erase(path.begin());
            }
            current_size = new_size;
        }
        if(path.size()==0) break;
    }
    for(int i=0;i<AllAugPath.size();i++)
        AllAugPath[i].print();
    cout << total_cap <<endl;

    return 0;
}
