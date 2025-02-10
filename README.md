# Valiant SDK

Valiant is a high-level programming language designed to compile to multiple different targets, ranging from C++ desktop applications to webpage JavaScript.
Valiant is designed to be easily read and written by beginners and is modelled closely after the English language.

## Dependencies

### Linux
* `g++`

### Windows
* Visual C++ Redistributable Build Tools
  * [AMD/Intel (64-bit)](https://aka.ms/vs/17/release/vc_redist.x64.exe)
  * [AMD/Intel (32-bit)](https://aka.ms/vs/17/release/vc_redist.x86.exe)
  * [ARM (64-bit)](https://aka.ms/vs/17/release/vc_redist.arm64.exe)

## Installation

* Install the [dependencies](#dependencies).

## Usage

```sh
python valiant.py {input_files} -o {output_file}
```

For example, to compile `hello_world.val` into `hello_world.exe`, you would type:

```sh
python valiant.py hello_world.val -o hello_world.exe
```

## [Examples](https://github.com/voidvoxel/valiant-sdk/tree/main/examples)

A collection of examples of Valiant source code can be found [here](https://github.com/voidvoxel/valiant-sdk/tree/main/examples).
