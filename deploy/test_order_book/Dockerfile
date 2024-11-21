# Stage 1: Build Stage
# NOTE: currently bazel image does not support darwin/arm64
FROM --platform=$BUILDPLATFORM l.gcr.io/google/bazel:latest AS build-stage

# Set the working directory
WORKDIR /app

# Print build information
# Print the Bazel version
RUN bazel version

# Copy project files
COPY .. .

# Build the executable using Bazel
RUN bazel build \
    --verbose_failures \
    --sandbox_debug \
    --cxxopt='-std=c++17' \
    --host_cxxopt='-std=c++17' \
    --cxxopt='-stdlib=libc++' \
    --linkopt='-stdlib=libc++' \
    --cxxopt='-I/usr/include/c++/11' \
    --cxxopt='-I/usr/include' \
    //:test_order_book

# Stage 2: Runtime Stage
FROM --platform=$BUILDPLATFORM debian:bullseye AS runtime-stage

# Copy the executables from the build stage
COPY --from=build-stage /app/bazel-bin/main /usr/local/bin/main

# Set the entrypoint to the executable
ENTRYPOINT ["/usr/local/bin/main"]

# Set flags