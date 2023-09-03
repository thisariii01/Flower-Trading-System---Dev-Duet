#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class BuyOrder{
public:
   string OrderID;
   string Flower;
   int quantity;
   double price;
};

class SellOrder{
public:
   string OrderID;   
   string Flower;
   int quantity;
   double price;
};


vector<BuyOrder> buyOrders;
vector<SellOrder> sellOrders;

int main() {
   vector<string> data; //vector to store the data

   ifstream file;
   file.open("Flower.csv"); //opening csv file
   string line;
   getline(file, line);

   while (getline(file, line)) { //reading line by line of the csv file
      stringstream ss(line);
      string item;
      while (getline(ss, item, ',')) {
         data.push_back(item);  //getting the data in a line and storing it in a vector
      }


      if (stoi(data[2]) == 1){
         BuyOrder buy;
         buy.OrderID = data[0];
         buy.Flower = data[1];
         buy.quantity = stoi(data[3]);
         buy.price = stoi(data[4]);
         buyOrders.push_back(buy);  
      }
      else{
         SellOrder sell;
         sell.OrderID = data[0];
         sell.Flower = data[1];
         sell.quantity = stoi(data[3]);
         sell.price = stoi(data[4]);
         sellOrders.push_back(sell);
      }
   
      data.clear(); //clearing the vector for the next line
   }

/*     for (auto & i : buyOrders)
   {
      cout << i.OrderID << " " << i.Flower << " " << i.quantity << " " << i.price << endl;
   }
   cout << "sellorders" << endl; //printing the data in the vector
   for (auto & i : sellOrders)
   {
      cout << i.OrderID << " " << i.Flower << " " << i.quantity << " " << i.price << endl;
   } */ 
    file.close();
    return 0;
}
