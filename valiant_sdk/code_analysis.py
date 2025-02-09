from lark.lexer import Token
from valiant_sdk.parsing import valiant_parse
from valiant_sdk.utils import abort

from .components import ASTNode, IntegerLiteral, NumberLiteral, PrintExpression, StringLiteral


class ValiantCodeAnalysisReport():
    '''
    An analysis report of Valiant source code.
    '''

    _body = []
    '''
    A collection of top-level statements defined in the source code currently being parsed.
    '''

    _functions = []
    '''
    A collection of functions defined in the source code currently being parsed.
    '''

    _imports = []
    '''
    A collection of modules imported in the source code currently being parsed.
    '''

    _includes = []
    '''
    A collection of files included in the source code currently being parsed.
    '''

    _types = []
    '''
    A collection of types defined in the source code currently being parsed.
    '''

    @property
    def body(self) -> list:
        '''
        A collection of top-level statements defined in the source code currently being parsed.
        '''
        return self._body

    def __init__(self, valiant_ast):
        # Add all top-level statements to the body.
        for node in valiant_ast.children:
            self._analyze_node(node)

    def _analyze_node(self, node: ASTNode) -> ASTNode:
        # If the node is a token:
        if isinstance(node, Token) is True:
            return self._analyze_token(node)
        # If the node is a token:
        if hasattr(node, "children") is False:
            abort(
                code = 0x49DF_73E2,
                message = "Invalid node: " + str(node)
            )
        if hasattr(node, "data") is True:
            first_child_node = node.children[0]
            node_type = node.data
            if node_type == "expression":
                return self._analyze_node(first_child_node)
            if node_type == "literal":
                return self._analyze_node(first_child_node)
            if node_type == "string_literal":
                literal = StringLiteral()
                literal.value = first_child_node.value
                return literal
        # Loop all children of the node:
        for child_node in node.children:
            # Assume this node is not a token until proven otherwise.
            is_token = False
            # If the node is a token:
            if hasattr(child_node, "data") is False:
                is_token = True
            # If the child node has no data:
            elif child_node.data is None:
                is_token = True
            if is_token is True:
                dir(node)
                exit
                # Analyze the child node.
                self._analyze_node(child_node)
            # Otherwise:
            else:
                # Assume this node isn't a statement until proven otherwise.
                statement = None
                # Get the child node's type.
                child_node_type = child_node.data
                # If the child node is a print statement:
                if (child_node_type == "literal"):
                    # Get the subclass of the literal.
                    return self._analyze_node(child_node.children[0])
                # If the child node is a print statement:
                elif (child_node_type == "print_statement"):
                    # Get the expression to print.
                    expression = self._analyze_node(child_node.children[0])
                    # Get the statement.
                    statement = PrintExpression(expression)
                # Otherwise:
                else:
                    # Throw error "Feature not yet supported: {child_node_type}".
                    print("Feature not yet supported: " + child_node_type)
                    # Stop the program.
                    exit(1)
                # If this node is a statement:
                if statement is not None:
                    # Add the statement to the list.
                    self._body.append(statement)

    def _analyze_token(self, token: Token):
        '''
        Analyze a single token of Valiant source code.
        '''
        # If the token is a string:
        if token.type == "ESCAPED_STRING":
            literal = StringLiteral()
            literal.value = token.value
            return literal
        # If the token is a number:
        elif token.type == "SIGNED_NUMBER":
            literal = NumberLiteral()
            literal.value = float(token.value)
            return literal
        # Abort due to unsupported token type.
        abort(0x274A_B373, "Token type not supported: " + token.type)


class ValiantCodeAnalyzer():
    '''
    Analyze Valiant source code.
    '''

    def analyze(self, valiant_translation_unit: object | str):
        '''
        Analyze either an AST or a string of Valiant source code.
        '''
        # If source code was provided:
        if type(valiant_translation_unit) is str:
            # Analyze the source code.
            return self._analyze_source_code(valiant_translation_unit)
        # Otherwise:
        else:
            # Analyze the AST.
            return self._analyze_ast(valiant_translation_unit)

    def _analyze_ast(self, valiant_ast: object):
        '''
        Analyze a Valiant AST.
        '''
        # Analyze the AST and return the report.
        return ValiantCodeAnalysisReport(valiant_ast)

    def _analyze_source_code(self, valiant_source_code: str):
        '''
        Analyze a Valiant AST.
        '''
        # Parse the source code.
        valiant_ast = valiant_parse(valiant_source_code)
        # Analyze the AST obtained from parsing and return the report.
        return ValiantCodeAnalysisReport(valiant_ast)


def valiant_analyze(valiant_translation_unit: object | str):
    '''
    Analyze either an AST or a string of Valiant source code.
    '''
    # Create a new instance of the code analyzer.
    code_analyzer = ValiantCodeAnalyzer()
    # Analyze the Valiant AST.
    code_analysis_report = code_analyzer.analyze(valiant_translation_unit)
    # Return the code analysis report.
    return code_analysis_report
