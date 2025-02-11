from ast import Expression
from lark import Tree # type: ignore
from lark.lexer import Token # type: ignore
from valiant_sdk.parsing import valiant_parse
from valiant_sdk.utils import abort, throw_feature_not_supported, throw_token_not_supported

from .components import ASTNode, Comment, EventHandler, FunctionBody, MultiLineComment, PrintExpression, SingleLineComment, TopLevelDefinition


class ValiantCodeAnalysisReport():
    '''
    An analysis report of Valiant source code.
    '''

    @property
    def body(self) -> FunctionBody:
        '''
        A collection of top-level statements defined in the source code currently being parsed.
        '''
        return self._body

    @property
    def event_handlers(self) -> list[EventHandler]:
        '''
        A collection of event handlers defined in the source code currently being parsed.
        '''
        return self._event_handlers

    def __init__(
        self,
        valiant_ast,
        debug = False
    ):
        super().__init__()

        self._body: FunctionBody = FunctionBody()
        '''
        A collection of top-level statements defined in the source code currently being parsed.
        '''

        self._event_handlers: list[EventHandler] = []
        '''
        A collection of event handlers defined in the source code currently being parsed.
        '''

        self._functions: list[FunctionBody] = []
        '''
        A collection of functions defined in the source code currently being parsed.
        '''

        self._imports: list[str] = []
        '''
        A collection of modules imported in the source code currently being parsed.
        '''

        self._includes: list[str] = []
        '''
        A collection of files included in the source code currently being parsed.
        '''

        self._types: list[str] = []
        '''
        A collection of types defined in the source code currently being parsed.
        '''
        if debug:
            print(valiant_ast.pretty())
            exit()
        # Analyze all top-level statements.
        for node in valiant_ast.children:
            self._analyze_top_level_definition(node)
        # Add all event handlers to the body.
        self._add_event_handlers_to_body()

    def _add_event_handler_to_body(self, event_handler: EventHandler):
        # Get the event handler's body.
        function_body = event_handler.body
        # Loop all statements in the event handler's body.
        for statement in function_body:
            # Add the statement to the body.
            self.body.append(statement)

    def _add_event_handlers_to_body(self):
        # Get all of the event handlers registered in the analyzed source code.
        event_handlers = self.event_handlers
        # Create a mapping of event names to lists of event handlers matching that name.
        event_handler_map: dict[str, list[EventHandler]] = {}
        event_handler_map["start"] = []
        event_handler_map["stop"] = []
        # Loop each event handler:
        for event_handler in event_handlers:
            event_name = event_handler.name
            if event_handler_map[event_name] is None:
                event_handler_map[event_name] = []
            event_handler_map[event_name].append(event_handler)
        # Loop each start event handler:
        for event_handler in event_handler_map["start"]:
            # Add the event handler to the body.
            self._add_event_handler_to_body(event_handler)
        # Loop each stop event handler:
        for event_handler in event_handler_map["stop"]:
            # Add the event handler to the body.
            self._add_event_handler_to_body(event_handler)

    def _analyze_comment(self, node: object) -> Comment:
        # Unbox the node.
        unboxed_node = node.children[0]
        # Get the unboxed node's type.
        unboxed_node_type = unboxed_node.data
        # If the unboxed node is a multi-line comment:
        if unboxed_node_type == "multi_line_comment":
            # Analyze the comment.
            return self._analyze_multi_line_comment(unboxed_node)
        # If the unboxed node is a single-line comment:
        if unboxed_node_type == "single_line_comment":
            # Analyze the comment.
            return self._analyze_single_line_comment(unboxed_node)
        # Throw an error.
        throw_feature_not_supported(unboxed_node_type)

    def _analyze_multi_line_comment(self, node: object) -> MultiLineComment:
        # Unbox the node.
        comment = node.children[0]
        # Return the comment.
        return MultiLineComment(comment)

    def _analyze_single_line_comment(self, node: object) -> SingleLineComment:
        # Unbox the node.
        comment = node.children[0]
        # Return the comment.
        return SingleLineComment(comment)

    def _analyze_event_handler(self, node: object) -> EventHandler:
        # Analyze the event name.
        event_name_node = node.children[0]
        if event_name_node.data != "event_name":
            throw_feature_not_supported(event_name_node)
        event_name = self._analyze_event_name(event_name_node)
        # Validate the event handler's body.
        function_body_node = node.children[1]
        if function_body_node.data != "function_body":
            throw_feature_not_supported(function_body_node)
        # Analyze the event handler's body.
        function_body = self._analyze_function_body(function_body_node)
        # Create the event handler.
        event_handler = EventHandler(event_name, function_body)
        # Register the event handler.
        self.event_handlers.append(event_handler)
        # Return the event handler.
        return event_handler

    def _analyze_event_name(self, node: object) -> str:
        # Unbox the node.
        unboxed_node = node.children[0]
        # Get the unboxed node's type.
        unboxed_node_type: str = unboxed_node.data
        # Get the event's name.
        event_name = unboxed_node_type.split("event_name_")[1]
        # If the event's name is a valid event name:
        if type(event_name) is str and len(event_name) > 0:
            # Return the literal.
            return event_name
        # Throw an error if an unsupported feature was used.
        throw_feature_not_supported(unboxed_node_type)

    def _analyze_expression(self, node: object) -> Expression:
        # Unbox the node.
        unboxed_node = node.children[0]
        # Get the unboxed node's type.
        unboxed_node_type = unboxed_node.data
        # If the unboxed node is a literal:
        if unboxed_node_type == "literal":
            # Analyze the event handler.
            return self._analyze_literal(unboxed_node)
        # If the unboxed node is a print expression:
        if unboxed_node_type == "print_expression":
            # Analyze the event handler.
            return self._analyze_print_expression(unboxed_node)
        # Throw an error.
        throw_feature_not_supported(unboxed_node_type)

    def _analyze_function_body(self, node: object) -> FunctionBody:
        # Get a list of all statements in the function body.
        statement_nodes = node.children
        # Create an empty list of statements.
        statements = []
        # For each statement node:
        for statement_node in statement_nodes:
            # Get the type of the statement node.
            statement_node_type = statement_node.data
            # If the node is not a valid statement:
            if statement_node_type != "statement":
                # Throw an error.
                throw_feature_not_supported(statement_node_type)
            # Add the analyzed statement to the list.
            statement = self._analyze_statement(statement_node)
            statements.append(statement)
        # Return the function body.
        return FunctionBody(statements)

    def _analyze_literal(self, node: object) -> object:
        # Unbox the node.
        unboxed_node = node.children[0]
        # Get the unboxed node's type.
        unboxed_node_type = unboxed_node.data
        # If the unboxed node is an integer literal:
        if unboxed_node_type == "integer_literal":
            # Analyze the unboxed node.
            return self._analyze_integer_literal(unboxed_node)
        # If the unboxed node is a number literal:
        if unboxed_node_type == "number_literal":
            # Analyze the unboxed node.
            return self._analyze_number_literal(unboxed_node)
        # If the unboxed node is a string literal:
        if unboxed_node_type == "string_literal":
            # Analyze the unboxed node.
            return self._analyze_string_literal(unboxed_node)
        # Throw an error.
        throw_feature_not_supported(unboxed_node_type)

    def _analyze_print_expression(self, node: object) -> PrintExpression:
        # Unbox the node.
        message_node = node.children[0]
        # Get the unboxed node's type.
        message_node_type = message_node.data
        # If the unboxed node is invalid:
        if message_node_type != "expression":
            # Throw an error.
            throw_feature_not_supported(message_node_type)
        # Analyze the message.
        message = self._analyze_expression(message_node)
        # Return the expression.
        return PrintExpression(message)

    def _analyze_string_literal(self, node: object) -> str:
        unboxed_value = node.children[0]
        return str(unboxed_value)

    def _analyze_top_level_definition(self, node: object) -> TopLevelDefinition:
        # Unbox the node.
        unboxed_node = node.children[0]
        # Get the unboxed node's type.
        unboxed_node_type = unboxed_node.data
        # If the unboxed node is a comment:
        if unboxed_node_type == "comment":
            # Analyze the comment.
            return self._analyze_comment(unboxed_node)
        # If the unboxed node is an event handler:
        if unboxed_node_type == "event_handler":
            # Analyze the event handler.
            return self._analyze_event_handler(unboxed_node)
        # Throw an error.
        throw_feature_not_supported(unboxed_node_type)

    def _analyze_statement(self, node: object) -> Expression:
        # Unbox the node.
        unboxed_node = node.children[0]
        # Get the unboxed node's type.
        unboxed_node_type = unboxed_node.data
        # If the unboxed node is valid:
        if unboxed_node_type == "comment":
            # Analyze the event handler.
            return self._analyze_comment(unboxed_node)
        # If the unboxed node is valid:
        if unboxed_node_type == "expression":
            # Analyze the event handler.
            return self._analyze_expression(unboxed_node)
        # Throw an error.
        throw_feature_not_supported(unboxed_node_type)

    def _analyze_token(self, token: Token) -> object:
        '''
        Analyze a single token of Valiant source code.
        '''
        literal = None
        # If the token is a string:
        if token.type == "ESCAPED_STRING":
            literal = token.value
        # If the token is a number:
        elif token.type == "SIGNED_NUMBER":
            literal = token.value
        # If the token was successfully parsed:
        if literal is not None:
            # Return the parsed token.
            return literal
        # Abort due to unsupported token type.
        throw_token_not_supported(token.type)



