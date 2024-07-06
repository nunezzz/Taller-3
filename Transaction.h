#pragma once
#include <iostream>
using namespace std;

class Transaction
{
private:
    int ID;
    int sourceAccount;
    int destinationAccount;
    double amount;
    string date;
    string hour;
    string location;

public:
    Transaction(int, int, int, double, string, string, string);

    int getID();
    int getSoucerAccount();
    int getDestinationAccount();
    double getAmount();
    string getDate();
    string getHour();
    string getLocation();

    void setID(int);
    void setSourceAccount(int);
    void setDestinationAccount(int);
    void setAmount(double);
    void setDate(string);
    void setHour(string);
    void setLocation(string);
};