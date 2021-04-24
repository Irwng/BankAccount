#include "Account.h"

#include <utility>
using namespace std::rel_ops;


/*AccountRecord*/


AccountRecord::AccountRecord(const Date& date,string id,double balance,double amount,string desc)
    :date(date),id(std::move(id)),amount(amount),balance(balance),desc(std::move(desc)){}

void AccountRecord::show() const {
    cout<<date<<"\t#"<<id<<"\t"<<amount<<"\tBalance: "<<balance<<"\t"<<desc<<endl;
}


/*Account*/


double Account::total = 0;
RecordMap Account::recordMap;
Account::Account(const Date& date, string id):id(std::move(id)),balance(0){}

//仅作显示账目和记录余额、总金额，不计算利息
void Account::record(const Date& date, double amount, const string& desc){
    amount = floor(amount*100+0.5)/100; //保留小数点后两位
    balance += amount;
    total +=amount;
    cout<<date<<"\t#"<<id<<"\t"<<amount<<"\tBalance: "<<balance<<"\t"<<desc<<endl;
    AccountRecord accountRecord(date,id,balance,amount,desc);
    recordMap.insert(make_pair(date,accountRecord));
}

void Account::show() const{
    cout<<"#"<<id<<"\tBalance: "<<balance<<endl;
}

ostream & operator << (ostream &out,const Account &account){
    out<<"#"<<account.id<<"\tBalance: "<<account.balance<<endl;
    return out;
}

double Account::getTotal(){
    return total;
}

void Account::query(const Date&begin, const Date&end){
    cout<<"Querying..."<<endl;
    for(auto iter = recordMap.lower_bound(begin);iter!=recordMap.upper_bound(end);iter++){
        (*iter).second.show();
    }
}


/*SavingCount*/


SavingAccount::SavingAccount(const Date& date, const string& id, double rate)
        :Account(date,id),acc(date,0),rate(rate){
    cout<<date<<"\tSavingAccount #"<<id<<" is created"<<endl;
}

void SavingAccount::deposit(const Date& date, double amount,const string& desc) {
    record(date,amount,desc);
    acc.change(date,amount);
}

void SavingAccount::withdrew(const Date& date, double amount, const string& desc) {
    if(amount>getBalance())
        throw AccountException(this,"Not enough balance!");
    record(date, -amount, desc);
    acc.change(date,-amount);
}

void SavingAccount::settle(const Date& date) {
    if(date.getMonth()==1){
        double interest = acc.getSum(date)*rate/365; //计算年息
        record(date, interest,"interest");
        acc.reset(date,0);
    }
}

void SavingAccount::show() const {
    Account::show();
}


/*CreditAccont*/


CreditAccount::CreditAccount(const Date& date, const string& id, double credit, double rate, double fee)
        :Account(date,id),acc(date,0),credit(credit),fee(fee),rate(rate) {
    cout<<date<<"\tCreditAccount #"<<id<<" is created"<<endl;
}

void CreditAccount::deposit(const Date& date, double amount, const string& desc) {
    if(getBalance()>0)
        record(date,amount,desc);
    else{
        record(date,amount,desc);
        if(getBalance()>0){
            acc.change(date,amount-getBalance());
        }else{
            acc.change(date,amount);
        }
    }
}

void CreditAccount::withdrew(const Date& date, double amount, const string& desc) {
    if(amount-getBalance()>credit)
        throw AccountException(this,"Not enough credit!");
    else if(getBalance()>0&&(getBalance()<amount)){
            record(date,-amount,desc);
            acc.change(date,getBalance());
        }
    else if(getBalance()<=0){
        record(date,-amount,desc);
        acc.change(date,-amount);
    }
}

void CreditAccount::settle(const Date& date) {
    double interest = acc.getSum(date)*rate;
    if(interest!=0)
        record(date,interest,"interest");
    if(date.getMonth()==1)
        record(date,-fee,"annual fee");
    acc.reset(date,interest);//尚不清楚debt怎么计算
}

void CreditAccount::show() const {
    Account::show();
    cout<<"\tAvailable credit:"<<getAvailableCredit()<<endl;
}
