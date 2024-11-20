//
// Created by JIANG on 19/11/24.
//

#ifndef ENGINE_TAKEHOME_ORDER_MANAGER_H
#define ENGINE_TAKEHOME_ORDER_MANAGER_H

#include <map>
#include "order_book.h"

class OrderManager {
public:
    OrderManager() {}

    void readFromInputFile (const std::string& filePath);

private:
    std::map<std::string, OrderBook> _orderBooks;
};



#endif //ENGINE_TAKEHOME_ORDER_MANAGER_H
