#include <iostream>
#include <string>
#include <stack>
using namespace std;

void display_stack(stack<int> s);

int main(){
    int n;
    string first_line;
    // read adjacency matrix
    cin >> first_line;
    n = (first_line.length()+1)/2;
    int matrix[n][n];
    int index_m = 0;
    for(int i=0; i<first_line.length();i+=2){
        matrix[0][index_m] = stoi(first_line.substr(i,1));
        index_m++;
    }
    for(int i=1; i<n;i++){
        string read;
        cin >> read;
        index_m = 0;
        for (int j=0;j<read.length();j+=2){
            matrix[i][index_m] = stoi(read.substr(j,1));
            index_m++;
        }
    }

    // finish reading
    // start put things into stack
    stack<int> s;
    string hasgone = "";
    s.push(1);
    hasgone += "1";
    cout << 1 << endl;
    int top;
    bool done = false;
    if (n==1 and matrix[0][0]==1)
        done = true;
    while (true){
        bool isinsert = false;
        top = s.top();
        //cout << "top int in stack = " << top <<endl;
        for (int j=0;j<n;j++){
            //cout << "-----------------------" <<endl;
            //cout << "j = " << j <<endl;
            if (matrix[top-1][j]==1 && hasgone.find(to_string(j+1))==string::npos){
                s.push(j+1);
                //cout << j+1 << "has been pushed" <<endl;
                hasgone += to_string(j+1);
                isinsert = true;
                if (j==n-1) done = true;
            }
        }
        if (!isinsert) {
            //cout << top << "has been poped" <<endl;
            s.pop();
        }else{
            //cout << "display the stack: ";
            display_stack(s);
        }
        if (done or s.size()==0) break;
    }
    cout << done ;
    return 0;
}

void display_stack(stack<int> s){
    stack<int> c = s;
    stack<int> d;
    while( c.size()!=0 ){
        d.push(c.top());
        c.pop();
    }
    while( d.size()!=0 ){
        cout << d.top();
        if (d.size()!=1)
            cout << ",";
        else cout << endl;
        d.pop();
    }

}
