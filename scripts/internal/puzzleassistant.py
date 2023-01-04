import pathlib

from . import constants
from . import generate_templates


def add_new_day(root_dir: pathlib.Path, year: int, day: int) -> None:
    assert year >= constants.MINIMAL_AOC_YEAR, f"year expected to be greater or equal than {constants.MINIMAL_AOC_YEAR}"
    assert day >= constants.MINIMAL_AOC_DAY, f"day expected to be greater or equal than {constants.MINIMAL_AOC_DAY}"
    assert day <= constants.MAXIMUM_AOC_DAY, f"day expected to be less or equal than {constants.MAXIMUM_AOC_DAY}"

    # puzzles folder
    puzzles_folder = pathlib.Path(root_dir / "puzzles")
    generate_templates.create_cmakelists_for_puzzles(root_dir)
    # year folder
    year_folder = puzzles_folder / str(year)
    year_folder.mkdir(parents=True, exist_ok=True)
    generate_templates.create_cmakelists_for_year(root_dir, year)
    # day folder
    day_folder = year_folder / str(day)
    day_folder.mkdir(parents=True, exist_ok=True)
    generate_templates.create_cmakelists_for_day(root_dir, year, day)
    generate_templates.create_readme_for_day(root_dir, year, day)
    # sources folder
    sources_folder = day_folder / "sources"
    sources_folder.mkdir(parents=True, exist_ok=True)
    generate_templates.create_cmakelists_for_sources(root_dir, year, day)
    generate_templates.create_inputtxt_for_sources(root_dir, year, day)
    generate_templates.create_solutionscpp_for_sources(root_dir, year, day)
    generate_templates.create_solutionshpp_for_sources(root_dir, year, day)
    generate_templates.create_maincpp_for_sources(root_dir, year, day)
    # tests folder
    tests_folder = day_folder / "tests"
    tests_folder.mkdir(parents=True, exist_ok=True)
    generate_templates.create_cmakelists_for_tests(root_dir, year, day)
    generate_templates.create_inputtxt_for_tests(root_dir, year, day)
    generate_templates.create_solutions_for_tests(root_dir, year, day)
    generate_templates.create_unittestscpp_for_tests(root_dir, year, day)
