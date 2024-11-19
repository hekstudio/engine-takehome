//
// Created by JIANG on 18/11/24.
//

#include "./../include/trade.h"


// print trade in text
void Trade::printTrade() const {
    std::cout << TradeUtils::PREFIX << " "
    << instrument << " "
    << sellOrderID << " "
    << buyOrderID << " "
    << quantity << " "
    << price << std::endl;
}