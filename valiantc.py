from codegen import valiant_transpile
from utils import load_text_file

# Load the source code.
valiant_source_code = load_text_file("examples/hello_world.valiant")

# Generate C++ output source code from the Valiant input source code.
cpp_source_code = valiant_transpile(valiant_source_code, "cpp")

# Print the generated source code.
print(cpp_source_code)
