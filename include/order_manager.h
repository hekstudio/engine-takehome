//
// Created by JIANG on 19/11/24.
//

#ifndef ENGINE_TAKEHOME_ORDER_MANAGER_H
#define ENGINE_TAKEHOME_ORDER_MANAGER_H

#include <map>
#include <vector>
#include <optional>
#include "order_book.h"

class OrderManager {
public:
    OrderManager() {}

    void readFromInputFile (const std::string& filePath);

    unsigned long getOrderBooksSize() const { return _orderBooks.size(); } // no. of order books managed
    unsigned long getOrderSizeBySymbol(const std::string& symbol) const;
    std::vector<std::string> getSymbols() const;
    std::optional<OrderBook> getOrderBookBySymbol(const std::string& symbol) const; // check for nullopt required

private:
    std::map<std::string, OrderBook> _orderBooks;
};



#endif //ENGINE_TAKEHOME_ORDER_MANAGER_H
