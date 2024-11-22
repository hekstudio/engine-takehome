# engine-takehome-interview

## Prompt

Your application is a matching engine that receives orders and continuously matches them to see if they can trade. Your application must be implemented in C++ and you should use a modern revision of the C++ standard (e.g., C++17).

The orders that your matching engine shall receive are timestamped upon arrival. Orders are first ranked according to their price; orders of the same price are then ranked depending on the timestamp at entry.

Your application must read orders from stdin in the format described below. As your program reads the orders, it must emit any trades that result from the placement of an order. These trades shall be printed to stdout.

Once the input stream is fully consumed, your application must print all remaining orders that did not fully trade. These orders must also be printed to stdout.

Please note the streaming nature of this input and structure your program accordingly.

## Input Format

Each order shall be delimitted by a new line. Each line consists of an order's `OrderID`, `Side`, `Instrument`, `Quantity` and `Price`, delimitted by a varying quantity of white space. The stream of orders are sequenced chronologically.

### Sample Input

```
12345 BUY BTCUSD 5 10000
zod42 SELL BTCUSD 2 10001
13471 BUY BTCUSD 6 9971
11431 BUY ETHUSD 9 175
abe14 SELL BTCUSD 7 9800
plu401 SELL ETHUSD 5 170
45691 BUY ETHUSD 3 180
```

## Output Format

For each trade produced by your application, your application must print a string followed by a newline. This string must being with the word `TRADE` and be followed by the `Instrument`, `OrderID`, `ContraOrderID`, `Quantity`, and `Price` of the trade.

Once the input stream is fully consumed, your application shall print all orders that remain on each side of every order book. The `SELL` side of each order book shall be printed first; the `BUY` side of each order book shall be printed last. For each side of every order book, orders shall be printed in the order in which they arrived. Note that arrival order is different from each order's price/time priority.

Please ensure that you leave exactly one line of whitespace between each portion of the requested output.

### Sample Output

```
TRADE BTCUSD abe14 12345 5 10000
TRADE BTCUSD abe14 13471 2 9971
TRADE ETHUSD plu401 11431 5 175

zod42 SELL BTCUSD 2 10001
13471 BUY BTCUSD 4 9971
11431 BUY ETHUSD 4 175
45691 BUY ETHUSD 3 180
```

## Submission Requirements

Please submit an archived directory containing the following:
1. All source code and any additional tooling required to build, compile, and test your submission
2. A `README.md` containing the following:
    - your name
    - instructions on how to build and run your application
    - a description of how you approached the problem
    - how long much time you spent on this project
3. A `run.sh` that builds a Docker image and runs your application 
    - Please do not submit precompiled artifacts; your `Dockerfile` must compile your source code when building the container image
4. A `test.sh` that builds a Docker image and runs your tests 
    - Similarly, please do not submit precompiled artifacts

It is of utmost importance that your submission is complete. All submissions lacking any of the above requirements will be rejected on the basis of being incomplete.

You should also showcase your knowledge of modern best practices in application development. Some relevant areas include developing with testings frameworks (like `googletest` or `catch2`), using automatic code formatters (like `clang-format`), and integrating static code analysis tooling (like `clang-tidy`).

## Runtime Requirements

Gemini's Engine Team has provided a barebones project that includes `./run.sh`, a `Dockerfile`, a `Makefile`, and a `main.cpp` which simply echos input. Executing `./run.sh` locally must build and launch a Docker image that defaults to running your application. The `./run.sh` file must accept piped input.

