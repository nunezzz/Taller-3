#include <iostream>
#include "Transaction.h"
using namespace std;

// contructor de la clase transacción
Transaction ::Transaction(int ID, int sourceAccount, int destinationAccount, double amount, string date, string hour, string location)
{
    // atributos correspondientes
    this->ID = ID;
    this->sourceAccount = sourceAccount;
    this->destinationAccount = destinationAccount;
    this->amount = amount;
    this->date = date;
    this->hour = hour;
    this->location = location;
}

// getters y setter
int Transaction ::getID() { return this->ID; }
int Transaction ::getSoucerAccount() { return this->sourceAccount; }
int Transaction ::getDestinationAccount() { return this->destinationAccount; }
double Transaction ::getAmount() { return this->amount; }
string Transaction ::getDate() { return this->date; }
string Transaction ::getHour() { return this->hour; }
string Transaction ::getLocation() { return this->location; }
void Transaction ::setID(int ID) { this->ID = ID; }
void Transaction ::setSourceAccount(int sourceAccount) { this->sourceAccount = sourceAccount; }
void Transaction ::setDestinationAccount(int destinationAccount) { this->destinationAccount = destinationAccount; }
void Transaction ::setAmount(double amount) { this->amount = amount; }
void Transaction ::setDate(string date) { this->date = date; }
void Transaction ::setHour(string hour) { this->hour = hour; }
void Transaction ::setLocation(string location) { this->location = location; }
