from . import code_generator
from . import cpp

from .code_generator import ValiantCodeGenerator
from .cpp import CPPCodeGenerator


def _valiant_get_code_generator(
    output_language: str
) -> ValiantCodeGenerator:
    '''
    Create an instance of the code generator for the output language.
    '''
    # Get the code generator for the output language.
    code_generator = None
    # C++
    if output_language == "cpp":
        code_generator = CPPCodeGenerator()
    # Dummy code generator
    else:
        code_generator = ValiantCodeGenerator()
    # Return the code generator.
    return code_generator


def valiant_transpile(
    valiant_source_code: str,
    output_format: str = "cpp"
) -> str:
    '''
    Compile Valiant source code into a target programming language.
    '''
    # Create an instance of the code generator for the output language.
    code_generator = _valiant_get_code_generator(output_format)
    # Transpile the source code from Valiant to the target programming language.
    output_source_code = code_generator.transpile(valiant_source_code)
    # Return the generated source code.
    return output_source_code
