#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class FlowerOrderSeparator {
private:
    vector<vector<string>> roseOrders;
    vector<vector<string>> orchidOrders;
    vector<vector<string>> lavenderOrders;
    vector<vector<string>> lotusOrders;
    vector<vector<string>> tulipOrders;

public:
    FlowerOrderSeparator() {
        roseOrders.clear();
        orchidOrders.clear();
        lavenderOrders.clear();
        lotusOrders.clear();
        tulipOrders.clear();
    }

    void separateOrder(const vector<string>& order) {
        if (order[2] == "Rose") {
            roseOrders.push_back(order);
        } else if (order[2] == "Orchid") {
            orchidOrders.push_back(order);
        } else if (order[2] == "Lavender") {
            lavenderOrders.push_back(order);
        } else if (order[2] == "Lotus") {
            lotusOrders.push_back(order);
        } else if (order[2] == "Tulip") {
            tulipOrders.push_back(order);
        }
    }
    vector<vector<string>> getRoseOrders() const {
        return roseOrders;
    }
    vector<vector<string>> getOrchidOrders() const {
        return orchidOrders;
    }
    vector<vector<string>> getLavenderOrders() const {
        return lavenderOrders;
    }
    vector<vector<string>> getLotusOrders() const {
        return lotusOrders;
    }
    vector<vector<string>> getTulipOrders() const {
        return tulipOrders;
    }
};