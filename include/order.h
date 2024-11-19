//
// Created by JIANG on 16/11/24.
//

#ifndef ENGINE_TAKEHOME_ORDER_H
#define ENGINE_TAKEHOME_ORDER_H

#include <sstream>
#include "order_status.h"
namespace OrderUtils {
    constexpr const char* BUY = "BUY";
    constexpr const char* SELL = "SELL";
}

class Order {
public:
    // constructor using parameters
    Order(std::string orderID, std::string side, std::string instrument, double quantity, double price);
    // constructor using string line
    Order(std::string& lineString, const bool& printOrder = false);

    std::string orderID;              // order ID, alphanumeric
    std::string side;                 // BUY or SELL
    std::string instrument;           // instrument, e.g. BTCUSD
    std::string timeInForce;          // time in force
    double quantity;                  // quantity
    double price;                     // price
    OrderStatusManager status;               // order status (NEW, PARTIAL, FILLED, CANCELED, REJECTED)

    // check if the order is valid
    bool isValid() const { return _isValid; }
    // check if the order is a market order
    // NOTE: users are recommended to call isValid() before calling isMarketOrder()
    bool isMarketOrder() const { return price == 0.0; }
    // check if direction is valid
    bool isDirectionValid() const { return side == OrderUtils::BUY || side == OrderUtils::SELL; }
    // check if price is valid (0 is valid for market order)
    bool isPriceValid() const { return price >= 0.0; }
    // check if quantity is valid
    bool isQuantityValid() const { return quantity > 0; }
    // check if all parameters are valid
    bool isParametersValid() const { return isDirectionValid() && isPriceValid() && isQuantityValid(); }
    // check if order direction is BUY
    bool isBuy() const { return side == OrderUtils::BUY; }
    // check if order direction is SELL
    bool isSell() const { return side == OrderUtils::SELL; }
    // print orders
    void printOrder() const;

private:
    bool _isValid;
};

#endif //ENGINE_TAKEHOME_ORDER_H
