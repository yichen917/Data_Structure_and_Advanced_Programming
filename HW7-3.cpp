/*This assignment primarily involves Tree structure.

Question:
Given an undirected graph presented in adjencency matrix, the graph is a tree if there is exactly one path between any two nodes. 
Based on the input undirected graph, determine if it is a tree. If it is a tree, print out the possible minimum height of this tree.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;
static int n;
int** matrix;
static int height_count = 1;
vector<int> has_appeared;

class Node;
bool set_children(Node current, int parent_value);

class Node{
private:
    int number;
    int num_children;
    int height;
    vector<Node> children;
    //Node* parent;
public:
    Node();
    Node(int number);
    ~Node();
    void set_number(int number);
    void set_children(vector<int> children,int p_value);
    void set_height(const int h);
    //void set_parent(Node* parent);
    int gNumber();
    int gNum_children();
    int gHeight();
    vector<Node> gChildren();
    //Node* gParent();
};
Node::Node(){
    number = num_children = -1;
    height = 0;
}
Node::Node(int number){
    this->number = number;
    this->num_children = -1;
    this->height = 1;
}
Node::~Node(){
    children.clear();
    height = 0;
}
void Node::set_number(int number){
    this->number = number;
}
/*
void Node::set_parent(Node* p){
    this->parent = p;
} */
void Node::set_children(vector<int> c, int p_value){
    for(int i=0;i<c.size();i++){
        if ( c[i] == p_value )
            c.erase(c.begin()+i);
    }
    num_children = c.size();
    int parent_height = this->height;
    //cout << "num_children = " << num_children << endl;
    for(int i=0;i<num_children;i++){
        int v_child = c[i];
        Node new_child(v_child);
        new_child.set_height(parent_height+1);
        children.push_back(new_child);
        //children[i].set_parent( this );
    }
}
void Node::set_height(const int h){
    this->height = h;
}
int Node::gNumber(){
    return number;
}
int Node::gNum_children(){
    return num_children;
}
int Node::gHeight(){
    return height;
}
/*
Node* Node::gParent(){
    return parent;
} */
vector<Node> Node::gChildren(){
    return children;
}

int main(){
    cin >> n;
    const int num = n;
    matrix = new int*[num];
    for(int i=0;i<num;i++)
        matrix[i] = new int[num];
    for(int i=0;i<num;i++)
        for(int j=0;j<num;j++)
            cin >> matrix[i][j];
    //for(int i=0;i<num;i++)
    //    for(int j=0;j<num;j++)
    //        cout << matrix[i][j];
    Node root(0);
    has_appeared.push_back(0);
    bool succeed = set_children( root,-1);
    //cout << endl;

    int* height;
    if (succeed){
        height = new int[num];
        height[0] = height_count;
        for(int i=1;i<num;i++){
            height_count = 1;
            has_appeared.clear();
            has_appeared.push_back(i);
            root = Node(i);
            set_children( root, -1);
            height[i] = height_count;
            //cout << endl;
        }
        int lowest_height = 1100;
        for(int i=0;i<num;i++){
            if ( height[i] < lowest_height )
                lowest_height = height[i];
        }
            cout << succeed << " " << lowest_height << endl;
    }else{
        cout << 0 <<endl;
    }

    for(int i=0;i<n;i++){
        //cout << height[i] << ",";
        delete [] matrix[i];
    }
    delete [] matrix;
    delete [] height;
    return 0;
}
bool set_children(Node current, int parent_value){
    // return false if not a tree
    //cout << "current Node's value is " << current.gNumber()<<endl;
    int search_line = current.gNumber();
    vector<int> children_str;
    for(int j=0;j<n;j++){
        if (matrix[search_line][j]==1 && j!=parent_value){
            for(int k=0;k<has_appeared.size();k++){
                if ( j == has_appeared[k])//plural paths
                    return false;
            }
            //still a tree
                children_str.push_back(j);
                has_appeared.push_back(j);
        }
    }
	current.set_children( children_str, parent_value );
    int num_of_new_children = current.gNum_children();
    int new_parent_value = current.gNumber();
    bool status = true, result;

    for(int i=0;i<num_of_new_children;i++){
        if ( current.gChildren()[i].gHeight() >= height_count )
            height_count = current.gChildren()[i].gHeight();
	}
	//cout << "after adding " << current.gNumber() << "'s children, height becomes " << height_count <<endl;

    for(int i=0;i<num_of_new_children;i++){
        bool result = set_children( current.gChildren()[i],new_parent_value);
        //cout << "result of " << current.gChildren()[i].gNumber() << "is " << result <<endl;
        if (result==false){
            status=false;
            break;
    	}
    }
    //cout << "status of " << current.gNumber() << "is " << status <<endl;
    //cout << "height = " << height_count <<endl;
    //cout << "process of " << current.gNumber() << " has finished" <<endl;

    return status;
}
