load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# boost library
http_archive(
    name = "boost",
    build_file = "//third_party/boost:BUILD.bazel",  # Point to your BUILD file
    strip_prefix = "boost_1_86_0",
    urls = ["https://archives.boost.io/release/1.86.0/source/boost_1_86_0.tar.gz"],
)

# googletest library
http_archive(
    name = "com_google_googletest",
    strip_prefix = "googletest-1.15.2",
    urls = ["https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz"],
)

# Add Bazel Skylib
http_archive(
    name = "bazel_skylib",
    sha256 = "66ffd9315665bfaafc96b52278f57c7e2dd09f5ede279ea6d39b2be471e7e3aa",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.4.2/bazel-skylib-1.4.2.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.4.2/bazel-skylib-1.4.2.tar.gz",
    ],
)
