//
// Created by JIANG on 20/11/24.
//


#include <gtest/gtest.h>
#include <optional>
#include "./../include/order_manager.h"
#include "./../include/order_book.h"


TEST(OrderBookTest, readFile) {
    OrderManager orderManager;
    orderManager.readFromInputFile("./tests/test_input_01.txt");

    // check for nullopt if symbol is not found
    std::optional<OrderBook> orderBook = orderManager.getOrderBookBySymbol("");
    EXPECT_EQ(orderBook, std::nullopt);

    // print trades
    orderBook = orderManager.getOrderBookBySymbol("BTCUSD");
    if (orderBook.has_value()) {
        orderBook->printTrades();
    } else {
        FAIL() << "OrderBook not found";
    }

    // check order size
    EXPECT_EQ(orderManager.getOrderBooksSize(), 2);
    // check symbols
    EXPECT_EQ(orderManager.getSymbols().size(), 2);
    EXPECT_EQ(orderManager.getSymbols()[0], "BTCUSD");
    EXPECT_EQ(orderManager.getSymbols()[1], "ETHUSD");

    // check no. of orders for BTCUSD
    EXPECT_EQ(orderManager.getOrderSizeBySymbol("BTCUSD"), 44);
    // check no. of orders for ETHUSD
    EXPECT_EQ(orderManager.getOrderSizeBySymbol("ETHUSD"), 40);
}

TEST(OrderBookTest, withNoTrades) {
    // test with no trades executed (bid price < ask price)
    OrderManager orderManager;
    orderManager.readFromInputFile("./tests/test_input_02.txt");

    // check for nullopt if symbol is not found
    std::optional<OrderBook> orderBook = orderManager.getOrderBookBySymbol("");
    EXPECT_EQ(orderBook, std::nullopt);

    // check trade size for BTCUSD
    orderBook = orderManager.getOrderBookBySymbol("BTCUSD");
    if (orderBook.has_value()) {
        EXPECT_EQ(orderBook->getTradesSize(), 0);
    } else {
        FAIL() << "OrderBook not found";
    }

    // check trade size for ETHUSD
    orderBook = orderManager.getOrderBookBySymbol("ETHUSD");
    if (orderBook.has_value()) {
        EXPECT_EQ(orderBook->getTradesSize(), 0);
    } else {
        FAIL() << "OrderBook not found";
    }
}

TEST(OrderBookTest, allTraded) {
    // test with no trades executed (bid price < ask price)
    OrderManager orderManager;
    orderManager.readFromInputFile("./tests/test_input_03.txt");

    // check for nullopt if symbol is not found
    std::optional<OrderBook> orderBook = orderManager.getOrderBookBySymbol("");
    EXPECT_EQ(orderBook, std::nullopt);

    // check order size for BTCUSD
    orderBook = orderManager.getOrderBookBySymbol("BTCUSD");
    if (orderBook.has_value()) {
        EXPECT_EQ(orderBook->getOrdersSize(), 10);
    } else {
        FAIL() << "OrderBook not found";
    }

    // check order size for ETHUSD
    orderBook = orderManager.getOrderBookBySymbol("ETHUSD");
    if (orderBook.has_value()) {
        EXPECT_EQ(orderBook->getOrdersSize(), 10);
    } else {
        FAIL() << "OrderBook not found";
    }

    // check trade size for BTCUSD
    orderBook = orderManager.getOrderBookBySymbol("BTCUSD");
    if (orderBook.has_value()) {
        EXPECT_EQ(orderBook->getTradesSize(), 5);
    } else {
        FAIL() << "OrderBook not found";
    }

    // check trade size for ETHUSD
    orderBook = orderManager.getOrderBookBySymbol("ETHUSD");
    if (orderBook.has_value()) {
    EXPECT_EQ(orderBook->getTradesSize(), 5);
    } else {
    FAIL() << "OrderBook not found";
    }
}

