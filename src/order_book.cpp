//
// Created by JIANG on 18/11/24.
//

#include "./../include/order_book.h"
#include <iostream>
#include <fstream>
#include <algorithm>

OrderBook::OrderBook(const std::string& symbol) : _symbol(symbol) {}

OrderBook::~OrderBook() {}

void OrderBook::addOrder(const Order& order) {
    if (order.instrument != _symbol) {
        // ignore the order if the symbol does not match
        return;
    }
    // validity check
    if (!order.isValid()) {
        // ignore the order if it is not valid
        return;
    }
    // check if order already exists
    if (_orders.find(order.orderID) != _orders.end()) {
        // ignore the order if it already exists
        return;
    }
    // add order to internal orders map
    _orders.insert(std::make_pair(order.orderID, order));
    // add the order to the order book
    if (order.side == OrderUtils::BUY) {
        _buyOrders[order.price].push_back(order.orderID);
    } else if (order.side == OrderUtils::SELL) {
        _sellOrders[order.price].push_back(order.orderID);
    }
}

void OrderBook::doMatching() {
    // compare the best buy price with the best sell price
    // if the best buy price is higher than the best sell price, do matching
    // otherwise, do nothing

    // check if buy orders and sell orders are empty
    if (_buyOrders.empty() || _sellOrders.empty()) {
        return;
    }

    while (true) {
        // get the best buy price and the best sell price
        double bestBuyPrice = _buyOrders.rbegin()->first;  // highest bid price
        double bestSellPrice = _sellOrders.begin()->first; // lowest ask price

        if (bestBuyPrice >= bestSellPrice) {
            // find buy quantity
            double buyQty = getOrderByID(_buyOrders.rbegin()->second[0]).quantity;
            // find sell quantity
            double sellQty = getOrderByID(_sellOrders.begin()->second[0]).quantity;
            // create a trade and store it
            // traded qty is the minimum of buyQty and sellQty
            Trade trade(_symbol,
                        _sellOrders.begin()->second[0],
                        _buyOrders.rbegin()->second[0],
                        std::min(buyQty, sellQty), bestBuyPrice);
            // store the trade
            _trades.push_back(trade);

            if (buyQty == sellQty) {
                // set sell order to be FILLED
                getOrderByID(_sellOrders.begin()->second[0]).status.SetFilled();
                // set buy order to be FILLED
                getOrderByID(_buyOrders.rbegin()->second[0]).status.SetFilled();
                // remove both orders from order book
                removeOrderByID(_sellOrders.begin()->second[0]);
                removeOrderByID(_buyOrders.rbegin()->second[0]);
            }
            else if (buyQty > sellQty) {
                // set sell order to be FILLED
                getOrderByID(_sellOrders.begin()->second[0]).status.SetFilled();
                // set buy order to be PARTIAL
                getOrderByID(_buyOrders.rbegin()->second[0]).status.SetPartial();
                // remove sell order from the order book
                removeOrderByID(_sellOrders.begin()->second[0]);
                // update buy order quantity
                getOrderByID(_buyOrders.rbegin()->second[0]).quantity -= sellQty;
            } else {
                // buyQty < sellQty
                // set buy order to be FILLED
                getOrderByID(_buyOrders.rbegin()->second[0]).status.SetFilled();
                // set sell order to be PARTIAL
                getOrderByID(_sellOrders.begin()->second[0]).status.SetPartial();
                // remove buy order from the order book
                removeOrderByID(_buyOrders.rbegin()->second[0]);
                // update sell order quantity
                getOrderByID(_sellOrders.begin()->second[0]).quantity -= buyQty;
            }
            // check if buy orders and sell orders are empty
            if (_buyOrders.empty() || _sellOrders.empty()) {
                break;
            }
        } else {
            // break the loop if the best buy price is lower than the best sell price
            // otherwise, continue the loop
            break;
        }
    }
}

bool OrderBook::cancelOrder(const std::string& orderID) {
    // check if order exists
    if (_orders.find(orderID) == _orders.end()) {
        return false;
    }
    // order exists, find if it's in buy orders or sell orders
    auto target_order = _orders.at(orderID);
    if (target_order.isBuy()) {
        // buy order
        // use price to find the order
        _buyOrders[target_order.price].erase(
                std::remove(_buyOrders[target_order.price].begin(),
                _buyOrders[target_order.price].end(),
                orderID),
                 _buyOrders[target_order.price].end());
    } else {
        // sell order
        // use price to find the order
        _sellOrders[target_order.price].erase(
                std::remove(_sellOrders[target_order.price].begin(),
                _sellOrders[target_order.price].end(),
                orderID),
                 _sellOrders[target_order.price].end());
    }
    // last but if not least, remove the order from the orders map
    _orders.erase(orderID);
    return true;
}

void OrderBook::removeOrderByID(const std::string &orderID) {
    // check if order exists
    if (_orders.find(orderID) == _orders.end()) {
        return;
    }
    // check if it's in buy orders or sell orders
    if (getOrderByID(orderID).isBuy()) {
        // buy order
        // use price to find the order
        _buyOrders[getOrderByID(orderID).price].erase(
                std::remove(_buyOrders[getOrderByID(orderID).price].begin(),
                            _buyOrders[getOrderByID(orderID).price].end(),
                            orderID),
                _buyOrders[getOrderByID(orderID).price].end());
        // check if that order is empty for this price
        if (_buyOrders[getOrderByID(orderID).price].empty()) {
            // remove the price key if the order is empty
            _buyOrders.erase(getOrderByID(orderID).price);
        }
    } else {
        // sell order
        // use price to find the order
        _sellOrders[getOrderByID(orderID).price].erase(
                std::remove(_sellOrders[getOrderByID(orderID).price].begin(),
                            _sellOrders[getOrderByID(orderID).price].end(),
                            orderID),
                _sellOrders[getOrderByID(orderID).price].end());
        // check if that order is empty for this price
        if (_sellOrders[getOrderByID(orderID).price].empty()) {
            // remove the price key if the order is empty
            _sellOrders.erase(getOrderByID(orderID).price);
        }
    }
}

void OrderBook::printTrades() const {
    for (const auto& trade : _trades) {
        trade.printTrade();
    }
}

void OrderBook::printBuyOrders() const {
    for (const auto& buyOrder : _buyOrders) {
        // get the order associated with orderID
        for (const auto& orderID : buyOrder.second) {
            _orders.at(orderID).printOrder();
        }
    }
}

void OrderBook::printSellOrders() const {
    for (const auto& sellOrder : _sellOrders) {
        // get the order associated with orderID
        for (const auto& orderID : sellOrder.second) {
            _orders.at(orderID).printOrder();
        }
    }
}

void OrderBook::printOrderBook() const {
    printSellOrders();
    printBuyOrders();
}

