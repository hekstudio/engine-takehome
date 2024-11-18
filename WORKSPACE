load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# boost library
http_archive(
    name = "boost",
    urls = ["https://archives.boost.io/release/1.86.0/source/boost_1_86_0.tar.gz"],
    strip_prefix = "boost_1_86_0",
    build_file = "//third_party/boost:BUILD.bazel",  # Point to your BUILD file
)

# googletest library
http_archive(
    name = "com_google_googletest",
    urls = ["https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz"],
    strip_prefix = "googletest-1.15.2",
    integrity = "sha256-e0K01u1IgQxTYsJloX+uvpDcI3PIheUhZDnTeSfwKSY=",  # Verify the integrity of the downloaded file
)