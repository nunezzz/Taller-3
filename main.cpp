#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include <set>
#include "Transaction.h"
#include "Node.h"
#include "AVLTree.h"
#include "NodeABB.h"
#include "ABB.h"
using namespace std;

queue<Transaction *> transactions; // queue que contiene todas las transacciones
AVLTree transactionTree;
ABB transactionABB;
queue<Transaction *> suspiciousTransactionsQueue; // Cola para almacenar las transacciones sospechosas

vector<string> lines(string str, char dif) // separa los elementos de mi archivo por partes
{
    vector<string> parts;
    stringstream ss(str);
    string part;
    while (getline(ss, part, dif))
    {
        parts.push_back(part);
    }
    return parts;
}
void readFile() // lee el txt y guarda los datos en una cola, tambien inserta los datos a AVL y ABB
{
    string line;
    ifstream file("transacciones.txt");
    char dif = ',';
    while (getline(file, line))
    {
        vector<string> part = lines(line, dif);
        int ID = stoi(part[0]); // el stoi me pasa de string a int
        int sourceAccount = stoi(part[1]);
        int destinationAccount = stoi(part[2]);
        double amount = stod(part[3]); // el stod me pasa de string a double
        string date = part[4];
        string hour = part[5];
        string location = part[6];

        Transaction *newTransaction = new Transaction(ID, sourceAccount, destinationAccount, amount, date, hour, location); // instancia un objeto de tipo transacción
        transactions.push(newTransaction);                                                                                  // se agrega el objeto instanciado a la cola
        transactionTree.insert(newTransaction);                                                                             // se agrega el objeto instanciado a AVL
        transactionABB.insert(newTransaction);                                                                              // se agrega el objeto instanciado a ABB
    }
    file.close();
}
void newFile(Transaction *trans) // sobre escribe el archivo original
{
    ofstream file("transacciones.txt", ios::app);
    if (!file.is_open())
    {
        cout << "ERROR" << endl;
        return;
    }
    int ID = trans->getID();
    string id = to_string(ID); // el to_string pasa de in/double a un string
    int sourceAccount = trans->getSoucerAccount();
    string source = to_string(sourceAccount);
    int destinationAccount = trans->getDestinationAccount();
    string destination = to_string(destinationAccount);
    double amount = trans->getAmount();
    string money = to_string(amount);
    string data = id + "," + source + "," + destination + "," + money + "," + trans->getDate() + "," + trans->getHour() + "," + trans->getLocation() + "\n";
    file << data; // agrega los datos nuevos al txt

    file.close();
}
/*
Función que agrega una nueva transacción
*/
void enterTransaction()
{
    // pide los respectivos datos por pantalla
    cout << "Ingrese ID: ";
    int ID;
    cin >> ID;
    cout << "Ingrese cuenta de origen: ";
    int sourceAccount;
    cin >> sourceAccount;
    cout << "Ingrese cuenta destino: ";
    int destinationAccount;
    cin >> destinationAccount;
    cout << "Ingrese monto: ";
    double amount;
    cin >> amount;
    cout << "Ingrese la fecha (dd/mm/aaaa): ";
    string date;
    cin >> date;
    cout << "Ingrese la hora(hh:mm): ";
    string hour;
    cin >> hour;
    cout << "Ingrese la ubicación: ";
    string location;
    cin.ignore();
    getline(cin, location); // sirve para ignorar los espacios

    Transaction *newTransaction = new Transaction(ID, sourceAccount, destinationAccount, amount, date, hour, location); // se instancia un objeto del tipo transacción
    transactions.push(newTransaction);
    transactionTree.insert(newTransaction);
    transactionABB.insert(newTransaction);
    newFile(newTransaction); // agrega los nuevos datos creados al txt

    cout << "** Transacción registrada con exito **" << endl;
    cout << "Desea realizar otra transacción" << endl;
    cout << "1) Si\n"
         << "2) No\n"
         << "Seleccione una opción: ";
    int op;
    cin >> op;

    while (op != 2)
    {
        cout << "Ingrese ID: ";
        cin >> ID;
        cout << "Ingrese cuenta de origen: ";
        cin >> sourceAccount;
        cout << "Ingrese cuenta destino: ";
        cin >> destinationAccount;
        cout << "Ingrese monto: ";
        cin >> amount;
        cout << "Ingrese la fecha (dd/mm/aaaa): ";
        cin >> date;
        cout << "Ingrese la hora(hh:mm): ";
        cin >> hour;
        cout << "Ingrese la ubicación: ";
        cin.ignore();
        getline(cin, location);

        Transaction *newTransaction = new Transaction(ID, sourceAccount, destinationAccount, amount, date, hour, location);
        transactions.push(newTransaction);
        transactionTree.insert(newTransaction);
        transactionABB.insert(newTransaction);
        newFile(newTransaction); // agrega los nuevos datos creados al txt

        cout << "";
        cout << "** Transacción registrada con exito **" << endl;
        cout << "Desea realizar otra transacción" << endl;
        cout << "1) Si\n"
             << "2) No\n"
             << "Seleccione una opción: ";
        cin >> op;
    }
}
/*
Función que busca una determinada transacción en base a su ID
*/
void searchTransaction()
{
    cout << "___________________________________________" << endl;
    cout << "Ingrese el ID de la transacción: ";
    int ID;
    cin >> ID;
    Transaction *trans = transactionTree.search(ID); // llama al metodo search del objeto transactionTree que es una instancia de la clase AVLTree
    if (trans != nullptr)                            // si no apunta a nulo se despliega la transacción correspondiente
    {
        cout << "___________________________________________" << endl;
        cout << "-> ID: " << ID << "|Cuenta de origen: " << trans->getSoucerAccount() << "|Cuenta destino: " << trans->getDestinationAccount() << "|Monto: " << trans->getAmount() << "|Fecha: " << trans->getDate() << "|Hora: " << trans->getHour() << "|Ubicación: " << trans->getLocation() << endl;
    }
    else
    {
        cout << "* No se ha encontrado ninguna transacción con ese ID" << endl;
    }
    cout << "" << endl;
    cout << "Desea realizar otra busqueda: " << endl;
    cout << "1) Si\n"
         << "2) No\n"
         << "Seleccione una opción: ";
    int op;
    cin >> op;
    while (op != 2)
    {
        cout << "___________________________________________" << endl;
        cout << "Ingrese el ID de la transacción: ";
        int ID;
        cin >> ID;
        Transaction *trans = transactionTree.search(ID);
        if (trans != nullptr)
        {
            cout << "___________________________________________" << endl;
            cout << "-> ID: " << ID << "|Cuenta de origen: " << trans->getSoucerAccount() << "|Cuenta destino: " << trans->getDestinationAccount() << "|Monto: " << trans->getAmount() << "|Fecha: " << trans->getDate() << "|Hora: " << trans->getHour() << "|Ubicación: " << trans->getLocation() << endl;
        }
        else
        {
            cout << "* No se ha encontrado ninguna transacción con ese ID" << endl;
        }
        cout << "" << endl;
        cout << "Desea realizar otra busqueda: " << endl;
        cout << "1) Si\n"
             << "2) No\n"
             << "Seleccione una opción: ";
        cin >> op;
    }
}
/* Función me busca las transacciones sospechosas en base a diferentes criterios */
void transactionLimit()
{
    queue<suspiciousAccount> suspiciousAccounts;
    transactionABB.suspiciousTransactions(suspiciousAccounts);

    if (!suspiciousAccounts.empty())
    {
        set<int> uniqueAccounts;
        cout << "\n** Transacciones sospechosas ** " << endl;

        // Convertir la cola de transacciones a un vector para facilitar la iteración
        vector<Transaction *> transactionsVector;
        while (!transactions.empty())
        {
            transactionsVector.push_back(transactions.front());
            transactions.pop();
        }
        while (!suspiciousAccounts.empty())
        {
            suspiciousAccount account = suspiciousAccounts.front();
            suspiciousAccounts.pop();
            if (uniqueAccounts.insert(account.accountNumber).second)
            {
                cout << "-> Num. Cuenta: " << account.accountNumber << " - " << account.reason << endl;

                // Guardar las transacciones sospechosas
                for (Transaction *trans : transactionsVector)
                {
                    if (trans->getSoucerAccount() == account.accountNumber)
                    {
                        suspiciousTransactionsQueue.push(trans);
                    }
                }
            }
        }
    }
    else
    {
        cout << "** No hay transaferencias sospechosas **" << endl;
    }
}
/* Función que me genera los reportes de todas las transacciones sospechosas con sus determinados datos*/
void transactionReports()
{
    if (!suspiciousTransactionsQueue.empty())
    {
        cout << "\n** Reporte de Transacciones Sospechosas **" << endl;
        while (!suspiciousTransactionsQueue.empty())
        {
            Transaction *trans = suspiciousTransactionsQueue.front();
            suspiciousTransactionsQueue.pop();
            cout << "\nID: " << trans->getID()
                 << "\nCuenta de Origen: " << trans->getSoucerAccount()
                 << "\nCuenta Destino: " << trans->getDestinationAccount()
                 << "\nMonto: " << trans->getAmount()
                 << "\nFecha: " << trans->getDate()
                 << ", Hora: " << trans->getHour()
                 << ", Ubicación: " << trans->getLocation() << endl;
        }
    }
    else
    {
        cout << "** No hay transacciones sospechosas para mostrar **" << endl;
    }
}

