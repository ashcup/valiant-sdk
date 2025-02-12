from lark.lexer import Token

from valiant_sdk.components import ASTNode, Comment, Expression, FunctionBody, FunctionCallExpression, MultiLineComment, PrintExpression, SingleLineComment, VariableExpression
from valiant_sdk.code_analysis import valiant_analyze
from valiant_sdk.utils import load_text_file, throw_code_generator_feature_not_supported

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
        source_code = "int main(int argc, char *argv[])\n{\n"
        for statement in main_function_body:
            node_source_code = self._generate_statement(statement)
            if type(node_source_code) is str and len(node_source_code) > 0:
                source_code += "    " + node_source_code + "\n"
        source_code += "}\n"
        return source_code

    def _generate_multi_line_comment(self, node: MultiLineComment) -> str:
        return "/* " + node.value + " */";

    def _generate_single_line_comment(self, node: SingleLineComment) -> str:
        return "// " + node.value;

    def _generate_comment(self, node: Comment) -> str:
        # Multi-line Comment
        if isinstance(node, MultiLineComment) is True:
            return self._generate_multi_line_comment(node)
        # Single-line Comment
        if isinstance(node, SingleLineComment) is True:
            return self._generate_single_line_comment(node)
        throw_code_generator_feature_not_supported("cpp", node)

    def _generate_expression(self, node: Expression) -> str:
        # Function Call Expression
        if isinstance(node, FunctionCallExpression) is True:
            return self._generate_function_call_expression(node)
        # Print Expression
        if isinstance(node, PrintExpression) is True:
            return self._generate_print_expression(node)
        throw_code_generator_feature_not_supported("cpp", node)

    def _generate_csv(self, expressions: list[Expression]) -> str:
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
                expression_source_code = str(expression.global_id)
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

    def _generate_function_call_expression(self, node: FunctionCallExpression) -> str:
        # Get the global ID of the function.
        function_id = node.global_id
        # Get the list of function call arguments.
        args_source_code = self._generate_csv(node.args)
        # Generate the source code for the function call expression.
        source_code = function_id + "(" + args_source_code + ")"
        # Return the source code.
        return source_code

    def _generate_statement(self, node: ASTNode) -> str:
        # Comments
        if isinstance(node, Comment) is True:
            return self._generate_comment(node)
        # Expressions
        if isinstance(node, Expression) is True:
            return self._generate_expression(node) + ";"
        throw_code_generator_feature_not_supported("cpp", node)

    def _generate_print_expression(self, node: ASTNode) -> str:
        return "valiant::print(" + str(node.message) + ")"
