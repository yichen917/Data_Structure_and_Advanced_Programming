/*
This assignment involves implementing a simplified Python list.

Question:
Please implement a simplified version of a Python list, and use Python syntax to manipulate the list object. For simplicity, consider only the case where integers are placed in the list.

Common Python list methods include:
• aList.append(elmnt): Add the integer elmnt to the end of aList.
• aList.insert(pos, elmnt): Insert the integer elmnt at position pos in the list. If pos is greater than or equal to the length of the list, place elmnt at the end.
• aList.remove(elmnt): Remove the first occurrence of elmnt from aList.
• aList.index(elmnt): Get the index of the first occurrence of elmnt in aList.
• aList.count(elmnt): Get the number of occurrences of elmnt in aList.
• aList.extend(anotherList): Append the elements of anotherList to the end of aList.

For example, if aList is [1, 2, 3] and anotherList is [5, 6, 7], after this operation, aList becomes [1, 2, 3, 5, 6, 7], while anotherList remains unchanged.
aList.reverse(): Reverse the order of elements in aList.
aList.sort(): Sort the elements of the list in ascending order.
In Python, lists can be declared and initialized as empty using aList = [] or aList = list(). The former is commonly used. Similar to nullptr in C++, it signifies an empty object. 
However, in Python, the return type is not a pointer but an empty object.
*/

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
    int getLength();
public:
    list();
    list(string const name);
    ~list();
    string getName();
    void append(int const newelement);
    void insert(int const position, int const element);
    void remove(const int toRemove);
    int count(const int find);
    int index(const int find);
    void extend(list* anotherList);
    void reverse();
    void sort();
    void print();
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
int list::getLength(){
    return length;
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
void list::remove(const int toRemove){
    Node* current = headPtr;
    Node* preNode;
    for(int i=0;i<length;i++){
        if ( current->getItem()==toRemove){ // remove
            if (i==0){
                headPtr = current->getnextPtr();
                delete current;
            }else{
                preNode->set_nextPtr( current->getnextPtr() );
                delete current;
            }
            length--;
            break;
        }else{
            preNode = current;
            current = current->getnextPtr();
        }
    }
}
int list::count(const int find){
    int cnt = 0;
    Node* current = headPtr;
    for(int i=0;i<length;i++){
        if (current->getItem()==find)
            cnt++;
        current = current->getnextPtr();
    }
    return cnt;
}
int list::index(const int find){
    int pos = -1;
    Node* current = headPtr;
    for(int i=0;i<length;i++){
        if (current->getItem()==find){
            pos = i;
            break;
        }
        current = current->getnextPtr();
    }
    return pos;
}
void list::extend(list* anotherList){
    Node* current = headPtr;
    Node* current2 = anotherList->headPtr;

    for(int i=1;i<length;i++)
        current = current->getnextPtr();
    int copytimes = anotherList->length;
    for(int i=0;i<copytimes;i++){
        this->append( current2->getItem());
        current2 = current2->getnextPtr();
    }
}
void list::reverse(){
    if (length>1){
        Node* pre = headPtr;
        Node* current = headPtr;
        Node* ori_headPtr = headPtr;
        for(int i=0;i<length-1;i++){
            current = current->getnextPtr();
            if (i!=0)
                pre = pre->getnextPtr();
        }
        headPtr = current;
        current->set_nextPtr(pre);
        int times = length-2;
        while(times>0){
            current = ori_headPtr;
            pre = ori_headPtr;
            for(int i=0;i<times;i++){
                current = current->getnextPtr();
                if ( i!=0 )
                    pre = pre->getnextPtr();
            }
            current->set_nextPtr(pre);
            times--;
        }
        current = ori_headPtr;
        current->set_nextPtr(nullptr);
    }
}
void list::sort(){
    for(int j=length-1;j>0;j--){
        Node* pre = headPtr;
        Node* prepre = headPtr;
        Node* next = headPtr->getnextPtr();
    for(int i=0;i<j;i++){
        if ( next->getItem() < pre->getItem()){ //switch
            Node* temp = next;
            pre->set_nextPtr( next->getnextPtr() );
            next = pre;
            pre = temp;
            pre->set_nextPtr(next);
            if (next!=headPtr){
                prepre->set_nextPtr(pre);
            }else{
                headPtr = pre;
                prepre = headPtr;
            }
            //this->print();
        }
        if (i!=j-1)
            next = next->getnextPtr();
        pre = pre->getnextPtr();
        if (i!=0)
            prepre = prepre->getnextPtr();
        //cout << "prepre = " << prepre->getItem()<<endl;
        //cout << "pre = " << pre->getItem() <<endl;
        //cout << "next = " << next->getItem() <<endl;
    }
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
                if(command == "insert"){
                    num1_end_pos = input.find(",");
                    num2_end_pos = input.find(")");
                    int pos = stoi( input.substr(end_pos+1, num1_end_pos - end_pos-1));
                    int ins = stoi( input.substr(num1_end_pos+1, num2_end_pos - num1_end_pos-1));
                    lists[list_pos].insert(pos,ins);
                }else if (command == "reverse" or command == "sort"){
                    if (command == "reverse")
                        lists[list_pos].reverse();
                    else
                        lists[list_pos].sort();
                }else if (command == "extend"){
                    int name_start, name_end;
                    name_start = input.find("(");
                    name_end = input.find(")");
                    string anotherList = input.substr(name_start+1,name_end-name_start-1);
                    int anotherList_pos = -1;
                    for(int i=0;i<existedList;i++)
                        if (lists[i].getName() == anotherList)
                            anotherList_pos = i;
                    lists[list_pos].extend(&lists[anotherList_pos]);
                }else{
                    num1_end_pos = input.find(")");
                    int adjust = stoi( input.substr(end_pos+1,num1_end_pos-end_pos-1));
                    if (command == "append")
                        lists[list_pos].append(adjust);
                    else if (command == "remove")
                        lists[list_pos].remove(adjust);
                    else if (command == "count")
                        cout << lists[list_pos].count(adjust) <<endl;
                    else if (command == "index")
                        cout << lists[list_pos].index(adjust) << endl;
                }
            }
        }
    }
    return 0;
}