class ValiantCodeAnalyzer():
    '''
    Analyze Valiant source code.
    '''

    def __init__(self, debug: bool = False):
        self.debug = debug

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
            return self._analyze_ast(valiant_translation_unit, self.debug)

    def _analyze_ast(self, valiant_ast: object, debug: bool = False):
        '''
        Analyze a Valiant AST.
        '''
        # Analyze the AST and return the report.
        return ValiantCodeAnalysisReport(valiant_ast, debug)

    def _analyze_source_code(self, valiant_source_code: str, debug: bool = False):
        '''
        Analyze a Valiant AST.
        '''
        # Parse the source code.
        valiant_ast = valiant_parse(valiant_source_code)
        # Analyze the AST obtained from parsing and return the report.
        return ValiantCodeAnalysisReport(valiant_ast, debug)


def valiant_analyze(valiant_translation_unit: object | str, debug: bool = False) -> ValiantCodeAnalysisReport:
    '''
    Analyze either an AST or a string of Valiant source code.
    '''
    # Create a new instance of the code analyzer.
    code_analyzer = ValiantCodeAnalyzer(debug)
    # Analyze the Valiant AST.
    code_analysis_report = code_analyzer.analyze(valiant_translation_unit)
    # Return the code analysis report.
    return code_analysis_report
