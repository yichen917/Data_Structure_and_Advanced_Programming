/*
This assignment involves Queue data structure and implementation. 

Question:
Consider a service counter with a queue in front. 
When a customer arrives, if the counter is not in use, the customer goes directly to the counter for service. Otherwise, the customer will wait in the queue until the counter is available.
In this scenario, if the arrival time of customers follows an exponential distribution (with parameter λ), and the service time for each customer also follows an exponential distribution (with parameter μ), 
the lengths of these time intervals are determined by probabilities.
According to the probability model, the average waiting time for each customer in the queue () and the average number of customers waiting in the queue per unit time () can be calculated. 

In this question, test data will be provided in the form of multiple customer arrival times and service times, generated based on two given exponential distribution parameters.
Your task is to use a queue to simulate the queuing and waiting situation for each customer. Compare the simulation results with the calculated results from the probability model and output the percentage error.
*/

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
