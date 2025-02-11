#!/usr/bin/env python3

import os.path as path

from valiant_sdk.compilation import valiant_compile
from valiant_sdk.utils import load_text_file, parse_program_arguments, save_text_file


# Parse the arguments passed to the program.
program_arguments = parse_program_arguments()

input_paths = program_arguments.input
output_format = program_arguments.format
output_path = program_arguments.output
is_debug_mode_enabled = program_arguments.debug
is_verbose_mode_enabled = program_arguments.verbose

if output_path is None:
    output_path = input_paths[0] + "." + output_format

# Compile the input files and write the generated source code into the output file.
valiant_compile(
    input_paths,
    output_path,
    output_format
)
