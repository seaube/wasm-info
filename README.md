# wasm-info

Command line tool to extract information about your `.wasm` files.

## Usage

Running wasm-info with [a sample wasm file](https://github.com/WebAssembly/wasm-c-api/blob/master/example/hello.wasm) should look like this.

```bash
wasm-info hello.wasm
```

```json
{"exports":[{"name":"run","params":[],"results":[],"type":"WASM_EXTERN_FUNC"}],"imports":[{"name":"hello","params":[],"results":[],"type":"WASM_EXTERN_FUNC"}]}
```

If you want the json output to be pretty consider using a tool such as [`jq`](https://stedolan.github.io/jq/).

```bash
wasm-info hello.wasm | jq
```

```json
{
  "exports": [
    {
      "name": "run",
      "params": [],
      "results": [],
      "type": "WASM_EXTERN_FUNC"
    }
  ],
  "imports": [
    {
      "name": "hello",
      "params": [],
      "results": [],
      "type": "WASM_EXTERN_FUNC"
    }
  ]
}
```

## Install

`wasm-info` was intended to be integrated into the tools that need it, but you might find it useful in your `PATH`. Executables available on the [releases](https://github.com/seaube/wasm-info/releases) page. If you want to get started quickly there are some install scripts available for your convenience.

### Install on Windows (powershell)

```pwsh
iwr https://raw.githubusercontent.com/seaube/wasm-info/main/install.ps1 -useb | iex
```
