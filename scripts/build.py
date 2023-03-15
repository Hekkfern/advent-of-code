#!/usr/bin/env python3

import argparse
import pathlib
import sys
import typing

import colorama

from internal import argparse_utils as apr
from internal import utils
from internal.addday_subcommand import add_new_day
from internal.clean_subcommand import clean_project
from internal.cmake_subcommand import run_project, test_project, compile_project, generate_project
from internal.getinput_subcommand import get_input
from internal.getstatements_subcommand import get_statement
from internal.platform_type import PlatformType
from internal.update_subcommand import fetch_last_version


def __get_root_project_path() -> pathlib.Path:
    return pathlib.Path(__file__).absolute().parents[1]


def __check_min_python_version() -> bool:
    if sys.version_info[0] < 3 or sys.version_info[1] < 7:
        utils.print_error_msg(
            "This script requires Python version 3.7 or newer.")
        return False
    return True


def __add_generation_input_arguments(parser):
    parser.add_argument("-r", "--release", action="store_true",
                        help="Sets the release flags into the compilation environment (default: %(default)s)")
    parser.add_argument(
        "--platform", required=True, choices=["windows", "macos", "linux"],
        help="Selects the platform where you are executing this script")
    parser.add_argument(
        "--project", choices=['all', 'exes', 'unittests'], default='all',
        help="Selects which projects wants that CMake generate (default: everything is generated)")
    parser.add_argument(
        "--years", type=apr.ranged_int(2015, 2050), nargs='+',
        help="List of years whose puzzles will only be generated (default: everything is generated)")
    parser.add_argument(
        "--no-ccache", action="store_true",
        help="Disable usage of ccache in the project if it is available")
    parser.add_argument(
        "--no-cppcheck", action="store_true",
        help="Disable usage of cppcheck in the project if it is available")


def __add_session_arguments(parser):
    session_group = parser.add_mutually_exclusive_group(required=True)
    session_group.add_argument(
        "-s", "--session", metavar='SESSION_KEY',
        help='Provides the session key string of the cookie generated by logging in into the Advent of Code" official webpage')
    session_group.add_argument(
        "-S", "--session-file", metavar='FILE', type=argparse.FileType("r"),
        help='Select the file where the script can found the the session key string of the cookie generated by logging in into the Advent of Code" official webpage')


def __configure_input_parameters():
    parser = argparse.ArgumentParser(
        description='Assistant software to operate this project in a easier way')
    subparsers = parser.add_subparsers(dest="subcommand", required=True)
    # ----- generate -----
    parser_generate = subparsers.add_parser(
        'generate', help="Cleans the project and generates the project with CMake from scratch")
    __add_generation_input_arguments(parser_generate)
    # ----- compile -----
    parser_compile = subparsers.add_parser(
        'compile', help="Compiles the last CMake project which was generated")
    # ----- build -----
    parser_build = subparsers.add_parser(
        'build', help="Cleans, generates and compiles the project")
    __add_generation_input_arguments(parser_build)
    # ----- update -----
    parser_update = subparsers.add_parser(
        'update',
        help='Downloads the latest version in "master" branch for this project and updates all its dependencies')
    parser_update.add_argument("-f", "--force", action="store_true",
                               help="Deletes all the pending changes in the repo")
    # ----- clean -----
    parser_clean = subparsers.add_parser(
        'clean', help="Deletes all the local data stored in the project")
    # ----- add_day -----
    parser_addday = subparsers.add_parser(
        'add_day', help='Set up the project to add a new "Advent Of Code" puzzle')
    parser_addday.add_argument(
        "--year", type=apr.ranged_int(2015, 2099), required=True, metavar="[2015-2099]",
        help="Selects the year (format XXXX, as for instance, 2023) of the puzzle to generate")
    parser_addday.add_argument(
        "--day", type=apr.ranged_int(1, 25), required=True, metavar="[1-25]",
        help="Selects the day (from 1 to 25) of the puzzle to generate")
    parser_addday.add_argument(
        "-f", "--force", action="store_true", help="Forces the overwrite of existing files")
    __add_session_arguments(parser_addday)
    # ----- test -----
    parser_test = subparsers.add_parser(
        'test', help="Executes all the unit tests of the generated projects")
    # ----- get_input -----
    parser_getinput = subparsers.add_parser(
        'get_input',
        help='Downloads the input data for the "Advent Of Code" selected puzzle')
    parser_getinput.add_argument(
        "--year", type=apr.ranged_int(2015, 2099), required=True, metavar="[2015-2099]",
        help="Selects the year (format XXXX, as for instance, 2023) of the puzzle")
    parser_getinput.add_argument(
        "--day", type=apr.ranged_int(1, 25), required=True, metavar="[1-25]",
        help="Selects the day (from 1 to 25) of the puzzle")
    __add_session_arguments(parser_getinput)
    # ----- run -----
    parser_run = subparsers.add_parser(
        'run',
        help='Executes the solution of the selected puzzle')
    parser_run.add_argument(
        "--year", type=apr.ranged_int(2015, 2099), required=True, metavar="[2015-2099]",
        help="Selects the year (format XXXX, as for instance, 2023) of the puzzle")
    parser_run.add_argument(
        "--day", type=apr.ranged_int(1, 25), required=True, metavar="[1-25]",
        help="Selects the day (from 1 to 25) of the puzzle")
    # ----- get_statement -----
    parser_getstatement = subparsers.add_parser(
        'get_statement',
        help='Downloads the statement (both parts if available) for the "Advent Of Code" selected puzzle')
    parser_getstatement.add_argument(
        "--year", type=apr.ranged_int(2015, 2099), required=True, metavar="[2015-2099]",
        help="Selects the year (format XXXX, as for instance, 2023) of the puzzle")
    parser_getstatement.add_argument(
        "--day", type=apr.ranged_int(1, 25), required=True, metavar="[1-25]",
        help="Selects the day (from 1 to 25) of the puzzle")
    __add_session_arguments(parser_getstatement)

    return parser.parse_args()


