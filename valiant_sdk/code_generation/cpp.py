from valiant_sdk.components import ASTNode, PrintExpression
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
        # Load the source code header for the target programming language.
        header_path = self.get_component_path("header")
        self.output = load_text_file(header_path) + "\n\n"
        # Add all top-level statements to the output source code.
        self.output += "int main(int argc, char *argv[])\n{\n";
        for statement in code_analysis_report.body:
            node_source_code = self._generate_node(statement)
            if type(node_source_code) is str and len(node_source_code) > 0:
                self.output += "    " + node_source_code + ";\n"
        self.output += "}\n"
        # Load the source code footer for the target programming language.
        footer_path = self.get_component_path("footer")
        self.output += "\n\n" + load_text_file(footer_path) + "\n"
        # Return the generated source code.
        return self.output.strip()

    def _generate_node(self, node: ASTNode):
        source_code = None
        if isinstance(node, PrintExpression) is True:
            source_code = "valiant::print(" + str(node.message) + ")"
        return source_code