/*
Función que despliega el menú del programa
*/
void menu()
{
    cout << "-------------------------" << endl;
    cout << "         MENU" << endl;
    cout << "-------------------------" << endl;
    cout << "1) Ingresar Transacción\n"
         << "2) Buscar Transacción\n"
         << "3) Detección transacciones sospechosas\n"
         << "4) Historial Transaccion sospechosas\n"
         << "5) Salir\n"
         << "Seleccione una opción: ";
    int option;
    cin >> option;
    while (option != 5)
    {
        switch (option)
        {
        case 1:
            enterTransaction();
            break;
        case 2:
            searchTransaction();
            break;
        case 3:
            transactionLimit();
            break;
        case 4:
            transactionReports();
            break;
        }
        cout << "\n"
             << "-------------------------\n"
             << "         MENU\n"
             << "-------------------------" << endl;
        cout << "1) Ingresar Transacción\n"
             << "2) Buscar Transacción\n"
             << "3) Detección transacciones sospechosas\n"
             << "4) Historial Transaccion sospechosas\n"
             << "5) Salir\n";
        cout << "Seleccione una opción: ";
        cin >> option;
    }
    cout << "-------------------------" << endl;
    cout << "         MENU" << endl;
    cout << "-------------------------" << endl;
    cout << "1) Ingresar Transacción\n"
         << "2) Buscar Transacción\n"
         << "3) Modificar Transacción\n"
         << "4) Historial Transaccion sospechosas\n"
         << "5) salir\n";
    cin >> option;
}

int main()
{
    readFile();
    menu();
    // realiza limpieza
    while (!transactions.empty())
    {
        delete transactions.front();
        transactions.pop();
    }
    return 0;
}