def __manage_session_key(args) -> str:
    if args.session:
        return args.session.strip()
    else:
        session_file: typing.IO = args.session_file
        if not session_file:
            utils.print_error_msg(
                "Missing session key for accessing your profile in Advent of Code's webpage.")
            return ""
        with session_file:
            return session_file.read().strip()


def main() -> int:
    colorama.init(autoreset=True)

    __check_min_python_version()

    ret_code: int = 1
    args = __configure_input_parameters()
    root_path = __get_root_project_path()
    if args.subcommand == "build":
        ret_code = generate_project(root_path, PlatformType.from_str(args.platform), args.years, args.release,
                                    args.project, not args.no_ccache, not args.no_cppcheck)
        if ret_code == 0:
            ret_code = compile_project(root_path)
    elif args.subcommand == "update":
        ret_code = fetch_last_version(args.force)
    elif args.subcommand == "generate":
        ret_code = generate_project(root_path, PlatformType.from_str(args.platform), args.years, args.release,
                                    args.project, not args.no_ccache, not args.no_cppcheck)
    elif args.subcommand == "compile":
        ret_code = compile_project(root_path)
    elif args.subcommand == "clean":
        ret_code = clean_project(root_path)
    elif args.subcommand == "add_day":
        session: str = __manage_session_key(args)
        ret_code = add_new_day(root_path, args.year, args.day, args.force)
        if ret_code != 0:
            return ret_code
        ret_code = get_statement(root_path, args.year, args.day, session)
        if ret_code != 0:
            return ret_code
        ret_code = get_input(root_path, args.year, args.day, session)
    elif args.subcommand == "test":
        ret_code = test_project(root_path)
    elif args.subcommand == "get_input":
        session: str = __manage_session_key(args)
        ret_code = get_input(root_path, args.year, args.day, session)
    elif args.subcommand == "run":
        ret_code = run_project(root_path, args.year, args.day)
    elif args.subcommand == "get_statement":
        session: str = __manage_session_key(args)
        ret_code = get_statement(root_path, args.year, args.day, session)

    return ret_code


if __name__ == "__main__":
    exit_code: int = main()
    if exit_code == 0:
        print(colorama.Fore.GREEN + "Script finished successfully.")
    else:
        print(colorama.Fore.RED + "Script failed.")
    sys.exit(exit_code)
