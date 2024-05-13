import pathlib
import subprocess

import colorama

from .constants import RETURN_CODE_SUCCESS, RETURN_CODE_ERROR


def create_empty_file(file_path: pathlib.Path):
    try:
        open(file_path, 'a').close()
    except OSError:
        pass


def execute_program(command: str, cwd: pathlib.Path = None) -> int:
    with subprocess.Popen(command, shell=True, stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE, cwd=cwd,
                          universal_newlines=True, encoding='utf-8',
                          bufsize=1) as p:
        for line in p.stdout:
            print(line, end='')
    return RETURN_CODE_ERROR if p.returncode != 0 else RETURN_CODE_SUCCESS


def print_error_msg(msg: str) -> None:
    print(colorama.Fore.RED + msg)
