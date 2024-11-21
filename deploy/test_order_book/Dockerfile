# Use a base image with Bazel installed
FROM l.gcr.io/google/bazel:latest

# Set the working directory
WORKDIR /app

# Copy the project files into the container
COPY . .

# Install any necessary dependencies (if required)
# RUN apt-get update && apt-get install -y <dependencies>

# Build the project and run the test
RUN bazel test //:test_order_book --test_output=all

# Set the entrypoint to run the test
ENTRYPOINT ["bazel", "test", "//:test-order", "--test_output=all"]