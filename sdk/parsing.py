import os.path as path

from lark import Lark

from .utils import load_text_file


# Get the path to the directory this script is contained in.
dirname = path.dirname(path.abspath(__file__))

# Get the path to the grammar file.
grammar_path = path.join(dirname, "grammar.lark")

# Define the grammar of the programming language.
valiant_grammar = load_text_file(grammar_path)


class ValiantParser:
    '''
    A parser designed to convert Valiant source code into an Abstract Syntax Tree (AST).
    '''
    def parse(self, valiant_source_code):
        '''
        Parse Valiant source code into an AST representation of the source code.
        '''
        # Create a new parser using the Valiant grammar.
        parser = Lark(valiant_grammar)
        # Parse the source code.
        valiant_ast = parser.parse(valiant_source_code)
        # Return the parsed AST.
        return valiant_ast
