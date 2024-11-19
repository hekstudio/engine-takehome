//
// Created by JIANG on 18/11/24.
//

#ifndef ENGINE_TAKEHOME_TRADE_H
#define ENGINE_TAKEHOME_TRADE_H

#include <iostream>

/*
 * Trade format
 *
 * <prefix> | <instrument> | <sell_orderId> | <buy_orderId> | <quantity> | <price>
 * TRADE    | BTCUSD       | abe14          | 12345         | 5          | 10000
 * TRADE    | BTCUSD       | plu401         | 13471         | 5          | 9971
 * TRADE    | ETHUSD       | 45691          | 11431         | 3          | 180
 *
 */

namespace TradeUtils {
    constexpr const char* PREFIX = "TRADE";
}

class Trade {
public:
    // constructor using parameters
    Trade(const std::string &instrument,
          const std::string &sellOrderID,
          const std::string &buyOrderID,
          double quantity,
          double price) :
            instrument(instrument),
            sellOrderID(sellOrderID),
            buyOrderID(buyOrderID),
            quantity(quantity),
            price(price) {}
    ~Trade() {}

    std::string instrument;   // instrument, e.g. BTCUSD
    std::string sellOrderID;  // sell order ID
    std::string buyOrderID;   // buy order ID
    double quantity;          // quantity
    double price;             // price

    void printTrade() const;

};
#endif //ENGINE_TAKEHOME_TRADE_H
