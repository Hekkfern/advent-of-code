#!/usr/bin/env python

import argparse
import sys
import shutil
import pathlib
import git
import colorama


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
    parser_build = subparsers.add_parser('build', help="Cleans, generates and compiles the project.")
    parser_generate = subparsers.add_parser('generate', help="Generates the project with CMake.")
    parser_generate.add_argument("-d", "--debug", action="store_true", help="Sets the debug flags into the compilation environment.")
    parser_generate.add_argument(
        "-ut", "--unit-tests", action="store_true", help="Generates the unit-test project too.")
    parser_compile = subparsers.add_parser('compile', help="Compiles the CMake project if it was previously generated.")
    parser_update = subparsers.add_parser('update', help="Downloads the latest version of this project and updates all its dependencies.")
    parser_clean = subparsers.add_parser('clean', help="Deletes all the local data stored in the project.")
    parser_addday = subparsers.add_parser('add_day', help='Set up the project to add a new "Advent Of Code" puzzle.')
    parser_addday.add_argument(
        "-y", "--year", type=int, required=True, help="Selects the year (format XXXX, as for instance, 2023) of the puzzle to generate.")
    parser_addday.add_argument(
        "-d", "--day", type=int, required=True, help="Selects the day (from 1 to 25) of the puzzle to generate.")

    return parser.parse_args()


def main():
    colorama.init()

    __check_min_python_version()

    args = __get_input_parameters()
    if args.subcommand == "build":
        pass
    elif args.subcommand == "update":
        pass
    elif args.subcommand == "generate":
        pass
    elif args.subcommand == "compile":
        pass
    elif args.subcommand == "update":
        pass
    elif args.subcommand == "clean":
        pass
    elif args.subcommand == "add_day":
        pass
    else:
        print("This script requires Python version 3.7")
        sys.exit(1)


if __name__ == "__main__":
    main()
    sys.exit(0)
