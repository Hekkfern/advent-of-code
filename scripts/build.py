#!/usr/bin/env python

import argparse
import pathlib
import shutil
import sys

import colorama
import git


def __abort_execution(msg: str):
    print(colorama.Fore.RED + msg)
    sys.exit(1)


def __get_root_project_path() -> pathlib.Path:
    return pathlib.Path().absolute().parent


def __check_min_python_version():
    if sys.version_info[0] < 3 or sys.version_info[1] < 7:
        __abort_execution("This script requires Python version 3.7.")


def __fetch_last_version(force: bool = False):
    __clean_project()
    repo = git.Repo(__get_root_project_path())
    if repo.is_dirty():
        if force:
            repo.git.reset(hard=True)
        else:
            __abort_execution("Pending changes to commit in the repository. Save them or discard them, and try again.")
    repo.git.checkout("master")
    repo.remotes.origin.pull()
    print(f'Current commit is {repo.head.object.hexsha} in "master" branch')
    for submodule in repo.submodules:
        submodule.update(init=True)


def __clean_project():
    root_path = __get_root_project_path()
    shutil.rmtree(root_path / "out", ignore_errors=True)
    shutil.rmtree(root_path / "vcpkg_installed", ignore_errors=True)


def __generate_project():
    pass


def __get_input_parameters():
    parser = argparse.ArgumentParser(
        prog='AoC Builder',
        description='Assistant software to operate this project in a easier way')
    parser.add_argument("--no-color", action="store_true",
                        help="Disables all the colors in the output messages.")
    subparsers = parser.add_subparsers(dest="subcommand", required=True)
    parser_build = subparsers.add_parser(
        'build', help="Cleans, generates and compiles the project.")
    parser_generate = subparsers.add_parser(
        'generate', help="Cleans the project and generates the project with CMake from scratch.")
    parser_generate.add_argument("-d", "--debug", action="store_true",
                                 help="Sets the debug flags into the compilation environment.")
    parser_generate.add_argument(
        "-ut", "--unit-tests", action="store_true", help="Generates the unit-test project too.")
    parser_compile = subparsers.add_parser(
        'compile', help="Compiles the CMake project if it was previously generated.")
    parser_update = subparsers.add_parser(
        'update',
        help='Downloads the latest version in "master" branch for this project and updates all its dependencies.')
    parser_update.add_argument("-f", "--force", action="store_true",
                               help="Deletes all the pending changes in the repo.")
    parser_clean = subparsers.add_parser(
        'clean', help="Deletes all the local data stored in the project.")
    parser_addday = subparsers.add_parser(
        'add_day', help='Set up the project to add a new "Advent Of Code" puzzle.')
    parser_addday.add_argument(
        "-y", "--year", type=int, required=True,
        help="Selects the year (format XXXX, as for instance, 2023) of the puzzle to generate.")
    parser_addday.add_argument(
        "-d", "--day", type=int, required=True, help="Selects the day (from 1 to 25) of the puzzle to generate.")

    return parser.parse_args()


def main():
    colorama.init(autoreset=True)

    __check_min_python_version()

    args = __get_input_parameters()
    if args.subcommand == "build":
        pass
    elif args.subcommand == "update":
        __fetch_last_version(args.force)
    elif args.subcommand == "generate":
        __clean_project()
        __generate_project()
    elif args.subcommand == "compile":
        pass
    elif args.subcommand == "clean":
        __clean_project()
    elif args.subcommand == "add_day":
        pass
    else:
        # Unreachable option
        sys.exit(1)


if __name__ == "__main__":
    main()
    print(colorama.Fore.GREEN + "Script finished successfully.")
    sys.exit(0)