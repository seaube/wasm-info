workspace(name = "com_seaube_wasm_info")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_grail_bazel_toolchain",
    sha256 = "090fcd12d4a0d528a37be96f4ec554493e74d5dd0faa410bb09d0c1a6607a1a9",
    strip_prefix = "bazel-toolchain-2711d4189ff8c5670ecd1df46bbb1e758073fe78",
    url = "https://github.com/grailbio/bazel-toolchain/archive/2711d4189ff8c5670ecd1df46bbb1e758073fe78.zip",
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

load("//:wasmer.bzl", "wasmer_repo")

wasmer_repo(name = "wasmer")

_NLOHMANN_JSON_BUILD_FILE = """
load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "json",
    visibility = ["//visibility:public"],
    includes = ["include"],
    hdrs = glob(["include/**/*.hpp"]),
    strip_include_prefix = "include",
)
"""

http_archive(
    name = "nlohmann_json",
    build_file_content = _NLOHMANN_JSON_BUILD_FILE,
    sha256 = "b94997df68856753b72f0d7a3703b7d484d4745c567f3584ef97c96c25a5798e",
    url = "https://github.com/nlohmann/json/releases/download/v3.10.5/include.zip",
)

http_archive(
    name = "magic_enum",
    sha256 = "5e7680e877dd4cf68d9d0c0e3c2a683b432a9ba84fc1993c4da3de70db894c3c",
    strip_prefix = "magic_enum-0.8.0",
    urls = ["https://github.com/Neargye/magic_enum/archive/refs/tags/v0.8.0.tar.gz"],
)

http_archive(
    name = "hedron_compile_commands",
    sha256 = "cb29ade67efd170c98b86fe75524fc053c01dcbe1f6211d00ce658e57441ed42",
    strip_prefix = "bazel-compile-commands-extractor-670e86177b6b5c001b03f4efdfba0f8019ff523f",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/670e86177b6b5c001b03f4efdfba0f8019ff523f.tar.gz",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()
