import pathlib
import subprocess


def create_empty_file(file_path: pathlib.Path):
    try:
        open(file_path, 'a').close()
    except OSError:
        pass


def execute_program(command: str, cwd: pathlib.Path = None):
    with subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=cwd,
                          universal_newlines=True, encoding='utf-8', bufsize=1) as p:
        for line in p.stdout:
            print(line, end='')
