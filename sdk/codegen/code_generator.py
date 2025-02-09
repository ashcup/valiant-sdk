from lark import Lark

from ..parsing import ValiantParser


# Create a new instance of the Valiant parser.
valiant_parser = ValiantParser()


class ValiantCodeGenerator:
    '''
    A code generator designed to take Valiant source code as input and generate source code in another programming language as output.
    '''
    # Generate source code in the target format from a Valiant AST.
    def generate(self, valiant_ast):
        '''
        Convert a Valiant AST into source code of the target programming language.
        '''
        return ""

    def transpile(self, valiant_source_code):
        '''
        Convert Valiant source code into source code of the target programming language.
        '''
        # Parse the Valiant source code.
        valiant_ast = valiant_parser.parse(valiant_source_code)
        # Generate source code in the target language.
        output_source_code = self.generate(valiant_ast)
        # Return the generated source code.
        return output_source_code
