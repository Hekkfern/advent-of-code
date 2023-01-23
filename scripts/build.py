#!/usr/bin/env python3

import argparse
import pathlib
import shutil
import sys
import typing
import urllib.error
import urllib.request

import colorama
import git

from internal import argparse_utils as apr
from internal import puzzleassistant as pzas
from internal.platform_type import PlatformType
from internal.utils import execute_program


def __print_error_msg(msg: str) -> None:
    print(colorama.Fore.RED + msg)


def __get_root_project_path() -> pathlib.Path:
    return pathlib.Path(__file__).absolute().parents[1]


def __check_min_python_version() -> bool:
    if sys.version_info[0] < 3 or sys.version_info[1] < 7:
        __print_error_msg("This script requires Python version 3.7 or newer.")
        return False
    return True


def __store_current_preset(preset: str) -> None:
    out_path = __get_root_project_path() / "out"
    with open(out_path / "current_preset.txt", mode="w", encoding="utf-8") as file:
        file.write(preset)


def __read_current_preset() -> typing.Optional[str]:
    out_path = __get_root_project_path() / "out"
    with open(out_path / "current_preset.txt", mode="r", encoding="utf-8") as file:
        preset: str = file.readline()
    return preset


def __fetch_last_version(force: bool = False) -> int:
    __clean_project()
    repo = git.Repo(__get_root_project_path())
    if repo.is_dirty():
        if force:
            repo.git.reset(hard=True)
        else:
            __print_error_msg(
                "Pending changes to commit in the repository. Save them or discard them.")
            return 1
    repo.git.checkout("master")
    repo.remotes.origin.pull()
    print(f'Current commit is {repo.head.object.hexsha} in "master" branch')
    for submodule in repo.submodules:
        submodule.update(init=True)

    return 0


def __clean_project() -> int:
    root_path = __get_root_project_path()
    shutil.rmtree(root_path / ".idea", ignore_errors=True)
    shutil.rmtree(root_path / ".vs", ignore_errors=True)
    shutil.rmtree(root_path / ".vscode", ignore_errors=True)
    shutil.rmtree(root_path / "out", ignore_errors=True)
    shutil.rmtree(root_path / "Testing", ignore_errors=True)

    return 0


def __generate_project(platform: PlatformType, years: typing.List[int], release: bool,
                       project: str, ccache: bool, cppcheck: bool) -> int:
    root_path = __get_root_project_path()
    # select preset
    preset: str = ""
    if platform == PlatformType.WINDOWS:
        preset = "windows-x64-" + ("release" if preset else "debug")
    elif platform == PlatformType.LINUX:
        preset = "linux-x64-" + ("release" if preset else "debug")
    elif platform == PlatformType.MACOS:
        preset = "macos-x64-" + ("release" if preset else "debug")
    else:
        raise ValueError
    # delete folder if it already exists
    shutil.rmtree(root_path / f"out/build/" / preset, ignore_errors=True)
    # enable unit-tests
    ut_flag: str = f'-DGENERATE_PROJECTS:STRING={project.upper()}'
    # filter years
    years_flag: str = '-DGENERATE_YEARS="' + \
                      (';'.join(map(str, years)) if years else '') + '"'
    # enable ccache
    ccache_flag: str = '-DUSE_CCACHE:BOOL=' + ('ON' if ccache else 'OFF')
    # enable cppcheck
    cppcheck_flag: str = '-DUSE_CPPCHECK:BOOL=' + ('ON' if cppcheck else 'OFF')
    # run CMake
    command: str = f'cmake -S {root_path} --preset {preset} {ut_flag} {ccache_flag} {cppcheck_flag} {years_flag}'
    cmd_code: int = execute_program(command)
    print()  # add empty line in stdout
    # store generated preset
    __store_current_preset(preset)

    return cmd_code


def __compile_project() -> int:
    # get current preset name
    preset = __read_current_preset()
    if preset is None:
        __print_error_msg(
            "Execution aborted. Please, generate the project first.")
        return 1
    # check if the CMakeCache.txt file of the current preset exists
    out_preset_path = __get_root_project_path() / "out/build" / preset
    if not (out_preset_path / "CMakeCache.txt").is_file():
        __print_error_msg(
            "Output folder doesn't exist. Generate the project first.")
        return 1
    # run CMake
    command: str = f'cmake --build --preset {preset} -j'
    cmd_code: int = execute_program(command)
    print()  # add empty line in stdout

    return cmd_code


def __test_project() -> int:
    # get current preset name
    preset = __read_current_preset()
    if preset is None:
        __print_error_msg(
            "Project has not been generated. Use \"generate\" subcommand first.")
        return 1
    # run CTest
    command: str = f'ctest --preset {preset} -j'
    cmd_code: int = execute_program(command)
    print()  # add empty line in stdout

    if cmd_code != 0:
        __print_error_msg("One or more unit tests didn't pass.")

    return cmd_code


