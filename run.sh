#!/bin/bash

# Build the Docker image
docker build -t engine-takehome:latest -f ./deploy/Dockerfile . --progress=plain

# Run the Docker container
docker run -i engine-takehome:latest