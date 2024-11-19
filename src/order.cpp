//
// Created by JIANG on 16/11/24.
//

#include <string>
#include <sstream>
#include <iostream>
#include "./../include/order.h"

/*
 *
 * sample input line:
 *
 *
 *
 * limit order example input:
    12345 BUY BTCUSD 5 10000
    zod42 SELL BTCUSD 2 10001
    13471 BUY BTCUSD 6 9971
    11431 BUY ETHUSD 9 175
    abe14 SELL BTCUSD 7 9800
    plu401 SELL ETHUSD 5 170
    45691 BUY ETHUSD 3 180


   market order example input:

    12345 BUY BTCUSD 5
    zod42 SELL BTCUSD 2
    13471 BUY BTCUSD 6
    11431 BUY ETHUSD 9
    abe14 SELL BTCUSD 7
    plu401 SELL ETHUSD 5
    45691 BUY ETHUSD 3


    limit order types:

    Here are some common Time in Force (TIF) options for limit orders:
    GTC (Good 'Til Canceled): The order remains active until it is either executed or explicitly canceled by the trader.
    IOC (Immediate or Cancel): The order must be executed immediately, and any portion of the order that cannot be filled immediately is canceled.
    FOK (Fill or Kill): The order must be executed immediately in its entirety, or it is canceled.
    DAY: The order is valid only for the trading day on which it is placed. If it is not executed by the end of the trading day, it is canceled.
    GTD (Good 'Til Date): The order remains active until a specified date, unless it is executed or canceled before that date.
    AON (All or None): The order must be executed in its entirety or not at all. Partial fills are not allowed.
    OPG (At the Opening): The order is executed at the market open. If it cannot be executed at the open, it is canceled.
    CLS (At the Close): The order is executed at the market close. If it cannot be executed at the close, it is canceled.
 */

// constructor using parameters
Order::Order(std::string orderID, std::string side, std::string instrument, double quantity, double price) :
        orderID(orderID), side(side), instrument(instrument), quantity(quantity), price(price) {
    // NOTE:
    // price == 0 indicates a market order
    if (orderID.empty() || side.empty() || instrument.empty() || quantity <= 0 || price < 0
    || (side != OrderUtils::BUY && side != OrderUtils::SELL)
    ) {
        _isValid = false;
    } else {
        _isValid = true;
    }
}

// constructor using string line
Order::Order(std::string& lineString, const bool& printOrder) {
    std::istringstream iss(lineString);
    // try to parse LIMIT order
    if (iss >> orderID >> side >> instrument >> quantity >> price) {
        // check if parameters are valid
        _isValid = isParametersValid();
        // print out the order
        if (printOrder) {
            std::cout << "LIMIT Order: "
                      << orderID << " "
                      << side << " "
                      << instrument << " "
                      << quantity << " "
                      << price << std::endl;
        }
        return;
    }
    // reset the stream
    iss.clear();
    // re-initialize the stream
    iss.str(lineString);
    // try to parse MARKET order
    if (iss >> orderID >> side >> instrument >> quantity) {
        // set default price for market order
        price = 0.0;
        // check if parameters are valid
        _isValid = isParametersValid();
        // print out the order
        if (printOrder) {
            std::cout << "MARKET Order: "
                      << orderID << " "
                      << side << " "
                      << instrument << " "
                      << quantity << " "
                      << price << std::endl;
        }
        return;
    }

    // set default values
    orderID = "";
    side = "";
    instrument = "";
    quantity = 0.0;
    price = 0.0;
    _isValid = false;
}

void Order::printOrder() const {
    std::cout << orderID << " "
              << side << " "
              << instrument << " "
              << quantity << " "
              << price << std::endl;
}