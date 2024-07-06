#include "ABB.h"
#include "Transaction.h"
#include <stack>
#include <queue>
#include <iostream>
#include <set>
using namespace std;

ABB::ABB() : root(nullptr) {}

// Función para insertar una transacción en el ABB
NodeABB *ABB::insert(NodeABB *node, Transaction *transaction)
{
    if (node == nullptr)
    {
        return new NodeABB(transaction);
    }
    if (transaction->getID() < node->transaction->getID())
    {
        node->left = insert(node->left, transaction);
    } // si el menor a la raiz insertarlo por la izquierda
    else if (transaction->getID() > node->transaction->getID())
    {
        node->right = insert(node->right, transaction);
    } // si es mayor a la raiz lo inserto por la derecha
    return node;
}
void ABB::insert(Transaction *transaction) // inserta el nuevo nodo raiz al arbol
{
    root = insert(root, transaction);
}
NodeABB *ABB::search(NodeABB *node, int data)
{
    if (node == nullptr || node->transaction->getID() == data)
    {
        return node;
    }
    if (data < node->transaction->getID())
    {
        return search(node->left, data);
    } // si el dato es menor a la raiz busco en el lado izquiero de mi arbol
    else
    {
        return search(node->right, data);
    } // si el dato es mayor busco en el lado derecho de mi arbol
}
// Función para buscar una transacción por su ID
Transaction *ABB::search(int data)
{
    NodeABB *result = search(root, data);
    if (result != nullptr)
    {
        return result->transaction;
    }
    else
    {
        return nullptr;
    }
}
void ABB::inOrder(NodeABB *node)
{
    if (node != nullptr)
    {
        inOrder(node->left);
        cout << node->transaction->getID() << endl;
        inOrder(node->right);
    }
}
void ABB::inOrder()
{
    inOrder(root);
}

// Función para encontrar transacciones sospechosas y llenar la cola con cuentas sospechosas
void ABB::suspiciousTransactions(queue<suspiciousAccount> &suspiciousAccounts)
{
    findSuspiciousTransactions(root, suspiciousAccounts);
}
// Función para buscar transacciones sospechosas
void ABB::findSuspiciousTransactions(NodeABB *node, queue<suspiciousAccount> &suspiciousAccounts)
{
    if (node == nullptr)
        return;

    vector<Transaction *> transList;                // Vector para almacenar las transacciones del subárbol
    collectTransactions(node, transList);           // Recoge todas las transacciones en el vector
    checkConditions(transList, suspiciousAccounts); // Verifica las condiciones para determinar si las transacciones son sospechosas

    findSuspiciousTransactions(node->left, suspiciousAccounts);  // Busca en el subárbol izquierdo
    findSuspiciousTransactions(node->right, suspiciousAccounts); // Busca en el subárbol derecho
}
// Función para recolectar todas las transacciones en un vector
void ABB::collectTransactions(NodeABB *node, vector<Transaction *> &transList)
{
    if (node == nullptr)
        return;

    collectTransactions(node->left, transList);
    transList.push_back(node->transaction);
    collectTransactions(node->right, transList);
}
// Función para convertir el tiempo en un entero representando el tiempo en minutos
int timeToInt(const string &time)
{
    int hours = stoi(time.substr(0, 2));   // Obtiene las horas de la cadena
    int minutes = stoi(time.substr(3, 2)); // Obtiene los minutos de la cadena
    return hours * 100 + minutes;          // Convierte las horas y minutos en un entero en formato HHMM
}
// Función para calcular la diferencia en minutos entre dos tiempos en formato HHMM
int differenceInMinutes(int startTime, int endTime)
{
    int startHours = startTime / 100;                                  // horas tiempo inicial
    int startMinutes = startTime % 100;                                // minutos tiempo inicial
    int endHours = endTime / 100;                                      // horas tiempo fina
    int endMinutes = endTime % 100;                                    // minutos tiempo final
    return (endHours - startHours) * 60 + (endMinutes - startMinutes); // Calcula la diferencia en minutos
}
// Función para verificar si las transacciones cumplen con alguna de las condiciones de sospecha
void ABB::checkConditions(vector<Transaction *> &transList, queue<suspiciousAccount> &suspiciousAccounts)
{
    // Ordena las transacciones por fecha y hora
    sort(transList.begin(), transList.end(), [](Transaction *a, Transaction *b)
         { return a->getDate() + " " + a->getHour() < b->getDate() + " " + b->getHour(); });

    for (size_t i = 0; i + 4 < transList.size(); ++i)
    {
        string startDate = transList[i]->getDate();   // Obtiene la fecha de la primera transacción en el grupo
        string endDate = transList[i + 4]->getDate(); // Obtiene la fecha de la última transacción en el grupo

        int startTime = timeToInt(transList[i]->getHour());   // Convierte la hora de la primera transacción en minutos
        int endTime = timeToInt(transList[i + 4]->getHour()); // Convierte la hora de la última transacción en minutos

        if (startDate == endDate)
        {
            int duration = differenceInMinutes(startTime, endTime); // Calcula la duración en minutos entre la primera y la última transacción

            // Verifica si alguna transacción excede el monto de 500,000
            for (const auto &transaction : transList)
            {
                if (transaction->getAmount() > 500000)
                {
                    suspiciousAccounts.push({transaction->getSoucerAccount(), "* Excede limite de monto a transferir *"});
                    break; // Salir del bucle para evitar añadir la misma cuenta varias veces
                }
            }
            if (duration <= 10)
            { // Si hace varias transacciones en intervalos de menos de 10 minutos, sospecha
                suspiciousAccounts.push({transList[i]->getSoucerAccount(), "* Excede el limite de transacción en 10 minutos *"});
                break;
            }

            if (duration <= 60)
            { // Condición en menos de 1 hora
                set<string> locations;
                for (size_t j = i; j <= i + 4; ++j)
                {
                    locations.insert(transList[j]->getLocation());
                }
                if (locations.size() >= 5)
                { // Si tiene más de 5 ubicaciones distintas en menos de 1 hora, sospecha
                    suspiciousAccounts.push({transList[i]->getSoucerAccount(), "* Excede el limite de transacción de 5 ubicaciones distintas *"});
                    break;
                }
            }
        }
    }
}
