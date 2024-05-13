import pathlib
import shutil
import typing

from . import utils
from .platform_type import PlatformType
from .constants import RETURN_CODE_SUCCESS, RETURN_CODE_ERROR


def __store_current_preset(root_path: pathlib.Path, preset: str) -> None:
    out_path = root_path / "out"
    with open(out_path / "current_preset.txt", mode="w", encoding="utf-8") as file:
        file.write(preset)


def __read_current_preset(root_path: pathlib.Path) -> typing.Optional[str]:
    out_path = root_path / "out"
    with open(out_path / "current_preset.txt", mode="r", encoding="utf-8") as file:
        preset: str = file.readline()
    return preset


def generate_project(root_path: pathlib.Path, platform: PlatformType, years: typing.List[int], release: bool,
                     project: str, ccache: bool, cppcheck: bool) -> int:
    # select preset
    if platform == PlatformType.WINDOWS:
        preset = "windows-x64-" + ("release" if release else "debug")
    elif platform == PlatformType.LINUX:
        preset = "linux-x64-" + ("release" if release else "debug")
    elif platform == PlatformType.MACOS:
        preset = "macos-x64-" + ("release" if release else "debug")
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
    cmd_code: int = utils.execute_program(command)
    print()  # add empty line in stdout
    # store generated preset
    __store_current_preset(root_path, preset)

    return cmd_code


def compile_project(root_path: pathlib.Path) -> int:
    # get current preset name
    preset = __read_current_preset(root_path)
    if preset is None:
        utils.print_error_msg(
            "Execution aborted. Please, generate the project first.")
        return RETURN_CODE_ERROR
    # check if the CMakeCache.txt file of the current preset exists
    out_preset_path = root_path / "out/build" / preset
    if not (out_preset_path / "CMakeCache.txt").is_file():
        utils.print_error_msg(
            "Output folder doesn't exist. Generate the project first.")
        return RETURN_CODE_ERROR
    # run CMake
    command: str = f'cmake --build --preset {preset} -j'
    cmd_code: int = utils.execute_program(command)
    print()  # add empty line in stdout

    return cmd_code


def test_project(root_path: pathlib.Path) -> int:
    # get current preset name
    preset = __read_current_preset(root_path)
    if preset is None:
        utils.print_error_msg(
            "Project has not been generated. Use \"generate\" subcommand first.")
        return RETURN_CODE_ERROR
    # run CTest
    command: str = f'ctest --preset {preset} -j'
    cmd_code: int = utils.execute_program(command)
    print()  # add empty line in stdout

    if cmd_code != RETURN_CODE_SUCCESS:
        utils.print_error_msg("One or more unit tests didn't pass.")

    return cmd_code


def run_project(root_path: pathlib.Path, year: int, day: int) -> int:
    # get current preset name
    preset = __read_current_preset(root_path)
    if preset is None:
        utils.print_error_msg(
            "Project has not been generated. Use \"generate\" subcommand first.")
        return RETURN_CODE_ERROR
    # check if exe exists
    exe_path = root_path / \
        f"out/build/{preset}/puzzles/{year}/{day}/sources/aoc_{year}_{day}"
    if not exe_path.is_file():
        utils.print_error_msg(
            "Project has not been either generated or compiled. Use \"build\" subcommand first.")
        return RETURN_CODE_ERROR
    # run exe
    cmd_code: int = utils.execute_program(
        str(exe_path.absolute()), exe_path.parent)
    print()  # add empty line in stdout

    return cmd_code
