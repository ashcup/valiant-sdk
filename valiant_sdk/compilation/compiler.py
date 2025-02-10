from valiant_sdk.code_generation import ValiantCodeGenerator
from valiant_sdk.utils import load_text_files, save_text_file


class ValiantCompiler:
    '''
    A compiler that turns Valiant source code into executable programs.
    '''
    def __init__(
        self
    ):
        self.code_generator = ValiantCodeGenerator()

    def compile(
        self,
        input_files = [],
        output_path = None
    ):
        '''
        Transpile source code from Valiant into the output programming language.
        '''
        if output_path is None:
            output_path = "{DEFAULT_OUTPUT}"
        # Read all input files.
        input_file_separator = "\n\n"
        input_source_code = input_file_separator.join(load_text_files(input_files))
        # Transpile the source code from Valiant into the output programming language.
        output_source_code = self.code_generator.transpile(input_source_code)
        # Save the output source code.
        save_text_file(output_path, output_source_code)
