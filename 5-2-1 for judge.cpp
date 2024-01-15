#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Node{
private:
    Node* nextPtr;
    int item;
public:
    Node(int const item);
    int getItem();
    Node* getnextPtr();
    void set_nextPtr( Node& nextNode);
    void set_nextPtr( Node* nextNode);
    //bool operator==(Node compare);
friend class list;
};
Node::Node(int const item){
    nextPtr = nullptr;
    this->item = item;
}
int Node::getItem(){
    return item;
}
Node* Node::getnextPtr(){
    return nextPtr;
}
void Node::set_nextPtr( Node& nextNode){
    this->nextPtr = &nextNode;
}
void Node::set_nextPtr(Node* nextNode){
    this->nextPtr = nextNode;
}
/*
bool Node::operator==(Node compare){
    if (this->item == compare.getItem()
        && this->nextPtr == compare.getnextPtr())
            return true;
    else return false;
} */

class list{
private:
    string name;
    Node* headPtr;
    int length;
public:
    list();
    list(string const name);
    ~list();
    string getName();
    void append(int const newelement);
    void print();
    void insert(int const position, int const element);
};
list::list(){
    name = "";
    headPtr = nullptr;
    length =0;
}
list::list(string const name){
    this->name = name;
    headPtr = nullptr;
    length = 0;
}
list::~list(){
    Node* temp;
    while ( headPtr!= nullptr){
        temp = headPtr;
        headPtr = headPtr->getnextPtr();
        delete temp;
    }
}
string list::getName(){
    return name;
}
void list::append(int const newelement){
    Node* add = new Node(newelement);
    if (length==0){
        headPtr = add;
    }
    else{
        Node* current = headPtr;
        while( current->getnextPtr() != nullptr){
            current = current->getnextPtr();
        }
        current->set_nextPtr(add);
    }
    length++;
}
void list::insert(int const pos, int const elem){
    if (pos>=length){
        this->append(elem);
    }else if( pos==0 ){
        Node* add = new Node(elem);
        add->set_nextPtr( headPtr );
        headPtr = add;
        length++;
    }else{
        Node* current = headPtr;
        Node* add = new Node(elem);
        for(int i=0;i<pos-1;i++){
            current = current->getnextPtr();
        }
        add->set_nextPtr( current->getnextPtr() );
        current->set_nextPtr(add);
        length++;
    }
}
void list::print(){
    Node* current = headPtr;
    cout << "[";
    for(int i=0;i<length;i++){
        cout << current->getItem();
        if (i!=length-1) cout << ",";
        current = current->getnextPtr();
    }
    cout << "]" << endl;
}
int main(){
    list* lists = new list[30];
    int existedList = 0;
    string input ;

    while( getline(cin,input) ){
        if ( input.find("=")!=string::npos ) // create new list
        {   int equ = input.find("=");
            string listName = input.substr(0,equ-1);
            lists[existedList] = list(listName);
            existedList++;
        }else{
            string command, listName;
            int start_pos=0,end_pos=0, num1_end_pos = 0, num2_end_pos = 0;
            if ( input.find("(")==string::npos ){ // print
                for(int i=0;i<existedList;i++)
                if ( lists[i].getName()== input )
                    lists[i].print();
            }
            else{
                string name;
                start_pos = input.find(".");
                end_pos = input.find("(");
                command = input.substr(start_pos+1,end_pos-start_pos-1);
                name = input.substr(0,start_pos);
                int list_pos = -1;
                for(int i=0;i<existedList;i++)
                    if ( lists[i].getName() == name )
                        list_pos = i;
                if (command == "append"){
                    num1_end_pos = input.find(")");
                    int app = stoi( input.substr(end_pos+1,num1_end_pos-end_pos-1));
                    lists[list_pos].append(app);
                }else if(command == "insert"){
                    num1_end_pos = input.find(",");
                    num2_end_pos = input.find(")");
                    int pos = stoi( input.substr(end_pos+1, num1_end_pos - end_pos-1));
                    int ins = stoi( input.substr(num1_end_pos+1, num2_end_pos - num1_end_pos-1));
                    lists[list_pos].insert(pos,ins);
                }
            }
        }
    }
    // delete lists;
    return 0;
}
