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

using namespace std;
using namespace std::chrono;

class Order
{
public:
    string orderID;
    string ClientID;
    int quantity;
    double price;
};

class OrderBook
{
public:
    vector<Order> TulipBuyOrders;
    vector<Order> TulipSellOrders;

    vector<Order> RoseBuyOrders;
    vector<Order> RoseSellOrders;

    vector<Order> LavenderBuyOrders;
    vector<Order> LavenderSellOrders;

    vector<Order> LotusBuyOrders;
    vector<Order> LotusSellOrders;

    vector<Order> OrchidBuyOrders;
    vector<Order> OrchidSellOrders;

    vector<string> Executions;

    pair<vector<Order> *, vector<Order> *> OrderBookSelection(string flower)
    { // selecting orderbooks according to flower
        if (flower == "Tulip")
        {
            return make_pair(&TulipSellOrders, &TulipBuyOrders);
        }
        else if (flower == "Rose")
        {
            return make_pair(&RoseSellOrders, &RoseBuyOrders);
        }
        else if (flower == "Lavender")
        {
            return make_pair(&LavenderSellOrders, &LavenderBuyOrders);
        }
        else if (flower == "Lotus")
        {
            return make_pair(&LotusSellOrders, &LotusBuyOrders);
        }
        else if (flower == "Orchid")
        {
            return make_pair(&OrchidSellOrders, &OrchidBuyOrders);
        }
        else
        {
            cout << "Invalid Flower" << endl;
            return make_pair(nullptr, nullptr);
        }
    }

    string Timestamp()
    {
        auto now = chrono::system_clock::now(); // Get the current time
        time_t time = chrono::system_clock::to_time_t(now);
        auto ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000; // Extract milliseconds
        struct tm timeInfo;                                                                   // Format the time
        localtime_s(&timeInfo, &time);                                                        // On Windows, use localtime_s

        ostringstream formattedDateTime;
        formattedDateTime << put_time(&timeInfo, "%Y-%m-%d %H:%M:%S:") << setfill('0') << setw(3) << ms.count();
        string dateTimeString = formattedDateTime.str(); // Get the formatted date and time as a string
        return dateTimeString;
    }

    Order CreateOrder(string OrderID, string ID, int Quantity, double Price)
    { // creating order
        Order order;
        order.orderID = OrderID;
        order.ClientID = ID;
        order.quantity = Quantity;
        order.price = Price;
        return order;
    }

    void InsertSellOrder(vector<Order>& sellOrderbook, const Order&newOrder)
    {
        auto it = sellOrderbook.begin();
        while (it != sellOrderbook.end() && (it->price < newOrder.price || (it->price == newOrder.price && it->orderID < newOrder.orderID)))
        {
            ++it;
        }
        sellOrderbook.insert(it, newOrder);
    }

    void InsertBuyOrder (vector<Order>& buyOrderbook, const Order&newOrder)
    {
        auto it = buyOrderbook.begin();
        while (it != buyOrderbook.end() && (it->price > newOrder.price || (it->price == newOrder.price && it->orderID < newOrder.orderID)))
        {
            ++it;
        }
        buyOrderbook.insert(it, newOrder);
    }

