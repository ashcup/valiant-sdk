import argparse


def abort(
    code: int = 0xFFFFFFFF,
    message: str = ""
):
    '''
    Abort the program by printing `message` and then returning `code`.
    '''
    if (type(message) == str and len(message) > 0):
        print(message)
    else:
        print("An unknown error occured. ")
    exit(code)


def get_default_output(
    format: str
) -> str:
    if format == "c":
        return "main.c"
    if format == "cpp":
        return "main.cpp"
    if format == "js":
        return "index.js"
    if format == "ts":
        return "index.ts"


def load_text_file(
    path: str
) -> str:
    '''
    Load the contents of a text file.
    '''
    # Open the file and close the resource afterwards.
    with open(path, 'r') as file:
        # Read and return the contents of the file.
        return file.read().strip()


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
    program_arguments.output.replace(
        "{DEFAULT_OUTPUT}",
        DEFAULT_OUTPUT
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
