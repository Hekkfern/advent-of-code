import pathlib
import shutil
import typing

import jinja2

from . import constants
from . import utils


def __generate_file_from_template(root_dir: pathlib.Path, template_name: str, params: typing.Dict[str, any],
                                  file_path: pathlib.Path):
    # Get content template
    environment = jinja2.Environment(
        loader=jinja2.FileSystemLoader(root_dir / "templates/"))
    file_template = environment.get_template(template_name)
    # Generate the content of the file
    content = file_template.render(
        params
    )
    # Write the content into the file
    file_path.parent.mkdir(parents=True, exist_ok=True)
    with open(file_path, mode="w", encoding="utf-8") as file:
        file.write(content)


# ----------- puzzles -------------

def create_cmakelists_for_puzzles(root_dir: pathlib.Path) -> None:
    # Look for all the year folders
    year_list: typing.List[str] = []
    for path in (root_dir / "puzzles/").iterdir():
        if not path.is_dir():
            continue
        year = int(pathlib.PurePath(path).name)
        if year >= constants.MINIMAL_AOC_YEAR:
            year_list.append(str(year))
    year_list.sort()
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/CMakeLists.txt.j2", {"YEARS": year_list},
                                  root_dir / "puzzles/CMakeLists.txt")


# ----------- puzzles/year -------------

def create_cmakelists_for_year(root_dir: pathlib.Path, year: int) -> None:
    # Look for all the day folders
    day_list = []
    for path in (root_dir / f"puzzles/{year}").iterdir():
        if path.is_dir():
            try:
                day = int(pathlib.PurePath(path).name)
                if constants.MINIMAL_AOC_DAY <= day <= constants.MAXIMUM_AOC_DAY:
                    day_list.append(day)
            except:
                pass
    day_list.sort()
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/CMakeLists.txt.j2", {"DAYS": day_list},
                                  root_dir / f"puzzles/{year}/CMakeLists.txt")


# ----------- puzzles/year/day -------------

def create_cmakelists_for_day(root_dir: pathlib.Path, year: int, day: int) -> None:
    shutil.copyfile(root_dir / "templates/puzzles/year/day/CMakeLists.txt",
                    root_dir / f"puzzles/{year}/{day}/CMakeLists.txt")


def create_readme_for_day(root_dir: pathlib.Path, year: int, day: int, title: str = "TITLE OF THE PUZZLE",
                          content_part1: str = "", content_part2: str = "") -> None:
    # Check for empty values
    title = "TITLE OF THE PUZZLE" if not title else title
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/day/README.md.j2",
                                  {"DAY": day, "YEAR": year, "TITLE": title,
                                      "CONTENT_PART1": content_part1, "CONTENT_PART2": content_part2},
                                  root_dir / f"puzzles/{year}/{day}/README.md")


def create_explanation_for_day(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/day/EXPLANATION.md.j2", {
                                  "DAY": day, "YEAR": year}, root_dir / f"puzzles/{year}/{day}/README.md")


# ----------- puzzles/year/day/sources -------------

def create_cmakelists_for_sources(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/day/sources/CMakeLists.txt.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/sources/CMakeLists.txt")


def create_maincpp_for_sources(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/day/sources/main.cpp.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/sources/main.cpp")


def create_solutionscpp_for_sources(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/day/sources/solutions.cpp.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/sources/solutions.cpp")


def create_solutionshpp_for_sources(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/day/sources/solutions.hpp.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/sources/solutions.hpp")


def create_inputtxt_for_sources(root_dir: pathlib.Path, year: int, day: int) -> None:
    utils.create_empty_file(
        root_dir / f"puzzles/{year}/{day}/sources/input.txt")


# ----------- puzzles/year/day/tests -------------

def create_solutions_for_tests(root_dir: pathlib.Path, year: int, day: int) -> None:
    utils.create_empty_file(
        root_dir / f"puzzles/{year}/{day}/tests/solution1.txt")
    utils.create_empty_file(
        root_dir / f"puzzles/{year}/{day}/tests/solution2.txt")
    utils.create_empty_file(
        root_dir / f"puzzles/{year}/{day}/tests/solution1_test.txt")
    utils.create_empty_file(
        root_dir / f"puzzles/{year}/{day}/tests/solution2_test.txt")


def create_inputtxt_for_tests(root_dir: pathlib.Path, year: int, day: int) -> None:
    utils.create_empty_file(
        root_dir / f"puzzles/{year}/{day}/tests/input_test.txt")


def create_cmakelists_for_tests(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/day/tests/CMakeLists.txt.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/tests/CMakeLists.txt")


def create_unittestscpp_for_tests(root_dir: pathlib.Path, year: int, day: int) -> None:
    # Generate file
    __generate_file_from_template(root_dir, "puzzles/year/day/tests/unittests.cpp.j2", {"DAY": day, "YEAR": year},
                                  root_dir / f"puzzles/{year}/{day}/tests/unittests.cpp")