    void NewOrder(string OrderID, string ID, string flower, int BuyOrSell, int Quantity, double Price)
    {
        // selecting orderbooks according to flower
        vector<Order> *SelectedSellOrderbook = OrderBookSelection(flower).first;
        vector<Order> *SelectedBuyOrderbook = OrderBookSelection(flower).second;

        // if buy order
        if (BuyOrSell == 1)
        {
            if (!SelectedSellOrderbook->empty())
            {
                for (auto it = SelectedSellOrderbook->begin(); it != SelectedSellOrderbook->end(); ++it)
                {
                    auto &sell = *it;
                    if (sell.price <= Price)
                    {
                        if (sell.quantity == Quantity)
                        {                                                                                                                                                                                                     // if a matched sell order quantity in sell order book is equal to new buy order quantity
                            Executions.push_back(OrderID + "," + ID + "," + flower + "," + "1" + "," + "Fill" + "," + to_string(Quantity) + "," + to_string(sell.price) + " , " + " " + " , " + Timestamp());                 // add completed buy order to executions
                            Executions.push_back(sell.orderID + "," + sell.ClientID + "," + flower + "," + "2" + "," + "Fill" + "," + to_string(Quantity) + "," + to_string(sell.price) + " , " + " " + " , " + Timestamp()); // add completed sell order to executions
                            SelectedSellOrderbook->erase(it);
                            break;
                        }
                        else if (sell.quantity > Quantity)
                        {                                                                                                                                                                                                        // if a matched sell order quantity in sell order book is greater than new buy order quantity
                            Executions.push_back(OrderID + "," + ID + "," + flower + "," + "1" + "," + "Fill" + "," + to_string(Quantity) + "," + to_string(sell.price) + " , " + " " + " , " + Timestamp());                    // add completed buy order to executions
                            Executions.push_back(sell.orderID + "," + (sell).ClientID + "," + flower + "," + "2" + "," + "PFill" + "," + to_string(Quantity) + "," + to_string(sell.price) + " , " + " " + " , " + Timestamp()); // add partially completed sell order to executions
                            sell.quantity -= Quantity;                                                                                                                                                                           // update sell order quantity in sell order book
                            break;
                        }
                        else
                        {                                                                                                                                                                                                          // if a matched sell order quantity in sell order book is less than new buy order quantity
                            Executions.push_back(sell.orderID + "," + sell.ClientID + "," + flower + "," + "2" + "," + "Fill" + "," + to_string(sell.quantity) + "," + to_string(sell.price) + " , " + " " + " , " + Timestamp()); // add completed sell order in sellorderbook  to executions
                            Quantity -= sell.quantity;                                                                                                                                                                             // update remaining quantity of buy order
                            SelectedSellOrderbook->erase(it);                                                                                                                                                                      // delete sell order from sell order book
                            Executions.push_back(OrderID + "," + ID + "," + flower + "," + "1" + "," + "PFill" + "," + to_string(sell.quantity) + "," + to_string(sell.price) + " , " + " " + " , " + Timestamp());                // add partially completed buy order to executions
                            NewOrder(OrderID, ID, flower, 1, Quantity, Price);                                                                                                                                                     // to check if there are more sell orders in sell order book that can be matched with the remaining quantity of buy order
                            break;
                        }
                    }
                    else
                    { // if no sell order in sell order book can be matched with the new buy order
                        Executions.push_back(OrderID + "," + ID + "," + flower + "," + "1" + "," + "New" + "," + to_string(Quantity) + "," + to_string(Price) + " , " + " " + " , " + Timestamp()); // add new buy order to executions
                        InsertBuyOrder(*SelectedBuyOrderbook, CreateOrder(OrderID, ID, Quantity, Price));
                        break;
                    }
                }
            }
            else
            { // if sell order book is empty
                Executions.push_back(OrderID + "," + ID + "," + flower + "," + "1" + "," + "New" + "," + to_string(Quantity) + "," + to_string(Price) + " , " + " " + " , " + Timestamp()); // add new buy order to executions
                InsertBuyOrder(*SelectedBuyOrderbook, CreateOrder(OrderID, ID, Quantity, Price));
            }
        }
        else if (BuyOrSell == 2)
        { // if sell order
            if (!SelectedBuyOrderbook->empty())
            {
                for (auto it = SelectedBuyOrderbook->begin(); it != SelectedBuyOrderbook->end(); ++it)
                {
                    auto &buy = *it;
                    if (buy.price >= Price)
                    { // if there is a buy order in buy order book that can be matched with the new sell order
                        if (buy.quantity == Quantity)
                        {                                                                                                                                                                                                  // if a matched buy order quantity in buy order book is equal to new sell order quantity
                            Executions.push_back(OrderID + "," + ID + "," + flower + "," + "2" + "," + "Fill" + "," + to_string(Quantity) + "," + to_string(buy.price) + " , " + " " + " , " + Timestamp());               // add completed sell order to executions
                            Executions.push_back(buy.orderID + "," + buy.ClientID + "," + flower + "," + "1" + "," + "Fill" + "," + to_string(Quantity) + "," + to_string(buy.price) + " , " + " " + " , " + Timestamp()); // add completed buy order to executions
                            SelectedBuyOrderbook->erase(it);                                                                                                                                                               // delete buy order from buy order book
                            break;
                        }
                        else if (buy.quantity > Quantity)
                        {                                                                                                                                                                                                   // if a matched buy order quantity in buy order book is greater than new sell order quantity
                            Executions.push_back(OrderID + "," + ID + "," + flower + "," + "2" + "," + "Fill" + "," + to_string(Quantity) + "," + to_string(buy.price) + " , " + " " + " , " + Timestamp());                // add completed sell order to executions
                            Executions.push_back(buy.orderID + "," + buy.ClientID + "," + flower + "," + "1" + "," + "PFill" + "," + to_string(Quantity) + "," + to_string(buy.price) + " , " + " " + " , " + Timestamp()); // add partially completed buy order to executions
                            buy.quantity -= Quantity;                                                                                                                                                                       // update buy order quantity in buy order book
                            break;
                        }
                        else
                        {                                                                                                                                                                                                      // if a matched buy order quantity in buy order book is less than new sell order quantity
                            Executions.push_back(buy.orderID + "," + buy.ClientID + "," + flower + "," + "1" + "," + "Fill" + "," + to_string(buy.quantity) + "," + to_string(buy.price) + " , " + " " + " , " + Timestamp()); // add completed buy order to executions
                            Executions.push_back(OrderID + "," + ID + "," + flower + "," + "2" + "," + "PFill" + "," + to_string(buy.quantity) + "," + to_string(buy.price) + " , " + " " + " , " + Timestamp());              // add partially completed sell order to executions
                            Quantity -= buy.quantity;                                                                                                                                                                          // update remaining quantity of sell order
                            SelectedBuyOrderbook->erase(it);                                                                                                                                                                   // delete buy order from buy order book
                            NewOrder(OrderID, ID, flower, BuyOrSell, Quantity, Price);                                                                                                                                         // to check if there are more buy orders in buy order book that can be matched with the remaining quantity of sell order
                            break;
                        }
                    }
                    else
                    { // if no buy order in buy order book can be matched with the new sell order
                        Executions.push_back(OrderID + "," + ID + "," + flower + "," + "2" + "," + "New" + "," + to_string(Quantity) + "," + to_string(Price) + " , " + " " + " , " + Timestamp()); // add new sell order to executions
                        InsertSellOrder(*SelectedSellOrderbook, CreateOrder(OrderID, ID, Quantity, Price));
                    }
                }
            }
            else
            { // if buy order book is empty
                Executions.push_back(OrderID + "," + ID + "," + flower + "," + "2" + "," + "New" + "," + to_string(Quantity) + "," + to_string(Price) + " , " + " " + " , " + Timestamp()); // add new sell order to executions
                InsertSellOrder(*SelectedSellOrderbook, CreateOrder(OrderID, ID, Quantity, Price));
            }
        }
        else
        {
            cout << "Invalid Buy or Sell" << endl;
        }
        return;
    }

