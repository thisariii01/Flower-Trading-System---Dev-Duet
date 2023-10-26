//check whether the order is valid and return the reject condition
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip> 

using namespace std;

class Validator{
public:
        string isValidOrder(const vector<string>& order) {
        //string OrderID = order[0];
        //string ID = order[1];
        //string flower = order[2];
        //int BuyOrSell = stoi(order[3]);
        //int Quantity = stoi(order[5]);
        //double Price = stod(order[6]);

        if (order[0].empty()) {
            //Executions.push_back(order[0] + "," + order[1] + "," + order[2] + "," + (order[3]) + "," + "Reject" + "," + (order[5]) + "," + (order[6]) + "," + "Invalid OrderID" + " , " + Timestamp());
            return "Invalid OrderID";
        } else if (order[1].empty()) {
            //Executions.push_back(order[0] + "," + order[1] + "," + order[2] + "," + (order[3]) + "," + "Reject" + "," + (order[5]) + "," + (order[6]) + "," + "Invalid ClientID" + " , " + Timestamp());
            return "Invalid ClientID";
        } else if (order[2].empty() || (order[2] != "Rose" && order[2] != "Orchid" && order[2] != "Lavender" && order[2] != "Lotus" && order[2] != "Tulip")) {
            //Executions.push_back(order[0] + "," + order[1] + "," + order[2] + "," + (order[3]) + "," + "Reject" + "," + (order[5]) + "," + (order[6]) + "," + "Invalid Instrument" + " , " + Timestamp());
            return "Invalid Instrument";
        } else if (order[3].empty() || order[3] != "1" && order[3] != "2") {
            //Executions.push_back(order[0] + "," + order[1] + "," + order[2] + "," + (order[3]) + "," + "Reject" + "," + (order[5]) + "," + (order[6]) + "," + "Invalid Side" + " , " + Timestamp());
            return "Invalid Side";
        } else if (order[4].empty()) {
            //Executions.push_back(order[0] + "," + order[1] + "," + order[2] + "," + (order[3]) + "," + "Reject" + "," + (order[5]) + "," + (order[6]) + "," + "Invalid Quantity" + " , " + Timestamp());
            return "Invalid Quantity";
        }else if (stoi(order[4]) < 10 || stoi(order[4]) > 1000 || stoi(order[4]) % 10 != 0){
                return "Invalid Quantity";
        }else if (order[5].empty()){
            return "Invalid Price";
        }else if (stod(order[5]) <= 0 ) {
            //Executions.push_back(order[0] + "," + order[1] + "," + order[2] + "," + (order[3]) + "," + "Reject" + "," + (order[5]) + "," + (order[6]) + "," + "Invalid Price" + " , " + Timestamp());
            return "Invalid Price";
        }return "Valid";
    };
};
