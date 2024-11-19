//
// Created by Hongchuan JIANG on 18/11/24.
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
    OrderBook(const std::string& symbol);
    ~OrderBook();

    void addOrder(const Order& order);
    bool cancelOrder(const std::string& orderID);
    bool modifyOrder(const Order& order);
    void doMatching();
    std::string getSymbol() const { return _symbol; }
    void printTrades() const;

    void removeOrderByID(const std::string& orderID); // remove from buy orders or sell orders
    Order& getOrderByID(const std::string& orderID) { return _orders.at(orderID); }

    void printBuyOrders() const;
    void printSellOrders() const;
    void printOrderBook() const;
private:
    std::string _symbol;
    std::map<double, std::vector<std::string> >  _buyOrders;   // keep all buy orders (price, orderID[])
    std::map<double, std::vector<std::string> > _sellOrders;  // keep all sell orders (price, orderID[])
    std::map<std::string, Order> _orders;               // keep all orders
    std::vector<Trade> _trades;                         // keep all trades
};

#endif //ENGINE_TAKEHOME_ORDER_BOOK_H
