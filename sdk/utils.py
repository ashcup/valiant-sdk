def load_text_file(path: str) -> str:
    '''
    Load the contents of a text file.
    '''
    # Open the file and close the resource afterwards.
    with open(path, 'r') as file:
        # Read and return the contents of the file.
        return file.read()
