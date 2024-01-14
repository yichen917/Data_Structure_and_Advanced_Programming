#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Node;
class Tree;
priority_queue<string,vector<string>,greater<string>> to_print;

class Node{
private:
    char character;
    string word;
    vector<Node> children;
public:
    Node( const char character);
    void add_child( const char new_child);
    char g_char();
    string g_word();
    vector<Node>& g_children();
    void set_word( const string word);
};
Node::Node(const char character){
    this->character = character;
    word = "";
    children.clear();
}
void Node::add_child( const char new_child){
    this->children.push_back( Node(new_child) );
}
char Node::g_char(){
    return character;
}
string Node::g_word(){
    return word;
}
vector<Node>& Node::g_children(){
    return children;
}
void Node::set_word( const string word){
    this->word = word;
}

class Tree{
private:
    vector<Node> roots;
public:
    Tree();
    void add_new_word( string new_word);
    vector<Node>& g_roots();
    void print( const string starting);
    void print( Node* starting_node);
};
Tree::Tree(){
    roots.clear();
}
void Tree::add_new_word( string new_word){
    Node* current_node;
    bool need_new_node = true;
    for(int i=0;i<new_word.length();i++){
        need_new_node = true;
        char now = new_word[i];
        if ( i==0 ){
            for(int k=0;k<roots.size();k++)
                if ( roots[k].g_char() == now){
                    current_node = &roots[k];
                    need_new_node = false;
                    break;
                }
            if ( need_new_node ){
                roots.push_back( Node(now));
                current_node = &roots.back();
            }
        }else{
            for(int k=0;k<current_node->g_children().size();k++){
                if ( current_node->g_children()[k].g_char() == now){
                    current_node = &current_node->g_children()[k];
                    need_new_node = false;
                    break;
                }
            }
            if ( need_new_node ){
                current_node->add_child( now );
                current_node = &current_node->g_children().back();
            }
        }
        if ( i==new_word.length()-1){
            current_node->set_word( new_word );
        }
    }
}
void Tree::print( const string starting){
    char now = starting[0];
    bool exist = false;
    Node* starting_node = nullptr;
    for(int i=0;i<roots.size();i++){
        if ( now == roots[i].g_char() ){
            starting_node = &roots[i];
            //cout << starting_node->g_char() << "'s children num = " << starting_node->g_children().size()<<endl;
            if ( starting.length()==1)
                exist = true;
            break;
        }
    }
    for(int i=1;i<starting.length();i++){
        now = starting[i];
        exist = false;
        //cout << "i = " << i << endl;
        //cout << "children num = " << starting_node->g_children().size()<<endl;
        int children_size = starting_node->g_children().size();
        for(int k=0;k<children_size;k++){
            //cout << starting_node->g_children()[k].g_char() << endl;
            if ( now == starting_node->g_children()[k].g_char()){
                starting_node = &starting_node->g_children()[k];
                exist = true;
                break;
            }
        }
        if ( !exist ){
            starting_node = nullptr;
            break;
        }
    }
    //cout << "starting node is " ;
    //if ( starting_node != nullptr)
    //    cout << starting_node->g_char() <<endl;
    //else
    //    cout << " not existed" <<endl;
    this->print(starting_node);
}
void Tree::print(Node* starting_node){
    if ( starting_node != nullptr){
        int children_num = starting_node->g_children().size();
        if ( starting_node->g_word() != "" )
            to_print.push(starting_node->g_word());
        if ( children_num!=0 ){
            for(int i=0;i<children_num;i++)
                this->print( &starting_node->g_children()[i]);
        }
    }
}
int main(){
    Tree prefix_tree;
    int word_num, starting_word_num;
    string new_word,starting_word;
    cin >> word_num >> starting_word_num;
    for(int i=0;i<word_num;i++){
        cin >> new_word;
        prefix_tree.add_new_word( new_word );
    }

    for(int i=0;i<starting_word_num;i++){
        while ( to_print.size()!=0 )
            to_print.pop();
        cin >> starting_word;
        prefix_tree.print(starting_word);
        int ori_size = to_print.size();
        if ( to_print.size()==0)
            cout << endl;
        for(int j=0;j<ori_size;j++){
            cout << to_print.top();
            if ( j== ori_size-1)
                cout << endl;
            else
                cout << " ";
            to_print.pop();
        }
    }
    return 0;
}
