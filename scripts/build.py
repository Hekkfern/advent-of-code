#!/usr/bin/env python3

import argparse
import pathlib
import shutil
import sys
import typing

import colorama
import git

from internal import argparse_utils as apr
from internal import puzzleassistant as pzas
from internal.platform_type import PlatformType
from internal.utils import execute_program


def __abort_execution(msg: str) -> None:
    print(colorama.Fore.RED + msg)
    sys.exit(1)


def __get_root_project_path() -> pathlib.Path:
    return pathlib.Path(__file__).absolute().parents[1]


def __check_min_python_version() -> None:
    if sys.version_info[0] < 3 or sys.version_info[1] < 7:
        __abort_execution("This script requires Python version 3.7 or newer.")


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
            __abort_execution(
                "Pending changes to commit in the repository. Save them or discard them, and try again.")
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

    return 0


def __generate_project(platform: PlatformType, years: typing.List[int], release: bool,
                       unittests: bool, ccache: bool, cppcheck: bool) -> int:
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
    # delete folder if it already exists
    shutil.rmtree(root_path / f"out/build/" / preset, ignore_errors=True)
    # enable unit-tests
    ut_flag: str = '-DGENERATE_UNIT_TESTS:BOOL=' + ('ON' if unittests else 'OFF')
    # filter years
    years_flag: str = '-DGENERATE_YEARS="' + (';'.join(map(str, years)) if years else '') + '"'
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
        __abort_execution("Execution aborted. Please, generate the project first.")
    # check if the CMakeCache.txt file of the current preset exists
    out_preset_path = __get_root_project_path() / "out/build" / preset
    if not (out_preset_path / "CMakeCache.txt").is_file():
        __abort_execution("Output folder doesn't exist. Generate the project first.")
    # run CMake
    command: str = f'cmake --build --preset {preset}'
    cmd_code: int = execute_program(command)
    print()  # add empty line in stdout

    return cmd_code


def __test_project() -> int:
    # get current preset name
    preset = __read_current_preset()
    if preset is None:
        __abort_execution("Execution aborted. Please, generate the project first.")
    # run CTest
    command: str = f'ctest --preset {preset}'
    cmd_code: int = execute_program(command)
    print()  # add empty line in stdout

    if cmd_code != 0:
        print(colorama.Fore.RED + "One or more unit tests didn't pass.")

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
        print(f"Task skipped. Already-existing files in \"{day_path.absolute()}\" folder.")
        return 1


def __add_generation_input_arguments(parser):
    parser.add_argument("-r", "--release", action="store_true",
                        help="Sets the release flags into the compilation environment (default: %(default)s)")
    parser.add_argument(
        "--platform", required=True, choices=["windows", "macos", "linux"],
        help="Selects the platform where you are executing this script")
    parser.add_argument(
        "--no-unit-tests", action="store_true", help="Don't generate the unit-test projects")
    parser.add_argument(
        "--years", type=apr.ranged_int(2015, 2050), nargs='+',
        help="List of years whose puzzles will only be generated. (default: everything is generated)")
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
        "--year", type=apr.ranged_int(2015, 2050), required=True,
        help="Selects the year (format XXXX, as for instance, 2023) of the puzzle to generate")
    parser_addday.add_argument(
        "--day", type=apr.ranged_int(1, 25), required=True,
        help="Selects the day (from 1 to 25) of the puzzle to generate")
    parser_addday.add_argument(
        "-f", "--force", action="store_true",
        help="Forces the overwrite of existing files")
    # ----- test -----
    parser_test = subparsers.add_parser(
        'test', help="Executes all the unit tests of the generated projects.")

    return parser.parse_args()


def main() -> int:
    colorama.init(autoreset=True)

    __check_min_python_version()

    ret_code: int = 1
    args = __get_input_parameters()
    if args.subcommand == "build":
        __generate_project(PlatformType.from_str(args.platform), args.years, args.release, not args.no_unit_tests,
                           not args.no_ccache, not args.no_cppcheck)
        ret_code = __compile_project()
    elif args.subcommand == "update":
        ret_code = __fetch_last_version(args.force)
    elif args.subcommand == "generate":
        ret_code = __generate_project(PlatformType.from_str(args.platform), args.years, args.release,
                                      not args.no_unit_tests,
                                      not args.no_ccache, not args.no_cppcheck)
    elif args.subcommand == "compile":
        ret_code = __compile_project()
    elif args.subcommand == "clean":
        ret_code = __clean_project()
    elif args.subcommand == "add_day":
        ret_code = __add_new_day(args.year, args.day, args.force)
    elif args.subcommand == "test":
        ret_code = __test_project()

    return ret_code


if __name__ == "__main__":
    exit_code: int = main()
    if exit_code == 0:
        print(colorama.Fore.GREEN + "Script finished successfully.")
    else:
        print(colorama.Fore.RED + "Script failed.")
    sys.exit(exit_code)
