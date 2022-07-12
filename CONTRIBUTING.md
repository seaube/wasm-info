# Contributing

All contributions are welcome!

## Setup Autocomplete

Download and install the recommended VSCode extensions. There should be a prompt for you to download them. If not, they are listed in `.vscode/extensions.json`.

```sh
# Generates compile_commands.json
bazel run @hedron_compile_commands//:refresh_all
# Makes sure the LLVM toolchain is available
bazel build @llvm_toolchain_llvm//...
```

In VSCode there may be some prompts asking if you want to use the paths specified by the `.vscode/settings.json`. Select **Yes** for those prompts.

If the clangd vscode extension is working you should see a `.cache` folder generated and your autocomplete should be working.