def __run_project(year: int, day: int) -> int:
    # get current preset name
    preset = __read_current_preset()
    if preset is None:
        __print_error_msg(
            "Project has not been generated. Use \"generate\" subcommand first.")
        return 1
    # check if exe exists
    exe_path = __get_root_project_path() / f"out/build/{preset}/puzzles/{year}/{day}/sources/aoc_{year}_{day}"
    if not exe_path.is_file():
        __print_error_msg(
            "Project has not been either generated or compiled. Use \"build\" subcommand first.")
        return 1
    # run exe
    cmd_code: int = execute_program(str(exe_path.absolute()), exe_path.parent)
    print()  # add empty line in stdout

    return cmd_code


def __add_new_day(year: int, day: int, is_forced: bool) -> int:
    __clean_project()
    root_path = __get_root_project_path()
    day_path = root_path / f"puzzles/{year}/{day}/"
    if not day_path.is_dir() or is_forced:
        shutil.rmtree(day_path, ignore_errors=True)
        pzas.add_new_day(root_path, year, day)
        print(f"Added new files in \"{day_path.absolute()}\" folder.")
        return 0
    else:
        __print_error_msg(
            f'Task skipped. Already-existing files in \"{day_path.absolute()}\" folder. Use \"--force\" option to overwrite the existing files.')
        return 1


def __get_input(year: int, day: int, session: str) -> int:
    # Download data from server
    url: str = f"https://adventofcode.com/{year}/day/{day}/input"
    request = urllib.request.Request(
        url,
        headers={
            "Cookie": f"session={session}"
        })
    response = urllib.request.urlopen(request)
    if response.status != 200:
        __print_error_msg(
            'Error while trying to connect to the \"Advent of Code\" webpage. Check the input parameters of the script and make sure that the session key is valid.')
        return 1
    # Check if the selected puzzle folder structure exists
    input_path = __get_root_project_path() / f"puzzles/{year}/{day}/sources/input.txt"
    if not input_path.is_file():
        __print_error_msg(
            'Missing folder structure for the selected puzzle. Use \"add_day\" subcommand first.')
        return 1
    # Save into file
    with open(input_path, "wb") as f:
        f.write(response.read())
    print(
        f'Input data for puzzle {year} day {day} has been stored in {input_path.absolute()}.')
    return 0


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


def __get_input_parameters():
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
    session_group = parser_getinput.add_mutually_exclusive_group(required=True)
    session_group.add_argument(
        "-s", "--session", metavar='SESSION_KEY',
        help='Provides the session key string of the cookie generated by logging in into the Advent of Code" official webpage')
    session_group.add_argument(
        "-S", "--session-file", metavar='FILE', type=argparse.FileType("r"),
        help='Select the file where the script can found the the session key string of the cookie generated by logging in into the Advent of Code" official webpage')
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

    return parser.parse_args()


def main() -> int:
    colorama.init(autoreset=True)

    __check_min_python_version()

    ret_code: int = 1
    args = __get_input_parameters()
    if args.subcommand == "build":
        ret_code = __generate_project(PlatformType.from_str(args.platform), args.years, args.release, args.project,
                                      not args.no_ccache, not args.no_cppcheck)
        if ret_code == 0:
            ret_code = __compile_project()
    elif args.subcommand == "update":
        ret_code = __fetch_last_version(args.force)
    elif args.subcommand == "generate":
        ret_code = __generate_project(PlatformType.from_str(args.platform), args.years, args.release,
                                      args.project,
                                      not args.no_ccache, not args.no_cppcheck)
    elif args.subcommand == "compile":
        ret_code = __compile_project()
    elif args.subcommand == "clean":
        ret_code = __clean_project()
    elif args.subcommand == "add_day":
        ret_code = __add_new_day(args.year, args.day, args.force)
    elif args.subcommand == "test":
        ret_code = __test_project()
    elif args.subcommand == "get_input":
        if args.session:
            session: str = args.session.strip()
        else:
            session_file: typing.IO = args.session_file
            if not session_file:
                __print_error_msg(
                    "Missing session key for accessing your profile in Advent of Code's webpage.")
                return 1
            with session_file:
                session: str = session_file.read().strip()
        ret_code = __get_input(args.year, args.day, session)
    elif args.subcommand == "run":
        ret_code = __run_project(args.year, args.day)

    return ret_code


if __name__ == "__main__":
    exit_code: int = main()
    if exit_code == 0:
        print(colorama.Fore.GREEN + "Script finished successfully.")
    else:
        print(colorama.Fore.RED + "Script failed.")
    sys.exit(exit_code)
