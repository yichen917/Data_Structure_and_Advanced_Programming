#include <iostream>
#include <queue>
#include <string>
#include <cmath>
using namespace std;

class Customer{
private:
    double arriving_time;
    double served_time;
public:
    Customer();
    Customer(const double arr, const double ser);
    double get_arriving_time();
    double get_served_time();
};
Customer::Customer(){
    arriving_time = served_time = 0;
}
Customer::Customer(const double arr, const double ser){
    arriving_time = arr;
    served_time = ser;
}
double Customer::get_arriving_time() { return arriving_time; }
double Customer::get_served_time() { return served_time; }
int main(){
    queue<Customer> a;
    string read;
    int cus_num;
    double d, u, w, arr, ser, current_time, delay, error;
    delay = 0;
    cin >> cus_num >> d >> u;
    w = d/(u*(u-d));
    for(int i=0;i<cus_num;i++){
        cin >> arr >> ser;
        a.emplace(arr,ser);
    };
    Customer current;
    current = a.front();
    current_time = current.get_arriving_time();
    for(int i=0;i<cus_num;i++){
        current = a.front();
        a.pop();
        if ( current_time > current.get_arriving_time()){ //need to wait
            delay += current_time-current.get_arriving_time();
            current_time += current.get_served_time();
        }else{ // no need to wait
            current_time = current.get_arriving_time()+current.get_served_time();
        }
    }
    delay = delay/cus_num;
    error = (delay-w)/w*100;
    int error_int;
    if ( error>=0 )
        error_int = error+0.5;
    else
        error_int = error-0.5;
    cout << error_int;
    return 0;
}
