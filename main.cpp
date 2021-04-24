/************************************************************
Author: Wangyi     Version: C++11  Date: 2020/3/16
Theme: BankAccount
***********************************************************/
#include "Account.h"
#include "Array.h"

struct deleter{
    template <class T> void operator ()(T*p){delete p;}
};

class Controller{
private:
    Date date;
    char type;
    char cmd;
    int index, day;
    double amount,credit,rate,fee;
    string id, desc;
    Account *account;
    vector<Account*> accounts;
    bool end = false;
public:
    Controller(Date date):date(date){}
    bool runCommand(string cmdline);
    Date getDate(){return date;}
    bool isEnd(){return end;}
};

bool Controller::runCommand(string cmdline) {
    istringstream str(cmdline);
    str>>cmd;
    Date date1,date2;
    switch(cmd){
        case 'a'://增加账户
            str>>type>>id;
            if(type=='s'){
                str>>rate;
                account = new SavingAccount(date,id,rate);
            }else{
                str>>credit>>rate>>fee;
                account = new CreditAccount(date,id,credit,rate,fee);
            }
            accounts.push_back(account);
            return true;
        case 'd'://存入现金
            str>>index>>amount;
            getline(str,desc);
            accounts[index]->deposit(date, amount, desc);
            return true;

        case 'w'://取出现金
            str>>index>>amount;
            getline(str,desc);
            accounts[index]->withdrew(date,amount, desc);
            return true;

        case 's'://显示各账户余额
            for(int i = 0;i<accounts.size(); i++){
                cout<<"["<<i<<"]";
                accounts[i]->show();
                cout<<endl;
            }
            return false;

        case 'c'://改变日期
            str>>day;
            if(day<date.getDay())
                cout<<"You cannot specify a previous day"<<endl;
            else if(day>date.getMaxDay())
                cout<<"Invalid day"<<endl;
            else
                date = Date(date.getYear(),date.getMonth(),day);
            return true;

        case 'n':
            if(date.getMonth()==12)
                date = Date(date.getYear()+1,1,1);
            else
                date = Date(date.getYear(),date.getMonth()+1,1);
            for(auto iter = accounts.begin();iter!=accounts.end();iter++)
                (*iter)->settle(date);
            return true;

        case 'q'://查询一段时间的账目
            date1 = Date::read(str);
            date2 = Date::read(str);
            Account::query(date1,date2);
            return false;
        case 'e':
            end = true;
            return false;
    }
}

int main() {
    Date date(2008,11,1);
    Controller controller(date);
    string cmdLine;
    const char *FILE_NAME = "commands.txt";

    ifstream fileIn(FILE_NAME);
    if(fileIn){
        while(getline(fileIn,cmdLine)){
            try {
                controller.runCommand(cmdLine);
            }catch (exception &e){
                cout<<"Bad line in "<<FILE_NAME<<":"<<cmdLine<<endl;
                cout<<"Error: "<<e.what()<<endl;
                return 1;
            }
        }
        fileIn.close();
    }

    ofstream fileOut(FILE_NAME,ios_base::app);//以追加模式
    cout<<"(a)add account (d)deposit (w)withdrew (s)show"<<endl;
    cout<<"(c)change day (n)next month (e)exit (q)query"<<endl;
    while(!controller.isEnd()){//从标准输入读入命令并执行，直到退出
        cout<<controller.getDate()<<"\tTotal:"<<Account::getTotal()<<"\tcommand>";
        string cmdLine;
        getline(cin,cmdLine);
        try {
            if(controller.runCommand(cmdLine))
                fileOut<<cmdLine<<endl;//将命令写入文件
        }catch (AccountException &e){
            cout<<"Error(#"<<e.getAccount()->getID()<<")"<<e.what()<<endl;
        }catch(exception &e){
            cout<<"Error: "<<e.what()<<endl;
        }
    }
    return 0;
}
/*常用指令
 * a s S3755217 0.015
 * a s 02342342 0.015
 * a c C5392394 10000 0.0005 50
 * c 5
 * d 0 5000 salary
 * c 15
 * w 2 2000 buy a cell
 * c 25
 * d 1 10000 sell the stock
 * n
 * d 2 2016 repay the credit
 * c 5
 * d 0 5500 salary
 * n
 * s
 * q 2008 11 01 2008 11 30
 * q 2008 12 01 2008 12 31*/
