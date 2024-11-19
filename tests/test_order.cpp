//
// Created by JIANG on 16/11/24.
//

// test_order.cpp
#include <gtest/gtest.h>
#include "./../include/order.h"

// Test case for Order parser
TEST(OrderTest, ParseOrder) {
    std::string line = "12345 BUY BTCUSD 5 10000";
    Order order(line);

    EXPECT_EQ(order.orderID, "12345");
    EXPECT_EQ(order.side, "BUY");
    EXPECT_EQ(order.instrument, "BTCUSD");
    EXPECT_EQ(order.quantity, 5);
    EXPECT_EQ(order.price, 10000);
    EXPECT_EQ(order.isDirectionValid(), true);
    EXPECT_EQ(order.isPriceValid(), true);
    EXPECT_EQ(order.isQuantityValid(), true);
    EXPECT_EQ(order.isValid(), true);
    EXPECT_EQ(order.isMarketOrder(), false);
}

// Test case for Order parser
TEST(OrderTest, ParseOrderWithDecimalQuantity) {
    std::string line = "12345 BUY BTCUSD 5.12345 10000";
    Order order(line);

    EXPECT_EQ(order.orderID, "12345");
    EXPECT_EQ(order.side, "BUY");
    EXPECT_EQ(order.instrument, "BTCUSD");
    EXPECT_EQ(order.quantity, 5.12345);
    EXPECT_EQ(order.price, 10000);
    EXPECT_EQ(order.isDirectionValid(), true);
    EXPECT_EQ(order.isPriceValid(), true);
    EXPECT_EQ(order.isQuantityValid(), true);
    EXPECT_EQ(order.isValid(), true);
    EXPECT_EQ(order.isMarketOrder(), false);
}

// Test case for Order parser
TEST(OrderTest, ParseOrderWithDecimalPrice) {
    std::string line = "12345 BUY BTCUSD 5.12345 10000.123";
    Order order(line);

    EXPECT_EQ(order.orderID, "12345");
    EXPECT_EQ(order.side, "BUY");
    EXPECT_EQ(order.instrument, "BTCUSD");
    EXPECT_EQ(order.quantity, 5.12345);
    EXPECT_EQ(order.price, 10000.123);
    EXPECT_EQ(order.isDirectionValid(), true);
    EXPECT_EQ(order.isPriceValid(), true);
    EXPECT_EQ(order.isQuantityValid(), true);
    EXPECT_EQ(order.isValid(), true);
    EXPECT_EQ(order.isMarketOrder(), false);
}

// Test case for Order parser with different values
TEST(OrderTest, ParseOrderWithDifferentValues) {
    std::string line = "zod42 SELL BTCUSD 2 10001";
    Order order(line);

    EXPECT_EQ(order.orderID, "zod42");
    EXPECT_EQ(order.side, "SELL");
    EXPECT_EQ(order.instrument, "BTCUSD");
    EXPECT_EQ(order.quantity, 2);
    EXPECT_EQ(order.price, 10001);
    EXPECT_EQ(order.isValid(), true);
    EXPECT_EQ(order.isMarketOrder(), false);
}

// Test case for Order parser with invalid direction
TEST(OrderTest, ParseOrderWithInvalidDirection1) {
    std::string line = "zod42 BUYBUY BTCUSD 2 10001";
    Order order(line);

    EXPECT_EQ(order.isValid(), false);
}

// Test case for Order parser with invalid direction
TEST(OrderTest, ParseOrderWithInvalidDirection2) {
    std::string line = "zod42 SELLSELL BTCUSD 2 10001";
    Order order(line);

    EXPECT_EQ(order.isValid(), false);
}

// test for market order
TEST(OrderTest, ParseMarketOrder) {
    std::string line = "12345 BUY BTCUSD 5";
    Order order(line);

    EXPECT_EQ(order.orderID, "12345");
    EXPECT_EQ(order.side, "BUY");
    EXPECT_EQ(order.instrument, "BTCUSD");
    EXPECT_EQ(order.quantity, 5);
    EXPECT_EQ(order.price, 0.0);
    EXPECT_EQ(order.isValid(), true);
    EXPECT_EQ(order.isMarketOrder(), true);
}

// test for invalid order
TEST(OrderTest, ParseInvalidOrder) {
    std::string line = "INVALID LINE";
    Order order(line);

    EXPECT_EQ(order.isValid(), false);
}