# Use a Debian base image
FROM debian:bullseye

# Install Bazel dependencies
RUN apt-get update && apt-get install -y \
    curl \
    gnupg \
    openjdk-11-jdk \
    git \
    build-essential \
    unzip \
    && rm -rf /var/lib/apt/lists/*

# Install Bazel
RUN curl -fsSL https://github.com/bazelbuild/bazel/releases/download/5.4.0/bazel-5.4.0-installer-linux-x86_64.sh \
    -o /tmp/bazel-installer.sh && \
    chmod +x /tmp/bazel-installer.sh && \
    /tmp/bazel-installer.sh && \
    rm /tmp/bazel-installer.sh

# Set the working directory
WORKDIR /app

# Copy the entire project into the container
COPY . .

# Clean and run the Bazel test
RUN bazel clean --expunge
#RUN bazel test --cxxopt="-std=c++17" --copt="-std=c++17" //:test_order --test_outoput=all | tee bazel_test_output.log


# Set entry point to execute the Bazel test
ENTRYPOINT ["bazel", "test", "--cxxopt=-std=c++17", "--copt=-std=c++17", "//:test_order", "--test_output=all"]