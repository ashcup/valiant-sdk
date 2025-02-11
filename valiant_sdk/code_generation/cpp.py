from valiant_sdk.components import ASTNode, FunctionBody, PrintExpression
from valiant_sdk.code_analysis import valiant_analyze
from valiant_sdk.utils import load_text_file

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
        code_analysis_report = valiant_analyze(valiant_ast)
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
            node_source_code = self._generate_node(statement)
            if type(node_source_code) is str and len(node_source_code) > 0:
                source_code += "    " + node_source_code + ";\n"
        source_code += "}\n"
        return source_code

    def _generate_node(self, node: ASTNode) -> str:
        if isinstance(node, PrintExpression) is True:
            return self._generate_print_expression(node)
        return ""

    def _generate_print_expression(self, node: ASTNode) -> str:
        return "valiant::print(" + str(node.message) + ")"
