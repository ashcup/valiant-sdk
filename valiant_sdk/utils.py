import argparse


def _get_default_output(
    format: str
) -> str:
    # Windows Executable
    if format == "exe":
        return "program.exe"
    # C
    if format == "c":
        return "main.c"
    # C++
    if format == "cpp":
        return "main.cpp"
    # Java
    if format == "java":
        return "main.java"
    # JavaScript
    if format == "js":
        return "index.js"
    # TypeScript
    if format == "ts":
        return "index.ts"
    # Default
    return "program"


def abort(
    code: int = 0xFFFFFFFF,
    message: str = ""
):
    '''
    Abort the program by printing `message` and then returning `code`.
    '''
    # If a message was provided:
    if (type(message) is str and len(message) > 0):
        # Print the error message.
        print("[Error " + hex(code) + "] " + message)
    # Otherwise:
    else:
        # Print a generic error message.
        print("[Error " + hex(code) + "] An unknown error occured. ")
    # DEBUG: To debug errors, uncomment the following line and re-run.
    raise Exception()
    # Exit the program, returning the provided exit code.
    exit(code)


def list_str(values: list[object]) -> list[str]:
    converted_values = []
    for value in values:
        converted_value = str(value)
        converted_values.append(converted_value)
    return converted_values


def throw_feature_not_supported(
    feature_name: str
):
    abort(
        code = 0x111E_ED42,
        message = "Feature not yet supported: " + feature_name
    )


def throw_code_analyzer_feature_not_supported(
    feature_name: str
):
    throw_feature_not_supported("code_analyzer/" + feature_name)


def throw_code_generator_feature_not_supported(
    code_generator_name: str,
    feature: object
):
    throw_feature_not_supported("code_generator/" + code_generator_name + "/" + feature.__class__.__name__)


def throw_token_not_supported(
    token_type: str
):
    abort(
        code = 0x274A_B373,
        message = "Token type not supported: " + token_type
    )


def load_text_file(
    file_path: str
) -> str:
    '''
    Load the contents of a text file.
    '''
    # Open the file and close the resource afterwards.
    with open(file_path, 'r') as file:
        # Read and return the contents of the file.
        return file.read().strip()


def load_text_files(
    input_paths: list[str]
) -> list[str]:
    '''
    Load the contents of multiple text files.
    '''
    # Create an empty list to hold the contents of each file.
    file_contents = []
    # For each file path:
    for file_path in input_paths:
        # Load the contents of the text file.
        file_content = load_text_file(file_path)
        # Add the contents of the text file to the list.
        file_contents.append(file_content)
    # Return the list of contents of each file.
    return file_contents


def load_text_files_as_one(
    input_paths: list[str]
) -> str:
    '''
    Load the contents of multiple text files as one string.
    '''
    file_contents = load_text_files(input_paths)
    return "\n".join(file_contents)


def parse_program_arguments() -> object:
    '''
    Parse any arguments passed to the program.
    '''
    # Create a new program argument parser.
    argument_parser = argparse.ArgumentParser(
        prog = "valiantsdk",
        description = "Valiant SDK",
        epilog = "Made with lots of love <3",
        usage = "valiantc <input_files> [options] -o <output_file>"
    )
    # Add arguments to the parser.
    argument_parser.add_argument(
        "input",
        action = "extend",
        nargs = "+",
        type = str
    )
    argument_parser.add_argument(
        "--debug",
        type = bool,
        default = False
    )
    # argument_parser.add_argument("-h", "--help")
    argument_parser.add_argument(
        "-f",
        "--format",
        type = str,
        default = "cpp"
    )
    argument_parser.add_argument(
        "-o",
        "--output",
        type = str,
        default = "{DEFAULT_OUTPUT}"
    )
    # argument_parser.add_argument("--usage")
    argument_parser.add_argument("-V", "--verbose")
    # argument_parser.add_argument("-v", "--version")
    # Parse the program arguments.
    program_arguments = argument_parser.parse_args()
    output_format = program_arguments.format
    program_arguments.output.replace(
        "{DEFAULT_OUTPUT}",
        _get_default_output(output_format)
    )
    # Return the program's arguments.
    return program_arguments


def save_text_file(
    path: str,
    data: str
):
    '''
    Save the contents of a text file.
    '''
    # Open the file and close the resource afterwards.
    with open(path, 'w') as file:
        # Write the contents of the file.
        return file.write(data)
