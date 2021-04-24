#include "Accumulator.h"
#include <iostream>
using namespace std;

Accumulator::Accumulator(const Date& date, double va)
    :lastdate(date),value(va),sum(0){
}

double Accumulator::getSum(const Date& date) const {
//    cout<<"get the sum: "<<(sum + value*(date-lastdate))<<endl;
//    cout<<"get the value: "<<value<<endl;
    return sum + value*(date-lastdate);

}

void Accumulator::change(const Date& date, double va) {
//    cout<<"get the value after change: "<<value<<endl;
    sum += value*(date-lastdate);
    value += va;
//    cout<<"get the value after change: "<<value<<endl;
    lastdate = date;
}

void Accumulator::reset(const Date& date, double va) {
    lastdate = date;
    value += va;
    sum = 0;
}
