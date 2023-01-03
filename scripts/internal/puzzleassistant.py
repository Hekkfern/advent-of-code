import pathlib

import constants
import generate_templates


def __add_year(root_dir: pathlib.Path, year: int) -> None:
    puzzles_folder = pathlib.Path(root_dir / "puzzles")
    year_folder = puzzles_folder / str(year)
    year_folder.mkdir(parents=True, exist_ok=True)


def add_new_day(root_dir: pathlib.Path, year: int, day: int) -> None:
    assert year >= constants.MINIMAL_AOC_YEAR, f"year expected to be greater or equal than {constants.MINIMAL_AOC_YEAR}"
    assert day >= constants.MINIMAL_AOC_DAY, f"day expected to be greater or equal than {constants.MINIMAL_AOC_DAY}"
    assert day <= constants.MAXIMUM_AOC_DAY, f"day expected to be less or equal than {constants.MAXIMUM_AOC_DAY}"
