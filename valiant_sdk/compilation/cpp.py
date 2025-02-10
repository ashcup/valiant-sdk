from valiant_sdk.code_generation import CPPCodeGenerator
from valiant_sdk.compilation.compiler import ValiantCompiler
from valiant_sdk.utils import load_text_files_as_one, save_text_file


class CPPCompiler(ValiantCompiler):
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
