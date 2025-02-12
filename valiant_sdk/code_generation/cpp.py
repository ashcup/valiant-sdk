from lark.lexer import Token

from valiant_sdk.components import ASTNode, AddExpression, AssignExpression, Comment, DeclareVariableExpression, DivideExpression, Expression, FunctionBody, FunctionCallExpression, MultiLineComment, MultiplyExpression, PrintExpression, SingleLineComment, SubtractExpression, VariableExpression
from valiant_sdk.code_analysis import valiant_analyze
from valiant_sdk.utils import load_text_file, resolve_variable_name, throw_code_generator_feature_not_supported

from .code_generator import ValiantCodeGenerator


class CPPCodeGenerator(ValiantCodeGenerator):
    '''
    Generate C++ from Valiant.
    '''

    def __init__(self):
        # Set the target format to "cpp" (C++).
        self.target_format = "cpp"
        # Set the state properties.
        self.output = ""

    def generate(
            self,
            valiant_ast: object
    ) -> str:
        # Analyze the source code.
        # DEBUG: To debug the AST, comment out the following line and uncomment the line after that.
        code_analysis_report = valiant_analyze(valiant_ast, debug=False)
        # code_analysis_report = valiant_analyze(valiant_ast, debug=True)
        # Get the main function body from the analyzed source code.
        main_function_body = code_analysis_report.body
        # Get a list of event handlers in the analyzed source code.
        event_handlers = code_analysis_report.event_handlers
        # Load the source code header for the target programming language.
        header_path = self.get_component_path("header")
        self.output = load_text_file(header_path) + "\n\n"
        # Add all top-level statements to the output source code.
        self.output += self._generate_main_function(main_function_body)
        # Load the source code footer for the target programming language.
        footer_path = self.get_component_path("footer")
        self.output += "\n\n" + load_text_file(footer_path) + "\n"
        # Return the generated source code.
        return self.output.strip()

    def _generate_main_function(self, main_function_body: FunctionBody) -> str:
        function_body_source_code = self._generate_function_body(main_function_body)
        source_code = "int main(int argc, char *argv[])\n" + function_body_source_code + "\n"
        return source_code

    def _generate_multi_line_comment(self, comment: MultiLineComment) -> str:
        return "/* " + comment.value + " */";

    def _generate_single_line_comment(self, comment: SingleLineComment) -> str:
        return "// " + comment.value;

    def _generate_assign_expression(self, expression: AssignExpression, function_body: FunctionBody) -> str:
        variable_source_code = self._generate_variable_expression(expression.variable, function_body)
        assignment_source_code = self._generate_expression(expression.assignment, function_body)
        source_code = variable_source_code + " = " + assignment_source_code
        return source_code

    def _generate_add_expression(self, expression: AddExpression, function_body: FunctionBody) -> str:
        left_expression_source_code = self._generate_expression(expression.left_expression, function_body)
        right_expression_source_code = self._generate_expression(expression.right_expression, function_body)
        source_code = left_expression_source_code + " + " + right_expression_source_code
        return source_code

    def _generate_subtract_expression(self, expression: SubtractExpression, function_body: FunctionBody) -> str:
        left_expression_source_code = self._generate_expression(expression.left_expression, function_body)
        right_expression_source_code = self._generate_expression(expression.right_expression, function_body)
        source_code = left_expression_source_code + " - " + right_expression_source_code
        return source_code

    def _generate_multiply_expression(self, expression: MultiplyExpression, function_body: FunctionBody) -> str:
        left_expression_source_code = self._generate_expression(expression.left_expression, function_body)
        right_expression_source_code = self._generate_expression(expression.right_expression, function_body)
        source_code = left_expression_source_code + " * " + right_expression_source_code
        return source_code

    def _generate_divide_expression(self, expression: DivideExpression, function_body: FunctionBody) -> str:
        left_expression_source_code = self._generate_expression(expression.left_expression, function_body)
        right_expression_source_code = self._generate_expression(expression.right_expression, function_body)
        source_code = left_expression_source_code + " / " + right_expression_source_code
        return source_code

    def _generate_comment(self, comment: Comment) -> str:
        # Multi-line Comment
        if isinstance(comment, MultiLineComment) is True:
            return self._generate_multi_line_comment(comment)
        # Single-line Comment
        if isinstance(comment, SingleLineComment) is True:
            return self._generate_single_line_comment(comment)
        throw_code_generator_feature_not_supported("cpp", comment)

    def _generate_expression(self, expression: Expression, function_body: FunctionBody) -> str:
        # Token
        if isinstance(expression, Token) is True:
            return str(expression)
        # Assign Expression
        if isinstance(expression, AssignExpression) is True:
            return self._generate_assign_expression(expression, function_body)
        # Add Expression
        if isinstance(expression, AddExpression) is True:
            return self._generate_add_expression(expression, function_body)
        # Subtract Expression
        if isinstance(expression, SubtractExpression) is True:
            return self._generate_subtract_expression(expression, function_body)
        # Multiply Expression
        if isinstance(expression, MultiplyExpression) is True:
            return self._generate_multiply_expression(expression, function_body)
        # Divide Expression
        if isinstance(expression, DivideExpression) is True:
            return self._generate_divide_expression(expression, function_body)
        # Function Call Expression
        if isinstance(expression, FunctionCallExpression) is True:
            return self._generate_function_call_expression(expression, function_body)
        # Print Expression
        if isinstance(expression, PrintExpression) is True:
            return self._generate_print_expression(expression, function_body)
        throw_code_generator_feature_not_supported("cpp", expression)

    def _generate_csv(self, expressions: list[Expression], function_body: FunctionBody) -> str:
        # Create an empty list of source code for each expression.
        expression_source_codes = []
        # Loop expressions:
        for expression in expressions:
            # Declare the expression source code variable.
            expression_source_code = None
            # If the expression is a literal:
            if isinstance(expression, Token):
                expression_source_code = str(expression)
            # If the expression is a variable:
            if isinstance(expression, VariableExpression):
                expression_source_code = self._generate_variable_expression(expression, function_body)
            # If the expression failed to generate source code:
            if expression_source_code is None:
                # Throw an error.
                throw_code_generator_feature_not_supported("cpp", expression)
            # Add the expression's source code to the list.
            expression_source_codes.append(expression_source_code)
        # Concatenate the source code for each expression, separated by commas.
        source_code = ", ".join(expression_source_codes)
        # Return the source code.
        return source_code

    def _generate_function_body(self, function_body: FunctionBody) -> str:
        # Start with a left curly brace.
        source_code = "{\n"
        # Loop the function body:
        for statement in function_body:
            # Generate source code for the statement.
            statement_source_code = self._generate_statement(statement, function_body)
            # If the statement generated source code:
            if type(statement_source_code) is str and len(statement_source_code) > 0:
                # Add the statement's source code to the function's body.
                source_code += "    " + statement_source_code + "\n"
        # End with a right curly brace.
        source_code += "}"
        # Return the source code.
        return source_code

    def _generate_function_call_expression(self, function_call_expression: FunctionCallExpression, function_body: FunctionBody) -> str:
        # Get the global ID of the function.
        function_id = function_call_expression.name
        # Get the list of function call arguments.
        args_source_code = self._generate_csv(function_call_expression.args, function_body)
        # Generate the source code for the function call expression.
        source_code = function_id + "(" + args_source_code + ")"
        # Return the source code.
        return source_code

    def _generate_statement(self, expression: Expression, function_body: FunctionBody) -> str:
        # Comments
        if isinstance(expression, Comment) is True:
            return self._generate_comment(expression)
        # Expressions
        if isinstance(expression, Expression) is True:
            return self._generate_expression(expression, function_body) + ";"
        throw_code_generator_feature_not_supported("cpp", expression)

    def _generate_print_expression(self, print_expression: PrintExpression, function_body: FunctionBody) -> str:
        message_source_code = self._generate_expression(print_expression.message)
        return "valiant::print(" + message_source_code + ")"

    def _generate_variable_expression(self, variable: VariableExpression, function_body: FunctionBody) -> str:
        # Resolve the variable name.
        resolved_variable_name = resolve_variable_name(function_body.id, variable.name)
        # If the variable expression is a variable declaration expression:
        if isinstance(variable, DeclareVariableExpression):
            # Return a local variable declaration.
            return "auto " + resolved_variable_name
        # Return the resolved variable name.
        return resolved_variable_name
