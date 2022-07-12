#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <filesystem>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <magic_enum.hpp>
#include <wasm.h>

namespace fs = std::filesystem;
using namespace std::string_literals;
using namespace std::string_view_literals;

enum class cli_exit_code : int {
	ok,
	invalid_arguments,
	invalid_file_extension,
	file_open_fail,
	file_read_fail,
	wasm_compile_fail,
};

constexpr auto USAGE = R"(WebAssembly Info.

Takes a .wasm <file> as input and outputs information in JSON format of the
imports and exports.

Usage:
	wasm-info <file>

)";

std::string error_prefix() {
	return "\033[31m[ERROR]\033[0m ";
}

cli_exit_code cli_entry(const std::vector<std::string_view>& args) {
	if(args.size() != 1) {
		return cli_exit_code::invalid_arguments;
	}

	if(args.at(0) == "--help"sv || args.at(0) == "-h"sv) {
		std::cerr << USAGE;
		return cli_exit_code::ok;
	}

	fs::path wasm_file_path{args.at(0)};

	if(wasm_file_path.extension() != ".wasm") {
		return cli_exit_code::invalid_file_extension;
	}

	auto engine = wasm_engine_new();

	FILE* file = std::fopen(wasm_file_path.string().c_str(), "rb");
	if(!file) {
		return cli_exit_code::file_open_fail;
	}

	std::fseek(file, 0L, SEEK_END);
	auto file_size = std::ftell(file);
	std::fseek(file, 0L, SEEK_SET);

	wasm_byte_vec_t binary;
	wasm_byte_vec_new_uninitialized(&binary, file_size);

	if(std::fread(binary.data, file_size, 1, file) != 1) {
		return cli_exit_code::file_read_fail;
	}

	auto store = wasm_store_new(engine);
	auto wasm_mod = wasm_module_new(store, &binary);

	if(!wasm_mod) {
		return cli_exit_code::wasm_compile_fail;
	}

	auto json = R"({"exports": [], "imports": []})"_json;

	auto& exports_json = json.at("exports");
	auto& imports_json = json.at("imports");

	wasm_exporttype_vec_t exports;
	wasm_module_exports(wasm_mod, &exports);

	for(size_t expi=0; exports.size > expi; ++expi) {
		auto export_json = "{}"_json;
		auto export_name = wasm_exporttype_name(exports.data[expi]);
		std::string_view export_name_str(export_name->data, export_name->size);
		auto export_type = wasm_exporttype_type(exports.data[expi]);
		auto export_type_kind = static_cast<wasm_externkind_enum>(
			wasm_externtype_kind(export_type)
		);

		export_json["name"] = export_name_str;
		export_json["type"] = magic_enum::enum_name(export_type_kind);

		exports_json.push_back(export_json);
	}

	wasm_importtype_vec_t imports;
	wasm_module_imports(wasm_mod, &imports);

	for(size_t impi=0; imports.size > impi; ++impi) {
		auto import_json = "{}"_json;
		auto import_name = wasm_importtype_name(imports.data[impi]);
		std::string import_name_str(import_name->data, import_name->size);
		auto import_type = wasm_importtype_type(imports.data[impi]);
		auto import_type_kind = static_cast<wasm_externkind_enum>(
			wasm_externtype_kind(import_type)
		);

		import_json["name"] = import_name_str;
		import_json["type"] = magic_enum::enum_name(import_type_kind);

		imports_json.push_back(import_json);
	}

	std::cout << json;

	return cli_exit_code::ok;
}

int main(int argc, char* argv[]) {
	std::vector<std::string_view> args;
	args.reserve(argc);
	for(int i=1; argc > i; ++i) {
		args.push_back(std::string_view(argv[i]));
	}
	auto exit_code = cli_entry(args);
	if(exit_code != cli_exit_code::ok) {
		std::cerr
			<< error_prefix() << magic_enum::enum_name(exit_code) << "\n\n"
			<< USAGE;
	}
	return static_cast<int>(exit_code);
}
