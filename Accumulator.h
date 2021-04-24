#ifndef BNAKACCOUNT_ACCUMULATOR_H
#define BNAKACCOUNT_ACCUMULATOR_H

#include "Date.h"

class Accumulator{
private:
    Date lastdate;
    double value;
    double sum;
public:
    Accumulator(const Date& date, double va);
    double getSum(const Date& date)const;
    void change(const Date& date, double va);
    void reset(const Date& date, double va);
};


#endif //BNAKACCOUNT_ACCUMULATOR_H