    void Validation(string OrderID, string ID, string flower, int BuyOrSell, int Quantity, double Price)
    {

        if (OrderID.empty()) // if order id is empty
        {
            Executions.push_back(OrderID + "," + ID + "," + flower + "," + to_string(BuyOrSell) + "," + "Reject" + "," + to_string(Quantity) + "," + to_string(Price) + "," + "Invalid OrderID" + " , " + Timestamp()); // add completed buy order to executions
            return;
        }
        else if (ID.empty()) // if client id is empty
        {
            Executions.push_back(OrderID + "," + ID + "," + flower + "," + to_string(BuyOrSell) + "," + "Reject" + "," + to_string(Quantity) + "," + to_string(Price) + "," + "Invalid ClientID" + " , " + Timestamp()); // add completed buy order to executions
            return;
        }
        else if (flower.empty() || (flower != "Rose" && flower != "Orchid" && flower != "Lavender" && flower != "Lotus" && flower != "Tulip")) // if flower is empty or invalid
        {
            Executions.push_back(OrderID + "," + ID + "," + flower + "," + to_string(BuyOrSell) + "," + "Reject" + "," + to_string(Quantity) + "," + to_string(Price) + "," + "Invalid Instrument" + " , " + Timestamp());
            return;
        }
        else if (BuyOrSell != 1 && BuyOrSell != 2) // if buy or sell is invalid
        {
            Executions.push_back(OrderID + "," + ID + "," + flower + "," + to_string(BuyOrSell) + "," + "Reject" + "," + to_string(Quantity) + "," + to_string(Price) + "," + "Invalid Side" + " , " + Timestamp());
            return;
        }
        else if (Quantity < 10 || Quantity > 1000 || Quantity % 10 != 0) // if quantity is invalid
        {
            Executions.push_back(OrderID + "," + ID + "," + flower + "," + to_string(BuyOrSell) + "," + "Reject" + "," + to_string(Quantity) + "," + to_string(Price) + "," + "Invalid Quantity" + " , " + Timestamp());
            return;
        }
        else if (Price <= 0) // if price is invalid
        {
            Executions.push_back(OrderID + "," + ID + "," + flower + "," + to_string(BuyOrSell) + "," + "Reject" + "," + to_string(Quantity) + "," + to_string(Price) + "," + "Invalid Price" + " , " + Timestamp());
            return;
        }
        else
        {
            NewOrder(OrderID, ID, flower, BuyOrSell, Quantity, Price); // if all the inputs are valid, then call the NewOrder function
        }
    }

