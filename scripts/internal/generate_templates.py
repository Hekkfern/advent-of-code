import shutil
import typing
import pathlib

import jinja2

import constants
import utils


def __generate_file_from_template(root_dir: pathlib.Path, template_name: str, params: typing.Dict[str, any],
                                  file_path: pathlib.Path):
    # Get content template
    environment = jinja2.Environment(loader=jinja2.FileSystemLoader(root_dir / "templates/"))
    file_template = environment.get_template(template_name)
    # Generate the content of the file
    content = file_template.render(
        params
    )
    # Write the content into the file
    with open(file_path, mode="w", encoding="utf-8") as file:
        file.write(content)


# ----------- puzzles -------------

def __create_cmakelists_for_puzzles(root_dir: pathlib.Path) -> None:
    # Look for all the year folders
    year_list: typing.List[str] = []
    for path in (root_dir / "puzzles/").iterdir():
        year = int(pathlib.PurePath(path).name)
        if path.is_dir() and year >= constants.MINIMAL_AOC_YEAR:
            year_list.append(str(year))
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/CMakeLists.txt.j2", {"YEARS": year_list},
                                  root_dir / "puzzles/CMakeLists.txt")


# ----------- puzzles/year -------------

def __create_cmakelists_for_year(root_dir: pathlib.Path, year: int) -> None:
    # Look for all the day folders
    day_list = []
    for path in (root_dir / f"puzzles/{year}").iterdir():
        day = int(pathlib.PurePath(path).name)
        if path.is_dir() and constants.MINIMAL_AOC_DAY <= day <= constants.MAXIMUM_AOC_DAY:
            day_list.append(year)
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/CMakeLists.txt.j2", {"DAYS": day_list},
                                  root_dir / f"puzzles/{year}/CMakeLists.txt")


# ----------- puzzles/year/day -------------

def __create_cmakelists_for_day(root_dir: pathlib.Path, year: int, day: int) -> None:
    shutil.copyfile(root_dir / "templates/year/day/CMakeLists.txt",
                    root_dir / f"puzzles/{year}/{day}/CMakeLists.txt")


def __create_readme_for_day(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/day/README.md.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/README.md")


# ----------- puzzles/year/day/sources -------------

def __create_cmakelists_for_sources(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/sources/CMakeLists.txt.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/sources/CMakeLists.txt")


def __create_maincpp_for_sources(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/sources/main.cpp.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/sources/main.cpp")


def __create_solutionscpp_for_sources(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/sources/solutions.cpp.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/sources/solutions.cpp")


def __create_solutionshpp_for_sources(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/sources/solutions.hpp.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/sources/solutions.hpp")


def __create_inputtxt_for_sources(root_dir: pathlib.Path, year: int, day: int) -> None:
    utils.create_empty_file(
        root_dir / f"puzzles/{year}/{day}/sources/input.txt")


# ----------- puzzles/year/day/tests -------------

def __create_solutions_for_sources(root_dir: pathlib.Path, year: int, day: int) -> None:
    utils.create_empty_file(
        root_dir / f"puzzles/{year}/{day}/tests/solution1.txt")
    utils.create_empty_file(
        root_dir / f"puzzles/{year}/{day}/tests/solution2.txt")
    utils.create_empty_file(
        root_dir / f"puzzles/{year}/{day}/tests/solution_test.txt")


def __create_inputtxt_for_tests(root_dir: pathlib.Path, year: int, day: int) -> None:
    utils.create_empty_file(root_dir / f"puzzles/{year}/{day}/tests/input_test.txt")


def __create_cmakelists_for_tests(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/tests/CMakeLists.txt.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/tests/CMakeLists.txt")


def __create_unittestscpp_for_tests(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/tests/unittests.cpp.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/tests/unittests.cpp")
