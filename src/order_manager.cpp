//
// Created by JIANG on 19/11/24.
//


#include "./../include/order_manager.h"
#include <fstream>

void OrderManager::readFromInputFile (const std::string& filePath) {
    std::ifstream inputFile(filePath);
    if (!inputFile) {
        std::cerr << "Error: cannot open the file: " << filePath << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        // init order from line
        Order order(line);
        // check if order book has been created for this symbol
        if (_orderBooks.find(order.instrument) == _orderBooks.end()) {
            // create new order book with that symbol
            _orderBooks.insert(std::make_pair(order.instrument, OrderBook(order.instrument)));
        }
        // insert order to the order book
        _orderBooks.at(order.instrument).addOrder(order);
        // do matching
        _orderBooks.at(order.instrument).doMatching();
    }
    // close file
    inputFile.close();

    // print trades
    for (const auto& orderBook : _orderBooks) {
        orderBook.second.printTrades();
    }

    // print new line as required
    std::cout << std::endl;

    // print order book
    for (const auto& orderBook : _orderBooks) {
        orderBook.second.printOrderBook();
    }

    // optional print all orders with status

    /*
    for (const auto& orderBook : _orderBooks) {
        orderBook.second.printAllOrders();
    }
     */

}

unsigned long OrderManager::getOrderSizeBySymbol(const std::string& symbol) const {
    if (_orderBooks.find(symbol) == _orderBooks.end()) {
        return 0;
    }
    return _orderBooks.at(symbol).getOrdersSize();
}

std::vector<std::string> OrderManager::getSymbols() const {
    std::vector<std::string> symbols;
    for (const auto& orderBook : _orderBooks) {
        symbols.push_back(orderBook.first);
    }
    return symbols;
}

std::optional<OrderBook> OrderManager::OrderManager::getOrderBookBySymbol(const std::string& symbol) const {
    if (_orderBooks.find(symbol) == _orderBooks.end()) {
        return std::nullopt;
    }
    return _orderBooks.at(symbol);
}