    void printOrderBook()
    { // print order book
        cout << "Tulip Buy Orders" << endl;
        for (auto &i : TulipBuyOrders)
        {
            cout << i.ClientID << " " << i.quantity << " " << i.price << endl;
        }
        cout << "Tulip Sell Orders" << endl;
        for (auto &i : TulipSellOrders)
        {
            cout << i.ClientID << " " << i.quantity << " " << i.price << endl;
        }
        cout << "Rose Buy Orders" << endl;
        for (auto &i : RoseBuyOrders)
        {
            cout << i.ClientID << " " << i.quantity << " " << i.price << endl;
        }
        cout << "Rose Sell Orders" << endl;
        for (auto &i : RoseSellOrders)
        {
            cout << i.ClientID << " " << i.quantity << " " << i.price << endl;
        }
        cout << "Lavender Buy Orders" << endl;
        for (auto &i : LavenderBuyOrders)
        {
            cout << i.ClientID << " " << i.quantity << " " << i.price << endl;
        }
        cout << "Lavender Sell Orders" << endl;
        for (auto &i : LavenderSellOrders)
        {
            cout << i.ClientID << " " << i.quantity << " " << i.price << endl;
        }
        cout << "Lotus Buy Orders" << endl;
        for (auto &i : LotusBuyOrders)
        {
            cout << i.ClientID << " " << i.quantity << " " << i.price << endl;
        }
        cout << "Lotus Sell Orders" << endl;
        for (auto &i : LotusSellOrders)
        {
            cout << i.ClientID << " " << i.quantity << " " << i.price << endl;
        }
        cout << "Orchid Buy Orders" << endl;
        for (auto &i : OrchidBuyOrders)
        {
            cout << i.ClientID << " " << i.quantity << " " << i.price << endl;
        }
        cout << "Orchid Sell Orders" << endl;
        for (auto &i : OrchidSellOrders)
        {
            cout << i.ClientID << " " << i.quantity << " " << i.price << endl;
        }
    }
};