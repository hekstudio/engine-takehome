#!/bin/bash

# Build the Docker image (tests)
docker build -t test-order:latest -f ./deploy/test_order/Dockerfile . --progress=plain
docker build -t test-order-book:latest -f ./deploy/test_order_book/Dockerfile . --progress=plain


# Run the Docker container
docker run -i test-order:latest
docker run -i test-order-book:latest