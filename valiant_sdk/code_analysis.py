from lark import Tree # type: ignore
from lark.lexer import Token # type: ignore
from valiant_sdk.parsing import valiant_parse
from valiant_sdk.utils import abort, throw_code_analyzer_feature_not_supported, throw_token_not_supported

from .components import AddExpression, AssignExpression, Comment, DeclareVariableExpression, DivideExpression, EventHandler, Expression, FunctionBody, FunctionCallExpression, MathExpression, MultiLineComment, MultiplyExpression, PrintExpression, SingleLineComment, SubtractExpression, TopLevelDefinition, VariableExpression


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
            if event_name not in event_handler_map:
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

    def _analyze_add_expression(self, node: Tree) -> AddExpression:
        left_expression = self._analyze_expression(node.children[0])
        right_expression = self._analyze_expression(node.children[1])
        return AddExpression(left_expression, right_expression)

    def _analyze_subtract_expression(self, node: Tree) -> SubtractExpression:
        left_expression = self._analyze_expression(node.children[0])
        right_expression = self._analyze_expression(node.children[1])
        return SubtractExpression(left_expression, right_expression)

    def _analyze_multiply_expression(self, node: Tree) -> MultiplyExpression:
        left_expression = self._analyze_expression(node.children[0])
        right_expression = self._analyze_expression(node.children[1])
        return MultiplyExpression(left_expression, right_expression)

    def _analyze_divide_expression(self, node: Tree) -> DivideExpression:
        left_expression = self._analyze_expression(node.children[0])
        right_expression = self._analyze_expression(node.children[1])
        return DivideExpression(left_expression, right_expression)

    def _analyze_assign_expression(self, node: Tree) -> AssignExpression:
        # Get the variable expression.
        variable_expression = self._analyze_variable_expression(node.children[0])
        # Get the expression.
        expression = self._analyze_expression(node.children[1])
        # Return the expression.
        return AssignExpression(variable_expression, expression)

    def _analyze_comment(self, node: Tree) -> Comment:
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
        throw_code_analyzer_feature_not_supported(unboxed_node_type)

    def _analyze_csv(self, node: Tree | None) -> list[Expression]:
        # Create an empty CSV row.
        csv_row = []
        # If a CSV node is present:
        if node is not None:
            # If the CSV node is valid:
            if node.data == "csv":
                # Loop each element in the CSV node:
                for raw_csv_element in node.children:
                    # Analyze the CSV element.
                    csv_element = self._analyze_expression(raw_csv_element)
                    # Add the element to the row.
                    csv_row.append(csv_element)
        # Return the CSV row.
        return csv_row

    def _analyze_multi_line_comment(self, node: Tree) -> MultiLineComment:
        # Unbox the node.
        comment = node.children[0]
        # Return the comment.
        return MultiLineComment(comment)

    def _analyze_single_line_comment(self, node: Tree) -> SingleLineComment:
        # Unbox the node.
        comment = node.children[0]
        # Return the comment.
        return SingleLineComment(comment)

    def _analyze_event_handler(self, node: Tree) -> EventHandler:
        # Analyze the event name.
        event_name_node = node.children[0]
        if event_name_node.data != "event_name":
            throw_code_analyzer_feature_not_supported(event_name_node)
        event_name = self._analyze_event_name(event_name_node)
        # Validate the event handler's body.
        function_body_node = node.children[1]
        if function_body_node.data != "function_body":
            throw_code_analyzer_feature_not_supported(function_body_node)
        # Analyze the event handler's body.
        function_body = self._analyze_function_body(function_body_node)
        # Create the event handler.
        event_handler = EventHandler(event_name, function_body)
        # Register the event handler.
        self.event_handlers.append(event_handler)
        # Return the event handler.
        return event_handler

    def _analyze_event_name(self, node: Tree) -> str:
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
        throw_code_analyzer_feature_not_supported(unboxed_node_type)

    def _analyze_expression(self, node: Tree) -> Expression:
        # Unbox the node.
        unboxed_node = node.children[0]
        # Get the unboxed node's type.
        unboxed_node_type = unboxed_node.data
        # If the unboxed node is a literal:
        if unboxed_node_type == "literal":
            # Analyze the unboxed node.
            return self._analyze_literal(unboxed_node)
        # If the unboxed node is a function call expression:
        if unboxed_node_type == "function_call_expression":
            # Analyze the unboxed node.
            return self._analyze_function_call_expression(unboxed_node)
        # If the unboxed node is a math expression:
        if unboxed_node_type == "math_expression":
            # Analyze the unboxed node.
            return self._analyze_math_expression(unboxed_node)
        # If the unboxed node is a print expression:
        if unboxed_node_type == "print_expression":
            # Analyze the unboxed node.
            return self._analyze_print_expression(unboxed_node)
        # If the unboxed node is a variable expression:
        if unboxed_node_type == "variable_expression":
            # Analyze the unboxed node.
            return self._analyze_variable_expression(unboxed_node)
        # Throw an error.
        throw_code_analyzer_feature_not_supported(unboxed_node_type)

    def _analyze_function_call_expression(self, node: Tree) -> FunctionCallExpression:
        # Unbox the node.
        name_node = node.children[0]
        csv_node = None
        if len(node.children) >= 2:
            csv_node = node.children[1]
        # Validate the function name node.
        name = None
        if name_node.data == "variable_name":
            name = self._analyze_variable_name(name_node)
        if name is None:
            throw_code_analyzer_feature_not_supported(name_node.data)
        # Analyze the function arguments node.
        csv_row = self._analyze_csv(csv_node)
        # Return the expression.
        return FunctionCallExpression(name, csv_row)

    def _analyze_variable_name(self, node: Tree) -> str:
        # Unbox the node.
        unboxed_node = node.children[0]
        # Get the unboxed node's type.
        unboxed_node_type = unboxed_node.data
        # Get the variable name.
        variable_name = node.children[0].children[0]
        # If the unboxed node is a variable expression:
        if unboxed_node_type == "class_property_name":
            # Analyze the unboxed node.
            return "-" + variable_name
        # If the unboxed node is a variable expression:
        if unboxed_node_type == "local_variable_name":
            # Analyze the unboxed node.
            return variable_name
        # If the unboxed node is a variable expression:
        if unboxed_node_type == "unmangled_variable_name":
            # Analyze the unboxed node.
            return "@" + variable_name
        # Throw an error.
        throw_code_analyzer_feature_not_supported(unboxed_node_type)


    def _analyze_function_body(self, node: Tree) -> FunctionBody:
        # Get a list of all statements in the function body.
        statement_nodes = node.children
        # Create empty lists to contain data and statistics obtained via analysis of the function body.
        declared_local_variable_names: list[str] = []
        statements: list[Expression] = []
        # For each statement node:
        for statement_node in statement_nodes:
            # Get the type of the statement node.
            statement_node_type = statement_node.data
            # If the node is not a valid statement:
            if statement_node_type != "statement":
                # Throw an error.
                throw_code_analyzer_feature_not_supported(statement_node_type)
            # Add the analyzed statement to the list.
            statement = self._analyze_statement(statement_node)
            # Re-analyze the statement in the context of this function body.
            statement = self._reanalyze_expression_in_function_body(statement, declared_local_variable_names)
            # Add the statement to the list.
            statements.append(statement)
        # Return the function body.
        return FunctionBody(statements)

    def _reanalyze_expression_in_function_body(self, expression: Expression, declared_local_variable_names: list[str]) -> Expression:
        # Get the children nodes of the expression.
        children = expression.children
        # Start with the first node.
        child_index = 0
        # For each child node of the expression:
        for child in children:
            # If the child node is an expression:
            if isinstance(child, Expression):
                # Re-analyze the child expression.
                child = self._reanalyze_expression_in_function_body(child, declared_local_variable_names)
                # Update the child node.
                children[child_index] = child
                # Increment the index.
                child_index += 1
        # If the expression is a variable expression:
        if isinstance(expression, VariableExpression):
            expression = self._reanalyze_variable_expression_in_function_body(expression, declared_local_variable_names)
        # Return the re-analyzed expression.
        return expression


    def _reanalyze_variable_expression_in_function_body(self, variable_expression: VariableExpression, declared_local_variable_names: list[str]) -> VariableExpression:
        # Get the name of the variable.
        variable_name = variable_expression.name
        # If the variable has not been declared:
        if variable_name not in declared_local_variable_names:
            # Declare the variable.
            variable_expression = DeclareVariableExpression(variable_name)
            # Add the variable name to the list of declared local variables.
            declared_local_variable_names.append(variable_name)
        # Return the expression.
        return variable_expression

    def _analyze_literal(self, node: Tree) -> object:
        # Unbox the node.
        unboxed_node = node.children[0]
        # Unbox the value.
        unboxed_value = unboxed_node.children[0]
        # Return the unboxed value.
        return unboxed_value

    def _analyze_math_expression(self, node: Tree) -> MathExpression:
        # Unbox the node.
        unboxed_node = node.children[0]
        # Get the unboxed node's type.
        unboxed_node_type = unboxed_node.data
        # If the unboxed node is an add expression:
        if unboxed_node_type == "add_expression":
            return self._analyze_add_expression(unboxed_node)
        # If the unboxed node is a subtract expression:
        if unboxed_node_type == "subtract_expression":
            return self._analyze_subtract_expression(unboxed_node)
        # If the unboxed node is a multiply expression:
        if unboxed_node_type == "multiply_expression":
            return self._analyze_multiply_expression(unboxed_node)
        # If the unboxed node is a divide expression:
        if unboxed_node_type == "divide_expression":
            return self._analyze_divide_expression(unboxed_node)
        # If the unboxed node is an assign expression:
        if unboxed_node_type == "assign_expression":
            return self._analyze_assign_expression(unboxed_node)
        # Throw an error.
        throw_code_analyzer_feature_not_supported(unboxed_node_type)

    def _analyze_print_expression(self, node: Tree) -> PrintExpression:
        # Unbox the node.
        message_node = node.children[0]
        # Get the unboxed node's type.
        message_node_type = message_node.data
        # If the unboxed node is invalid:
        if message_node_type != "expression":
            # Throw an error.
            throw_code_analyzer_feature_not_supported(message_node_type)
        # Analyze the message.
        message = self._analyze_expression(message_node)
        # Return the expression.
        return PrintExpression(message)

    def _analyze_string_literal(self, node: Tree) -> str:
        unboxed_value = node.children[0]
        return str(unboxed_value)

    def _analyze_top_level_definition(self, node: Tree) -> TopLevelDefinition:
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
        throw_code_analyzer_feature_not_supported(unboxed_node_type)

    def _analyze_statement(self, node: Tree) -> Expression:
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
        throw_code_analyzer_feature_not_supported(unboxed_node_type)

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

    def _analyze_variable_expression(self, node: Tree) -> VariableExpression:
        # Unbox the node.
        unboxed_node = node.children[0]
        # Unbox the value.
        unboxed_value = unboxed_node.children[0].children[0]
        # Get the box type.
        box_type = unboxed_node.children[0].data
        # If the node is a class property name:
        if box_type == "class_property_name":
            # Return the expression.
            return VariableExpression("-" + unboxed_value)
        # If the node is a local variable name:
        if box_type == "local_variable_name":
            # Return the expression.
            return VariableExpression(unboxed_value)
        # If the node is a unmangled variable name:
        if box_type == "unmangled_variable_name":
            # Return the expression.
            return VariableExpression("@" + unboxed_value)
        # Abort due to unsupported token type.
        throw_token_not_supported(unboxed_value)



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
