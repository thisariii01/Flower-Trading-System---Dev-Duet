#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

        //string OrderID = order[0];
        //string ID = order[1];
        //string flower = order[2];
        //int BuyOrSell = stoi(order[3]);
        //int Quantity = stoi(order[5]);
        //double Price = stod(order[6]);


// Define the structure to store complete order information
// struct CompleteOrder {
//     string orderID;
//     string clientID;
//     string flower;
//     string BuyOrSell;
//     string Quantity;
//     string Price;
    
//     CompleteOrder(const string& o, const string& c, const string& f, const string& b, const string& q, const string& p)
//         : orderID(o), clientID(c), flower(f), BuyOrSell(b), Quantity(q), Price(p) {}

    // Custom comparator for prioritizing by price and order ID
    struct Comparator {
        bool operator()(const vector<string>& a, const vector<string>& b) const {
            if (stod(a[6]) != stod(b[6]) && a[3] == "2") { //sell order
                return stod(a[6]) < stod(b[6]); // Lower price comes first
            }
            else if (stod(a[6]) != stod(b[6]) && a[3] == "1") { //buy order
                return stod(a[6]) > stod(b[6]); // Higher price comes first
            }
            return a[0] < b[0]; // Lower order ID comes first
        }
    };

class SellOrderBook {
private:
    priority_queue<vector<string>, vector<vector<string>>, Comparator> minHeap;
public:
    bool isEmpty() {
        return minHeap.empty();
    }
    vector<string> getMinPriceOrder() {
            return minHeap.top();

    }
    void addTo(const vector<string>& order) {
        minHeap.push(order);
    }
    void popMinPriceOrder() {
        if (!minHeap.empty()) {
            minHeap.pop();
        }
    }
    void updateMinPriceOrderQuantity(int newQuantity) {
        if (!minHeap.empty()) {
            vector<string> topOrder = minHeap.top();
            topOrder[5]= to_string(newQuantity);
            minHeap.pop(); // Remove the top order with the old quantity
            minHeap.push(topOrder); // Push the updated order back into the min heap
        }
    }
};

class BuyOrderBook {
private:
    priority_queue<vector<string>, vector<vector<string>>, Comparator> maxHeap;
public:
    bool isEmpty() {
        return maxHeap.empty();
    }
    vector<string> getMaxPriceOrder() {
            return maxHeap.top();

    }
    void addTo(const vector<string>& order) {
        maxHeap.push(order);
    }
    void popMaxPriceOrder() {
        if (!maxHeap.empty()) {
            maxHeap.pop();
        }
    }
    void updateMaxPriceOrderQuantity(int newQuantity) {
        if (!maxHeap.empty()) {
            vector<string> topOrder = maxHeap.top();
            topOrder[5] = newQuantity;
            maxHeap.pop(); // Remove the top order with the old quantity
            maxHeap.push(topOrder); // Push the updated order back into the max heap
        }
    }
};