#include "OrderReader.h"
#include "Validator.h"
//#include "ExecutionReporter.h"
#include "OrderSeperator.h"
#include "OrderProcessor.h"
//#include "OrderBook.h"

using namespace std;

Validator validator;
ExecutionReporter RejectReport;
FlowerOrderSeparator seperator;
OrderProcessor processor;

int main()
{
    OrderReader orderReader("Flower.csv",0);
    vector<vector<string>> data = orderReader.read();
    //traverse in data and validate the orders
    for (int i = 0; i < data.size(); i++){
        string status = validator.isValidOrder(data[i]);
        if (status != "Valid") {
            RejectReport.Report(status, data[i]);
        }
        else{
            seperator.separateOrder(data[i]);
        }
    }

    vector<vector<string>> rose = seperator.getRoseOrders();
    vector<vector<string>> orchid = seperator.getOrchidOrders();
    vector<vector<string>> lavender = seperator.getLavenderOrders();
    vector<vector<string>> lotus = seperator.getLotusOrders();
    vector<vector<string>> tulip = seperator.getTulipOrders();

    //create order books for each flower
    BuyOrderBook roseBuy;
    SellOrderBook roseSell;
    BuyOrderBook orchidBuy;
    SellOrderBook orchidSell;
    BuyOrderBook lavenderBuy;
    SellOrderBook lavenderSell;
    BuyOrderBook lotusBuy;
    SellOrderBook lotusSell;
    BuyOrderBook tulipBuy;
    SellOrderBook tulipSell;
    
    for (int i = 0; i < rose.size(); i++){
        processor.Processor(rose[i], roseBuy, roseSell);
    }
    // for (int i = 0; i < orchid.size(); i++){
    //     processor.Processor(orchid[i], orchidBuy, orchidSell);
    // }
    // for (int i = 0; i < lavender.size(); i++){
    //     processor.Processor(lavender[i], lavenderBuy, lavenderSell);
    // }
    // for (int i = 0; i < lotus.size(); i++){
    //     processor.Processor(lotus[i], lotusBuy, lotusSell);
    // }
    // for (int i = 0; i < tulip.size(); i++){
    //     processor.Processor(tulip[i], tulipBuy, tulipSell);
    // }
    
    vector<string>Trades = processor.GetExecutionReport();
    vector<string> Execution = RejectReport.GetExecution();

    for (const std::string& Exchange : Trades) {
         std::cout << Exchange << std::endl;
     }

    return 0;
}



