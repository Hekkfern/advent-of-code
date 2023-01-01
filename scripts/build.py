#!/usr/bin/env python

import argparse
import sys
import shutil
import pathlib
import git


def __get_root_project_path() -> pathlib.Path:
    return pathlib.Path().parent


def __check_min_python_version():
    if sys.version_info[0] < 3 or sys.version_info[1] < 7:
        print("This script requires Python version 3.7")
        sys.exit(1)


def __fetch_last_version():
    __clean_project()
    repo = git.Repo(__get_root_project_path())
    repo.remotes.origin.pull()
    for submodule in repo.submodules:
        submodule.update(init=True)


def __clean_project():
    shutil.rmtree(__get_root_project_path() / "out")
    shutil.rmtree(__get_root_project_path() / "vcpkg_installed")


def __generate_project():
    pass


def __get_input_parameters():
    parser = argparse.ArgumentParser(
        prog='AoC Builder',
        description='Assistant software to operate this project in a easier way')
    subparsers = parser.add_subparsers(dest="subcommand", required=True)
    parser_build = subparsers.add_parser('build')
    parser_generate = subparsers.add_parser('generate')
    parser_update = subparsers.add_parser('update')
    parser_generate.add_argument(
        "--unit-tests", action="store_true", help="Generates the unit-test project too.")
    parser_compile = subparsers.add_parser('compile')
    parser_fetch = subparsers.add_parser('fetch')
    parser_clean = subparsers.add_parser('clean')
    parser_addday = subparsers.add_parser('add_day')
    parser_addday.add_argument(
        "-y", "--year", type=int, required=True, help="Selects the year (format XXXX, as for instance, 2023) of the puzzle to generate.")
    parser_addday.add_argument(
        "-d", "--day", type=int, required=True, help="Selects the day (from 1 to 25) of the puzzle to generate.")

    return parser.parse_args()


def main():
    __check_min_python_version()

    args = __get_input_parameters()


if __name__ == "__main__":
    main()
    sys.exit(0)
