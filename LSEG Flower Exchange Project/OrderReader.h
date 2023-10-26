//A class to read the CSV file that contains orders
// and store them in a vector of orders
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class OrderReader{
    private:
        string filename;
        ifstream file;
        int OrderCount = 0;  // to keep track of the order id

    public:
        //constructor
        OrderReader(string filename,int OrderCount){
            this->filename = filename;
            this->OrderCount = OrderCount;
            file.open(filename); // opening csv file
        };

        //destructor
        ~OrderReader(){
            if (file.is_open()) 
                file.close();
        };

        //function to read the csv file and store the orders in a vector
        vector<vector<string>> read(){
            vector<vector<string>> data; // vector to store the data

            string header; // to skip the header
            getline(file, header);

            string line;

            while (getline(file, line))
            { // reading line by line of the csv file
                OrderCount++;
                stringstream ss(line);
                string item;
                vector<string> row;
                row.clear();
                row.push_back("Order" + to_string(OrderCount));    // adding the order id to the vector
                while (getline(ss, item, ','))
                {
                    row.push_back(item); // getting the data in a line and storing it in a vector
                }
                data.push_back(row);    // clearing the vector for the next line
            }
            return data;
        };

};






