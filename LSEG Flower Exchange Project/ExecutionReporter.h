//Executions.push_back(OrderID + "," + ID + "," + flower + "," + to_string(BuyOrSell) + "," + "Reject" + "," + to_string(Quantity) + "," + to_string(Price) + "," + "Invalid OrderID" + " , " + Timestamp()); // add completed buy order to executions
//Executions.push_back(OrderID + "," + ID + "," + flower + "," + "1" + "," + "Fill" + "," + to_string(Quantity) + "," + to_string(sell.price) + " , " + " " + " , " + Timestamp());  // add completed buy order to executions
//2 inputs 1 - string status  2 - Order vector      //(Validation,Pfill,Fill)
//if validation !Valid, execution status = reject, reason : Validation
//if Pfill, execution status = Pfill , reason: ""
//if Fill, execution status = Fill , reason: ""
//Execution.push_back(OrderID + "," + ID + "," + flower + "," + to_string(BuyOrSell) + "," + "ExecutionStatus" + "," + to_string(Quantity) + "," + to_string(Price) + "," + "Reason" + " , " + Timestamp()); // add completed buy order to executions
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#include "Timestamp.h" // Include the timestamp header

class ExecutionReporter {
public:
    void Report(const string& status, vector<string>& orders) {
        TimestampGenerator timestampGenerator; // Create an instance of TimestampGenerator
            string timestamp = timestampGenerator.GenerateTimestamp();
            // Depending on the status, update the Execution vector
            if (status != "Valid") {
                execution_.push_back(GenerateExecutionString(orders, "Reject", status, timestamp));
            }
            else if (status == "Pfill") {
                execution_.push_back(GenerateExecutionString(orders, "Pfill", "", timestamp));
            } else{
                execution_.push_back(GenerateExecutionString(orders, "Fill", "", timestamp));
            }
    }

    vector<string> GetExecution() {
        return execution_;
    }

private:
    vector<string> execution_; // Vector to store the execution information
    string GenerateExecutionString(vector<string> order, string executionStatus, string reason, string timestamp) {
        // Generate the execution string based on the order and status
        //stringstream ss;
        //ss << order.at(0) << "," << order.at(1) << "," << order.at(2) << "," << order.at(3) << "," << executionStatus << "," << order.at(4) << "," << order.at(5) << "," << reason << " , " << timestamp;
        string executionString;
        //cout << order[0] + "," + order[1] + "," + order[2] + "," + order[3] + "," + executionStatus + "," + order[4] + "," + order[5] + "," + reason + " , " + timestamp; 
        executionString = order[0] + "," + order[1] + "," + order[2] + "," + order[3] + "," + executionStatus + "," + order[4] + "," + order[5] + "," + reason + " , " + timestamp; 
        return executionString;
    }
};

        //string OrderID = order[0];
        //string ID = order[1];
        //string flower = order[2];
        //int BuyOrSell = stoi(order[3]);
        //int Quantity = stoi(order[4]);
        //double Price = stod(order[5]);