import os
import random
import subprocess
import tempfile

from valiant_sdk.code_generation import CPPCodeGenerator
from valiant_sdk.compilation.compiler import ValiantCompiler
from valiant_sdk.utils import load_text_files_as_one, save_text_file


class CPPCompiler(ValiantCompiler):
    def build_exe(
        self,
        input_files = [],
        output_path = None
    ):
        with tempfile.TemporaryDirectory() as tmp_dir:
            # Compile the Valiant source code into C++ IL code.
            il_id = random.randint(0x0000_0000, 0xFFFF_FFFF)
            il_path = os.path.join(tmp_dir, str(il_id) + ".cpp")
            self.compile(input_files, il_path)
            # Compile the C++ IL code into an executable.
            clang_dir = "C:\\" + os.path.join(
                "Program Files",
                "LLVM",
                "bin",
            )
            cpp_compiler_path = os.path.join(
                clang_dir,
                "clang++.exe"
            )
            # Create the command to compile the C++ IL code.
            command = [ cpp_compiler_path ]
            command.append(il_path)
            command.append("-o")
            command.append(output_path)
            # Run the command.
            subprocess.run(command)

    def compile(
        self,
        input_files = [],
        output_path = "{DEFAULT_OUTPUT}"
    ):
        # Load the input source code.
        valiant_source_code = load_text_files_as_one(input_files)
        # Transpile the input source code.
        self.code_generator = CPPCodeGenerator()
        output_source_code = self.code_generator.transpile(valiant_source_code)
        # Save the output source code.
        save_text_file(output_path, output_source_code)
