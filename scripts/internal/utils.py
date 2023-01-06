import pathlib

def create_empty_file(file_path: pathlib.Path):
    try:
        open(file_path, 'a').close()
    except OSError:
        pass
