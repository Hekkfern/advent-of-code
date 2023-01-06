#!/usr/bin/env python3

import argparse
import pathlib
import shutil
import subprocess
import sys
import typing

import colorama
import git

from internal import argparse_utils as apr
from internal import puzzleassistant as pzas
from internal.platform_type import PlatformType


def __abort_execution(msg: str) -> None:
    print(colorama.Fore.RED + msg)
    sys.exit(1)


def __get_root_project_path() -> pathlib.Path:
    return pathlib.Path(__file__).absolute().parents[1]


def __check_min_python_version() -> None:
    if sys.version_info[0] < 3 or sys.version_info[1] < 7:
        __abort_execution("This script requires Python version 3.7 or newer.")


def __fetch_last_version(force: bool = False) -> None:
    __clean_project()
    repo = git.Repo(__get_root_project_path())
    if repo.is_dirty():
        if force:
            repo.git.reset(hard=True)
        else:
            __abort_execution(
                "Pending changes to commit in the repository. Save them or discard them, and try again.")
    repo.git.checkout("master")
    repo.remotes.origin.pull()
    print(f'Current commit is {repo.head.object.hexsha} in "master" branch')
    for submodule in repo.submodules:
        submodule.update(init=True)


def __clean_project() -> None:
    root_path = __get_root_project_path()
    shutil.rmtree(root_path / ".idea", ignore_errors=True)
    shutil.rmtree(root_path / ".vs", ignore_errors=True)
    shutil.rmtree(root_path / ".vscode", ignore_errors=True)
    shutil.rmtree(root_path / "out", ignore_errors=True)


def __generate_project(platform: PlatformType, years: typing.List[int], release: bool = False,
                       unittests: bool = True) -> None:
    root_path = __get_root_project_path()
    # select preset
    preset: str = ""
    if platform == PlatformType.WINDOWS:
        if release:
            preset = "windows-x64-release"
        else:
            preset = "windows-x64-debug"
    elif platform == PlatformType.LINUX:
        if release:
            preset = "linux-x64-release"
        else:
            preset = "linux-x64-debug"
    elif platform == PlatformType.MACOS:
        if release:
            preset = "macos-x64-release"
        else:
            preset = "macos-x64-debug"
    else:
        raise ValueError
    # enable unit-tests
    ut_flag: str = '-DGENERATE_UNIT_TESTS:BOOL=' + ('ON' if unittests else 'OFF')
    # filter years
    years_flag: str = '-DGENERATE_YEARS="' + ';'.join(map(str, years)) + '"'
    # run CMake
    command: str = f'cmake -S {root_path} --preset {preset} {ut_flag} {years_flag}'
    with subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=root_path,
                          universal_newlines=True, encoding='utf-8', bufsize=1) as p:
        for line in p.stdout:
            print(line, end='')
    print()


def __build_project():
    # run CMake
    # subprocess.run(cmake --build out)
    pass


def __add_new_day(year: int, day: int, is_forced: bool) -> None:
    __clean_project()
    root_path = __get_root_project_path()
    day_path = root_path / f"puzzles/{year}/{day}/"
    if not day_path.is_dir() or is_forced:
        shutil.rmtree(day_path, ignore_errors=True)
        pzas.add_new_day(root_path, year, day)
        print(f"Added new files in \"{day_path.absolute()}\" folder.")
    else:
        print(f"Task skipped. Already-existing files in \"{day_path.absolute()}\" folder.")


def __get_input_parameters():
    parser = argparse.ArgumentParser(
        description='Assistant software to operate this project in a easier way')
    # parser.add_argument("--no-color", action="store_true",
    #                     help="Disables all the colors in the output messages.")
    subparsers = parser.add_subparsers(dest="subcommand", required=True)
    parser_build = subparsers.add_parser(
        'build', help="Cleans, generates and compiles the project.")
    parser_generate = subparsers.add_parser(
        'generate', help="Cleans the project and generates the project with CMake from scratch.")
    parser_generate.add_argument("-r", "--release", action="store_true",
                                 help="Sets the release flags into the compilation environment.")
    parser_generate.add_argument(
        "--platform", required=True, choices=["windows", "macos", "linux"],
        help="Selects the platform where you are executing this script.")
    parser_generate.add_argument(
        "--unit-tests", action="store_true", help="Generates the unit-test project too.")
    parser_generate.add_argument(
        "--filter", type=apr.ranged_int(2015, 2050), nargs='+',
        help="List of years whose puzzles will only be generated.")
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
        "--year", type=apr.ranged_int(2015, 2050), required=True,
        help="Selects the year (format XXXX, as for instance, 2023) of the puzzle to generate.")
    parser_addday.add_argument(
        "--day", type=apr.ranged_int(1, 25), required=True,
        help="Selects the day (from 1 to 25) of the puzzle to generate.")
    parser_addday.add_argument(
        "-f", "--force", action="store_true",
        help="Forces the overwrite of existing files.")

    return parser.parse_args()


def main():
    colorama.init(autoreset=True)

    __check_min_python_version()

    args = __get_input_parameters()
    if args.subcommand == "build":
        __clean_project()
        __generate_project(args.platform, args.release, args.unit_tests)
        __build_project()
    elif args.subcommand == "update":
        __fetch_last_version(args.force)
    elif args.subcommand == "generate":
        __clean_project()
        __generate_project(PlatformType.from_str(args.platform), args.filter, args.release, args.unit_tests)
    elif args.subcommand == "compile":
        __build_project()
    elif args.subcommand == "clean":
        __clean_project()
    elif args.subcommand == "add_day":
        __add_new_day(args.year, args.day, args.force)
    else:
        # Unreachable option
        sys.exit(1)


if __name__ == "__main__":
    main()
    print(colorama.Fore.GREEN + "Script finished successfully.")
    sys.exit(0)
