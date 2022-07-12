load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_grail_bazel_toolchain",
    sha256 = "4f7782654b12e6b0231a98c98bae546d7c7c3156dde5792581dcf6e50e5cbca8",
    strip_prefix = "bazel-toolchain-f14a8a5de8f7e98a011a52163d4855572c07a1a3",
    url = "https://github.com/grailbio/bazel-toolchain/archive/f14a8a5de8f7e98a011a52163d4855572c07a1a3.zip",
)

load("@com_grail_bazel_toolchain//toolchain:deps.bzl", "bazel_toolchain_dependencies")

bazel_toolchain_dependencies()

load("@com_grail_bazel_toolchain//toolchain:rules.bzl", "llvm_toolchain")

llvm_toolchain(
    name = "llvm_toolchain",
    cxx_standard = {"linux": "c++20"},
    llvm_version = "14.0.0",
)

http_archive(
    name = "com_google_googletest",
    sha256 = "b4870bf121ff7795ba20d20bcdd8627b8e088f2d1dab299a031c1034eddc93d5",
    strip_prefix = "googletest-release-1.11.0",
    url = "https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz",
)

http_archive(
    name = "hedron_compile_commands",
    sha256 = "67c782434c52f38827ce0a317abc410d5ed2bf4829769e714d490c9adfbd4d46",
    strip_prefix = "bazel-compile-commands-extractor-c56fdb10fbfc60fe9d66aba040dab3f4bc1b88a4",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/c56fdb10fbfc60fe9d66aba040dab3f4bc1b88a4.tar.gz",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()
