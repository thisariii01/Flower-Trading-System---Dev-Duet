#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <cstring>
#include <chrono>
#include <ctime>
#include <utility>
#include "orders.h"

using namespace std;

int main()
{
    int OrderCount = 0;  // to keep track of the order id
    vector<string> data; // vector to store the data

    ifstream file;
    file.open("Flower.csv"); // opening csv file
    string line;
    getline(file, line);
    OrderBook flower_order; // creating an object of the class Flower
    while (getline(file, line))
    { // reading line by line of the csv file
        OrderCount++;
        stringstream ss(line);
        string item;
        while (getline(ss, item, ','))
        {
            data.push_back(item); // getting the data in a line and storing it in a vector
        }
        data.push_back("Order" + to_string(OrderCount));                                                 // adding the order id to the vector
        flower_order.Validation(data[5], data[0], data[1], stoi(data[2]), stoi(data[3]), stod(data[4])); // calling the Validation function
        data.clear();                                                                                    // clearing the vector for the next line
    }
    file.close();

    fstream fout;
    remove("ExecutionReport.csv");                         // removing the execution report if it already exists
    fout.open("ExecutionReport.csv", ios::out | ios::app); // generating the execution report
    fout << "OrderID"
         << ","
         << "Client Order ID"
         << ","
         << "Instrument"
         << ","
         << "Side"
         << ","
         << "Exec Status"
         << ","
         << "Quantity"
         << ","
         << "Price"
         << ","
         << "Reasons"
         << ","
         << "Transaction time" << endl;
    for (auto it = flower_order.Executions.begin(); it != flower_order.Executions.end(); ++it)
    {
        fout << *it << endl;
    }
    fout.close();
    flower_order.printOrderBook(); // printing the order book
}
