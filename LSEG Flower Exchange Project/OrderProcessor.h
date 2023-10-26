//Line by line  vector<string> values of orders will be read from the relevant order files
// Orderbooks buy and sell for each flower will be there //will have max and min heaps respectively
// has getminpriceorder, addto, popminpriceorder, updateminpriceorderquantity,delete,checkempty
// has getmaxpriceorder, addto, popmaxpriceorder, updatemaxpriceorderquantity,delete,checkempty

//2 inputs will be a vector of strings that has a 
//order id, client id, flower, buy or sell, quantity, price and the second will be the order book which is a priority queue 
//check the order flower and buy or sell
// if buy check sell order book for min price match and process accordingly if no match add to buy order book
// if sell check buy order book for max price match and process accordingly if no match add to sell order book
//will have to update the relevant order book
//will have to update the execution report

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include "OrderBook.h"
#include "ExecutionReporter.h"

using namespace std;
        //string OrderID = order[0];
        //string ID = order[1];
        //string flower = order[2];
        //int BuyOrSell = stoi(order[3]); // buy 1 sell 2
        //int Quantity = stoi(order[5]);
        //double Price = stod(order[6]);

ExecutionReporter ExecutionReport;

class OrderProcessor{
    public:
        void Processor(vector<string>& order, BuyOrderBook& buy, SellOrderBook& sell ){
            if (order[3] == "1"){
                if (!sell.isEmpty()){
                    bool flag = false;
                    while (true){
                        vector<string> TopSell = sell.getMinPriceOrder();
                        if (TopSell[6] <= order[6]){ //price
                            if (TopSell[5] == order[5]) { //quantity
                                ExecutionReport.Report("Fill",order);
                                ExecutionReport.Report("Fill",TopSell);
                                sell.popMinPriceOrder();
                                break;
                            }
                            else if (TopSell[5] > order[5]){
                                ExecutionReport.Report("Fill",order);
                                ExecutionReport.Report("PFill",TopSell);
                                sell.updateMinPriceOrderQuantity(stoi(TopSell[5])-stoi(order[5]));
                                break;
                            }
                            else{
                                ExecutionReport.Report("Fill",TopSell);
                                sell.popMinPriceOrder();
                                ExecutionReport.Report("PFill",order);
                                order[5] = to_string(stoi(order[5])-stoi(TopSell[5]));
                                flag  = true;
                            }
                        }
                        else{ // if no order matches the price
                            if (!flag){
                                ExecutionReport.Report("New",order);
                            }
                            buy.addTo(order);
                            break;
                        }
                    }
                }
                else{ //if sell order book is empty
                    ExecutionReport.Report("New",order);
                    buy.addTo(order);
                }
            }
            else{
                if(!buy.isEmpty()){
                    bool flag = false;
                    while(true){
                        vector<string> TopBuy = buy.getMaxPriceOrder();
                        if(TopBuy[6] >= order[6]){
                            if(TopBuy[5] == order[5]){
                                ExecutionReport.Report("Fill",order);
                                ExecutionReport.Report("Fill",TopBuy);
                                buy.popMaxPriceOrder();
                                break;
                            }
                            else if(TopBuy[5] > order[5]){
                                ExecutionReport.Report("Fill",order);
                                ExecutionReport.Report("PFill",TopBuy);
                                buy.updateMaxPriceOrderQuantity(stoi(TopBuy[5])-stoi(order[5]));
                                break;
                            }
                            else{
                                ExecutionReport.Report("Fill",TopBuy);
                                buy.popMaxPriceOrder();
                                ExecutionReport.Report("PFill",order);
                                order[5] = to_string(stoi(order[5])-stoi(TopBuy[5]));
                                flag = true;
                            }
                        }
                        else{ //price doesnt match
                            if (!flag){
                                ExecutionReport.Report("New",order);
                            }
                            sell.addTo(order);
                        }
                    }
                }
                else{
                    ExecutionReport.Report("New",order);
                    sell.addTo(order);
                }
            }
        }
        vector<string> GetExecutionReport(){
            return ExecutionReport.GetExecution();
        }
};
        

