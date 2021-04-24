#ifndef BNAKACCOUNT_ACCOUNT_H
#define BNAKACCOUNT_ACCOUNT_H

#include "Date.h"
#include "Accumulator.h"

class Account;//前置声明

class AccountRecord{//账目记录
public:
    AccountRecord(const Date& date,string id,double balance,double amount,string desc);
    void show() const;
private:
    Date date;//此处作为输出的日期，不承担排序功能
    double balance; //余额
    string id; //账号
    string desc;//描述
    double amount;//操作金额
};

typedef multimap<Date, AccountRecord> RecordMap;//此处的Date承担排序功能

class Account{
private:
    string id; //账号
    double balance; //余额
    static double total;
    static RecordMap recordMap;
protected:
    //供派生类调用的构造函数，id为账户
    Account(const Date& date, string id);
    //记录一笔账，date为日期，amount为金额，desc为说明
    void record(const Date& date, double amount, const string& desc);
    //报告错误信息
    void error(const string& msg)const{
        cout<<msg<<endl;
    }
public:
    string getID()const {return id;}
    double getBalance()const {return balance;}
    virtual void show() const;
    static double getTotal();
    virtual void deposit(const Date& date, double amount, const string& desc) = 0;
    virtual void withdrew(const Date& date, double amount, const string& desc) = 0;
    virtual void settle(const Date& date) = 0;
    static void query(const Date&begin, const Date&end);
    friend ostream & operator << (ostream &out,const Account &account);
};


class AccountException:public runtime_error{
private:
    const Account *account;
public:
    AccountException(const Account *account, const string &msg)
        :runtime_error(msg),account(account){}
    const Account *getAccount() const {return account;}
};


class SavingAccount:public Account{
private:
    double rate; //存款年利率
    Accumulator acc;

public:
    SavingAccount(const Date& date, const string& id, double rate);

    double GetRate() const {return rate;}

    //存入现金
    void deposit(const Date& date, double amount, const string& desc) override;
    //取出现金
    void withdrew(const Date& date, double amount, const string& desc) override;
    //结算利息，每年1月1日调用一次该函数
    void settle(const Date& date) override;
    void show() const override;
};


class CreditAccount:public Account{
private:
    Accumulator acc;
    double credit;
    double rate;//日利率
    double fee;
public:
    CreditAccount(const Date& date, const string& id, double credit, double rate, double fee);
    double getCredit() const{return credit;}
    double getRate() const{return rate;}
    double getFee() const{return fee;}
    double getAvailableCredit() const{return credit+getBalance();}

    //存入现金
    void deposit(const Date& date, double amount, const string& desc) override ;
    //取出现金
    void withdrew(const Date& date, double amount, const string& desc)override;
    //结算利息，每年1月1日调用一次该函数
    void settle(const Date& date)override;
    void show() const override;
};

#endif //BNAKACCOUNT_ACCOUNT_H