You are free to modify any of this project as you see fit. However, you must provide a `./run.sh` that builds and runs your application in a Docker container. You are not bound to use `FROM debian:10`, however you must use a base image that is available in [Docker Hub](https://hub.docker.com/).

If you would like to add logging to your application please use stderr so that we can discern your log statements from the expected application output.

### Runtime Example

```
$ cat sample_input.txt | ./run.sh
Sending build context to Docker daemon  197.1kB
Step 1/4 : FROM debian:10
 ---> 1b686a95ddbf
Step 2/4 : RUN apt-get -y update   && apt-get -y install build-essential   && apt-get clean
 ---> Using cache
 ---> 165e5b61f3e9
Step 3/4 : COPY src/ /app
 ---> 1e03b684802c
Step 4/4 : RUN cd /app && make build
 ---> Running in c930e5aaa0e9
mkdir -p build
g++ -o build/match_engine main.cpp
Removing intermediate container c930e5aaa0e9
 ---> 40ca2815137b
Successfully built 40ca2815137b
Successfully tagged gemini_interview:latest

====== Match Engine =====

TRADE BTCUSD abe14 12345 5 10000
TRADE BTCUSD abe14 13471 2 9971
TRADE ETHUSD plu401 11431 5 175

zod42 SELL BTCUSD 2 10001
13471 BUY BTCUSD 4 9971
11431 BUY ETHUSD 4 175
45691 BUY ETHUSD 3 180
```



---


## Pre-requisites

### Development machine

- Macbook (apple silicon)

### Bazel

Bazel is used to build and run the application. Install bazel using brew

```bash
brew install bazel
```

### Docker

Docker is used to build and run the application.

## Build the application

run the following command to build the application.

```bash
bazel build main
```

## Run the application

run the following command to start the application.

```bash
bazel run main -- --start
```

run the following command to start the module test.

```bash
bazel test test_order --test_output=all
bazel test test_order_book --test_output=all
```

## Docker build

run the `run.sh` script to build the docker image and run the application.

```bash
bash ./run.sh
```

run the `test.sh` script to build the docker image and run the tests. (tested on Linux)

```bash
bash ./test.sh
```

### build log example

```commandline
#0 building with "default" instance using docker driver

#1 [internal] load build definition from Dockerfile
#1 transferring dockerfile: 986B done
#1 DONE 0.0s

#2 [internal] load metadata for docker.io/library/debian:bullseye
#2 DONE 2.7s

#3 [internal] load .dockerignore
#3 transferring context: 2B done
#3 DONE 0.0s

#4 [1/6] FROM docker.io/library/debian:bullseye@sha256:01559430c84e6bc864bed554345d1bfbfa94ac108ab68f39915cae34604b15c3
#4 DONE 0.0s

#5 [internal] load build context
#5 transferring context: 16.35kB 0.0s done
#5 DONE 0.0s

#6 [2/6] RUN apt-get update && apt-get install -y     curl     gnupg     openjdk-11-jdk     git     build-essential     unzip     && rm -rf /var/lib/apt/lists/*
#6 CACHED

#7 [3/6] RUN curl -fsSL https://github.com/bazelbuild/bazel/releases/download/5.4.0/bazel-5.4.0-installer-linux-x86_64.sh     -o /tmp/bazel-installer.sh &&     chmod +x /tmp/bazel-installer.sh &&     /tmp/bazel-installer.sh &&     rm /tmp/bazel-installer.sh
#7 CACHED

#8 [4/6] WORKDIR /app
#8 CACHED

#9 [5/6] COPY . .
#9 DONE 0.1s

#10 [6/6] RUN bazel clean --expunge
#10 0.387 Extracting Bazel installation...
#10 2.403 Starting local Bazel server and connecting to it...
#10 4.251 INFO: Starting clean (this may take a while). Consider using --async if the clean takes more than several minutes.
#10 DONE 4.7s

#11 exporting to image
#11 exporting layers
#11 exporting layers 0.4s done
#11 writing image sha256:54e4163155ece63687ae3cc691680e4ca3dd7c1072809cf01e6ed0cb1465a583 done
#11 naming to docker.io/library/test-order:latest done
#11 DONE 0.4s
```

### test output example (test_order)

```commandline
Starting local Bazel server and connecting to it...
Loading: 
Loading: 0 packages loaded
Loading: 0 packages loaded
    currently loading: 
Analyzing: target //:test_order (1 packages loaded, 0 targets configured)
Analyzing: target //:test_order (33 packages loaded, 130 targets configured)
Analyzing: target //:test_order (35 packages loaded, 130 targets configured)
DEBUG: Rule 'com_google_googletest' indicated that a canonical reproducible form can be obtained by modifying arguments sha256 = "7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926"
DEBUG: Repository com_google_googletest instantiated at:
  /app/WORKSPACE:12:13: in <toplevel>
Repository rule http_archive defined at:
  /root/.cache/bazel/_bazel_root/8c069df52082beee3c95ca17836fb8e2/external/bazel_tools/tools/build_defs/repo/http.bzl:355:31: in <toplevel>
Analyzing: target //:test_order (39 packages loaded, 333 targets configured)
Analyzing: target //:test_order (42 packages loaded, 467 targets configured)
Analyzing: target //:test_order (42 packages loaded, 467 targets configured)
Analyzing: target //:test_order (42 packages loaded, 467 targets configured)
Analyzing: target //:test_order (48 packages loaded, 533 targets configured)
Analyzing: target //:test_order (48 packages loaded, 533 targets configured)
Analyzing: target //:test_order (48 packages loaded, 533 targets configured)
Analyzing: target //:test_order (48 packages loaded, 533 targets configured)
Analyzing: target //:test_order (48 packages loaded, 533 targets configured)
Analyzing: target //:test_order (48 packages loaded, 533 targets configured)
Analyzing: target //:test_order (48 packages loaded, 533 targets configured)
INFO: Analyzed target //:test_order (49 packages loaded, 667 targets configured).
INFO: Found 1 test target...
[0 / 4] [Prepa] Creating source manifest for //:test_order
[14 / 29] Compiling googlemock/src/gmock-spec-builders.cc; 1s processwrapper-sandbox ... (2 actions running)
[19 / 29] Compiling googletest/src/gtest.cc; 2s processwrapper-sandbox ... (2 actions running)
INFO: From Testing //:test_order:
==================== Test output for //:test_order:
Running main() from gmock_main.cc
[==========] Running 8 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 8 tests from OrderTest
[ RUN      ] OrderTest.ParseOrder
[       OK ] OrderTest.ParseOrder (0 ms)
[ RUN      ] OrderTest.ParseOrderWithDecimalQuantity
[       OK ] OrderTest.ParseOrderWithDecimalQuantity (0 ms)
[ RUN      ] OrderTest.ParseOrderWithDecimalPrice
[       OK ] OrderTest.ParseOrderWithDecimalPrice (0 ms)
[ RUN      ] OrderTest.ParseOrderWithDifferentValues
[       OK ] OrderTest.ParseOrderWithDifferentValues (0 ms)
[ RUN      ] OrderTest.ParseOrderWithInvalidDirection1
[       OK ] OrderTest.ParseOrderWithInvalidDirection1 (0 ms)
[ RUN      ] OrderTest.ParseOrderWithInvalidDirection2
[       OK ] OrderTest.ParseOrderWithInvalidDirection2 (0 ms)
[ RUN      ] OrderTest.ParseMarketOrder
[       OK ] OrderTest.ParseMarketOrder (0 ms)
[ RUN      ] OrderTest.ParseInvalidOrder
[       OK ] OrderTest.ParseInvalidOrder (0 ms)
[----------] 8 tests from OrderTest (0 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 8 tests.
================================================================================
[32 / 32] 1 / 1 tests; checking cached actions
Target //:test_order up-to-date:
  bazel-bin/test_order
INFO: Elapsed time: 43.087s, Critical Path: 4.89s
INFO: 32 processes: 10 internal, 22 processwrapper-sandbox.
INFO: Build completed successfully, 32 total actions
//:test_order                                                            PASSED in 0.0s

Executed 1 out of 1 test: 1 test passes.
There were tests whose specified size is too big. Use the --test_verbose_timeout_warnings command line option to see which ones these are.
INFO: Build completed successfully, 32 total actions
```

### test output example (test_order_book)

```commandline
Starting local Bazel server and connecting to it...
Loading: 
Loading: 0 packages loaded
Loading: 0 packages loaded
    currently loading: 
Analyzing: target //:test_order_book (1 packages loaded, 0 targets configured)
Analyzing: target //:test_order_book (32 packages loaded, 130 targets configured)
Analyzing: target //:test_order_book (35 packages loaded, 130 targets configured)
DEBUG: Rule 'com_google_googletest' indicated that a canonical reproducible form can be obtained by modifying arguments sha256 = "7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926"
DEBUG: Repository com_google_googletest instantiated at:
  /app/WORKSPACE:12:13: in <toplevel>
Repository rule http_archive defined at:
  /root/.cache/bazel/_bazel_root/8c069df52082beee3c95ca17836fb8e2/external/bazel_tools/tools/build_defs/repo/http.bzl:355:31: in <toplevel>
Analyzing: target //:test_order_book (38 packages loaded, 223 targets configured)
Analyzing: target //:test_order_book (41 packages loaded, 479 targets configured)
Analyzing: target //:test_order_book (41 packages loaded, 479 targets configured)
Analyzing: target //:test_order_book (41 packages loaded, 479 targets configured)
Analyzing: target //:test_order_book (48 packages loaded, 545 targets configured)
Analyzing: target //:test_order_book (48 packages loaded, 545 targets configured)
Analyzing: target //:test_order_book (48 packages loaded, 545 targets configured)
Analyzing: target //:test_order_book (48 packages loaded, 545 targets configured)
Analyzing: target //:test_order_book (48 packages loaded, 545 targets configured)
Analyzing: target //:test_order_book (48 packages loaded, 545 targets configured)
Analyzing: target //:test_order_book (48 packages loaded, 545 targets configured)
Analyzing: target //:test_order_book (48 packages loaded, 545 targets configured)
INFO: Analyzed target //:test_order_book (49 packages loaded, 679 targets configured).
INFO: Found 1 test target...
[0 / 4] [Prepa] Creating source manifest for //:test_order_book
[11 / 25] Compiling googletest/src/gtest.cc; 3s processwrapper-sandbox ... (2 actions, 1 running)
[18 / 25] Compiling googlemock/src/gmock.cc; 1s processwrapper-sandbox ... (2 actions, 1 running)
INFO: From Testing //:test_order_book:
==================== Test output for //:test_order_book:
Running main() from gmock_main.cc
[==========] Running 3 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 3 tests from OrderBookTest
[ RUN      ] OrderBookTest.readFile
TRADE BTCUSD order005 order001 5 10000
TRADE BTCUSD order005 order003 2 9971
TRADE BTCUSD order002 order011 2 10020
TRADE BTCUSD order008 order011 4 10020
TRADE BTCUSD order012 order011 1 10020
TRADE BTCUSD order016 order011 3 10020
TRADE BTCUSD order020 order023 5 10035
TRADE BTCUSD order024 order027 3 10045
TRADE BTCUSD order024 order031 1 10055
TRADE BTCUSD order028 order031 3 10055
TRADE BTCUSD order028 order035 3 10065
TRADE BTCUSD order032 order035 2 10065
TRADE BTCUSD order032 order039 5 10075
TRADE BTCUSD order036 order039 1 10075
TRADE BTCUSD order036 order043 7 10085
TRADE BTCUSD order040 order043 1 10085
TRADE BTCUSD order040 order047 8 10095
TRADE BTCUSD order044 order047 1 10095
TRADE BTCUSD order044 order051 9 10105
TRADE BTCUSD order048 order051 1 10105
TRADE BTCUSD order048 order055 1 10115
TRADE BTCUSD order052 order059 2 10125
TRADE BTCUSD order052 order063 2 10135
TRADE BTCUSD order056 order063 1 10135
TRADE BTCUSD order056 order067 4 10145
TRADE BTCUSD order060 order071 5 10155
TRADE BTCUSD order060 order075 1 10165
TRADE BTCUSD order064 order075 5 10165
TRADE BTCUSD order064 order079 2 10175
TRADE BTCUSD order068 order079 5 10175
TRADE BTCUSD order068 order083 3 10185
TRADE BTCUSD order072 order083 5 10185
TRADE ETHUSD order006 order004 5 175
TRADE ETHUSD order010 order007 3 180
TRADE ETHUSD order010 order004 3 175
TRADE ETHUSD order014 order013 2 178
TRADE ETHUSD order018 order017 4 182
TRADE ETHUSD order018 order013 4 178
TRADE ETHUSD order022 order021 3 180
TRADE ETHUSD order026 order025 1 185
TRADE ETHUSD order030 order029 2 190
TRADE ETHUSD order034 order033 3 195
TRADE ETHUSD order038 order037 4 200
TRADE ETHUSD order042 order041 5 205
TRADE ETHUSD order046 order045 1 210
TRADE ETHUSD order050 order049 3 215
TRADE ETHUSD order054 order053 4 220
TRADE ETHUSD order054 order049 2 215
TRADE ETHUSD order058 order057 3 225
TRADE ETHUSD order058 order045 4 210
TRADE ETHUSD order062 order061 2 230
TRADE ETHUSD order062 order045 1 210
TRADE ETHUSD order062 order041 2 205
TRADE ETHUSD order062 order037 3 200
TRADE ETHUSD order066 order065 1 235
TRADE ETHUSD order066 order037 3 200
TRADE ETHUSD order066 order033 5 195
TRADE ETHUSD order070 order069 2 240
TRADE ETHUSD order074 order073 3 245
TRADE ETHUSD order078 order077 4 250
TRADE ETHUSD order082 order081 5 255

order072 SELL BTCUSD 4 10160
order076 SELL BTCUSD 10 10170
order080 SELL BTCUSD 1 10180
order084 SELL BTCUSD 2 10190
order009 BUY BTCUSD 8 9950
order003 BUY BTCUSD 4 9971
order015 BUY BTCUSD 9 9990
order019 BUY BTCUSD 2 10025
order023 BUY BTCUSD 2 10035
order004 BUY ETHUSD 1 175
order013 BUY ETHUSD 1 178
order021 BUY ETHUSD 3 180
order025 BUY ETHUSD 4 185
order029 BUY ETHUSD 6 190
order033 BUY ETHUSD 1 195
order069 BUY ETHUSD 8 240
order073 BUY ETHUSD 6 245
order077 BUY ETHUSD 4 250
order081 BUY ETHUSD 2 255
TRADE BTCUSD order005 order001 5 10000
TRADE BTCUSD order005 order003 2 9971
TRADE BTCUSD order002 order011 2 10020
TRADE BTCUSD order008 order011 4 10020
TRADE BTCUSD order012 order011 1 10020
TRADE BTCUSD order016 order011 3 10020
TRADE BTCUSD order020 order023 5 10035
TRADE BTCUSD order024 order027 3 10045
TRADE BTCUSD order024 order031 1 10055
TRADE BTCUSD order028 order031 3 10055
TRADE BTCUSD order028 order035 3 10065
TRADE BTCUSD order032 order035 2 10065
TRADE BTCUSD order032 order039 5 10075
TRADE BTCUSD order036 order039 1 10075
TRADE BTCUSD order036 order043 7 10085
TRADE BTCUSD order040 order043 1 10085
TRADE BTCUSD order040 order047 8 10095
TRADE BTCUSD order044 order047 1 10095
TRADE BTCUSD order044 order051 9 10105
TRADE BTCUSD order048 order051 1 10105
TRADE BTCUSD order048 order055 1 10115
TRADE BTCUSD order052 order059 2 10125
TRADE BTCUSD order052 order063 2 10135
TRADE BTCUSD order056 order063 1 10135
TRADE BTCUSD order056 order067 4 10145
TRADE BTCUSD order060 order071 5 10155
TRADE BTCUSD order060 order075 1 10165
TRADE BTCUSD order064 order075 5 10165
TRADE BTCUSD order064 order079 2 10175
TRADE BTCUSD order068 order079 5 10175
TRADE BTCUSD order068 order083 3 10185
TRADE BTCUSD order072 order083 5 10185
[       OK ] OrderBookTest.readFile (1 ms)
[ RUN      ] OrderBookTest.withNoTrades

order002 SELL BTCUSD 2 10000
order004 SELL BTCUSD 7 10100
order003 BUY BTCUSD 6 8900
order001 BUY BTCUSD 5 9000
order006 SELL ETHUSD 5 200
order008 SELL ETHUSD 4 210
order007 BUY ETHUSD 3 140
order005 BUY ETHUSD 9 150
[       OK ] OrderBookTest.withNoTrades (0 ms)
[ RUN      ] OrderBookTest.allTraded
TRADE BTCUSD order002 order001 5 10000
TRADE BTCUSD order004 order003 3 10100
TRADE BTCUSD order010 order009 6 10200
TRADE BTCUSD order012 order011 4 10300
TRADE BTCUSD order018 order017 7 10400
TRADE ETHUSD order006 order005 4 200
TRADE ETHUSD order008 order007 2 210
TRADE ETHUSD order014 order013 5 220
TRADE ETHUSD order016 order015 3 230
TRADE ETHUSD order020 order019 6 240

[       OK ] OrderBookTest.allTraded (0 ms)
[----------] 3 tests from OrderBookTest (1 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 3 tests.
================================================================================
Target //:test_order_book up-to-date:
  bazel-bin/test_order_book
INFO: Elapsed time: 45.763s, Critical Path: 4.61s
INFO: 44 processes: 16 internal, 28 processwrapper-sandbox.
INFO: Build completed successfully, 44 total actions
//:test_order_book                                                       PASSED in 0.0s

Executed 1 out of 1 test: 1 test passes.
There were tests whose specified size is too big. Use the --test_verbose_timeout_warnings command line option to see which ones these are.
INFO: Build completed successfully, 44 total actions
```

## Architecture

### Key Components

- Order
  - Represents an order with OrderID, Side, Instrument, Quantity and Price
  - Expandable to include more fields like order status, filled quantity, timestamp, time in force etc.

- OrderBook
  - Represents an order book with buy and sell orders for a particular instrument
  - Supported operations:
    - add new order to the OrderBook
    - cancel an order from the OrderBook
    - modify an order in the OrderBook (only pending/working orders can be modified)
    - matching orders in the OrderBook

- OrderBookManager
  - Represents an order book manager that orchestrates multiple order books
  - Supported operations:
    - Create new Orderbook: Create an order book for a particular instrument
    - Add Order: Add an order to the Orderbook