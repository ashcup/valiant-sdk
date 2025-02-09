import os.path as path

from lark import Lark

from ..parsing import ValiantParser


# Create a new instance of the Valiant parser.
valiant_parser = ValiantParser()


class ValiantCodeGenerator:
    '''
    A code generator designed to take Valiant source code as input and generate source code in another programming language as output.
    '''

    @property
    def target_format(self):
        return self._target_format

    @target_format.setter
    def target_format(
        self,
        value: str
    ):
        self._target_format = value

    def __init__(
            self,
            target_format: str = "cpp"
    ):
        # Default the target format to "cpp" (C++).
        self.target_format = "cpp"
        # Reset the code generator.
        self.reset()

    def generate(
            self,
            valiant_ast: object
    ) -> str:
        '''
        Convert a Valiant AST into source code of the target programming language.
        '''
        # Reset the code generator.
        self.reset()
        # Return the output.
        return self.output

    def get_component_path(
            self,
            component_name: str
    ) -> str:
        # Get the target format.
        target_format = self.target_format
        # Return "./valiant_sdk/code_generation/components/{target_format}/{component_name}.{target_format}".
        return path.join(
            "valiant_sdk",
            "code_generation",
            "components",
            target_format,
            component_name + "." + target_format
        )

    def transpile(
            self,
            valiant_source_code: str
    ) -> str:
        '''
        Convert Valiant source code into source code of the target programming language.
        '''
        # Reset the code generator.
        self.reset()
        # Parse the Valiant source code.
        valiant_ast = valiant_parser.parse(valiant_source_code)
        # Generate source code in the target language.
        output_source_code = self.generate(valiant_ast)
        # Return the generated source code.
        return output_source_code

    def reset(self):
        self.output = ""
