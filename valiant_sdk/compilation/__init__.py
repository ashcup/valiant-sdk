from valiant_sdk.code_generation.cpp import CPPCodeGenerator
from valiant_sdk.utils import load_text_files_as_one

from . import compiler
from . import cpp

from .compiler import ValiantCompiler
from .cpp import CPPCompiler


def valiant_compile(
    input_files = [],
    output_path = None,
    output_format = "cpp"
):
    '''
    Compile Valiant source code into the target programming language.
    '''
    if output_format == "c":
        # TODO: Implement support for C as a target programming language.
        pass
    elif output_format == "cpp":
        compiler = CPPCompiler()
    elif output_format == "java":
        # TODO: Implement support for Java as a target programming language.
        pass
    elif output_format == "js":
        # TODO: Implement support for JavaScript as a target programming language.
        pass
    elif output_format == "rs":
        # TODO: Implement support for Rust as a target programming language.
        pass
    elif output_format == "ts":
        # TODO: Implement support for TypeScript as a target programming language.
        pass
    else:
        compiler = ValiantCompiler()
    # Compile the input files and write the generated source code to the file located at the output path.
    compiler.compile(input_files, output_path)
