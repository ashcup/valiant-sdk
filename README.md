# Valiant SDK

Valiant is a high-level programming language designed to compile to multiple different targets, ranging from C++ desktop applications to webpage JavaScript.
Valiant is designed to be easily read and written by beginners and is modelled closely after the English language.

## Dependencies

### Linux
* `g++`

### Windows
* [MS Build Tools](https://aka.ms/vs/17/release/vs_BuildTools.exe)
* [LLVM](https://github.com/llvm/llvm-project/releases) *(Direct download links below)*
  * [AMD/Intel (64-bit)](https://github.com/llvm/llvm-project/releases/download/llvmorg-20.1.0-rc1/LLVM-20.1.0-rc1-win64.exe)
  * [AMD/Intel (32-bit)](https://github.com/llvm/llvm-project/releases/download/llvmorg-20.1.0-rc1/LLVM-20.1.0-rc1-win32.exe)

## Installation

* Install the [dependencies](#dependencies).

## Usage

`type_this_exactly`, `{replace_these_variables}`, `[this_is_optional]`

```sh
python valiant.py {input_files} -o {output_file} -f {output_format}
```

For example, to compile `hello_world.val` into `hello_world.exe`, you would type:

```sh
python valiant.py hello_world.val -o hello_world.cpp -f cpp
```

## [Examples](https://github.com/voidvoxel/valiant-sdk/tree/main/examples)

A collection of examples of Valiant source code can be found [here](https://github.com/voidvoxel/valiant-sdk/tree/main/examples).
