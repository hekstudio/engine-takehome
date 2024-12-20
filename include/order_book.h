//
// Created by JIANG on 18/11/24.
//

#ifndef ENGINE_TAKEHOME_ORDER_BOOK_H
#define ENGINE_TAKEHOME_ORDER_BOOK_H

#include <string>
#include <vector>
#include <map>
#include "order.h"
#include "trade.h"

class OrderBook {
public:
    explicit OrderBook(const std::string& symbol); // OrderBook needs a symbol for constructor
    ~OrderBook();

    void addOrder(const Order& order);
    bool cancelOrder(const std::string& orderID);
    bool modifyOrder(const Order& order);
    void doMatching();
    std::string getSymbol() const { return _symbol; }
    void printTrades() const;

    void removeOrderByID(const std::string& orderID); // remove from buy orders or sell orders
    Order& getOrderByID(const std::string& orderID);  // caller should check if the order exists

    void printBuyOrders() const;
    void printSellOrders() const;
    void printOrderBook() const;
    void printAllOrders() const;

    int getBuyOrdersSize() const { return _buyOrders.size(); }
    int getSellOrdersSize() const { return _sellOrders.size(); }
    int getOrdersSize() const { return _orders.size(); }
    int getTradesSize() const { return _trades.size(); }
private:
    std::string _symbol;
    std::map<double, std::vector<std::string> >  _buyOrders;  // keep all buy orders (price, orderID[])
    std::map<double, std::vector<std::string> > _sellOrders;  // keep all sell orders (price, orderID[])
    std::map<std::string, Order> _orders;                     // keep all orders (orderID, Order)
    std::vector<Trade> _trades;                               // keep all trades (Trade)
};

#endif //ENGINE_TAKEHOME_ORDER_BOOK_H
