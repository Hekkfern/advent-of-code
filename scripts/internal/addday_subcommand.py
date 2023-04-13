import pathlib
import shutil

from . import constants
from . import generate_templates
from . import utils


def __create_files_from_templates(root_dir: pathlib.Path, year: int, day: int) -> None:
    assert year >= constants.MINIMAL_AOC_YEAR, f"year expected to be greater or equal than {constants.MINIMAL_AOC_YEAR}"
    assert day >= constants.MINIMAL_AOC_DAY, f"day expected to be greater or equal than {constants.MINIMAL_AOC_DAY}"
    assert day <= constants.MAXIMUM_AOC_DAY, f"day expected to be less or equal than {constants.MAXIMUM_AOC_DAY}"

    # sources folder
    generate_templates.create_cmakelists_for_sources(root_dir, year, day)
    generate_templates.create_inputtxt_for_sources(root_dir, year, day)
    generate_templates.create_solutionscpp_for_sources(root_dir, year, day)
    generate_templates.create_solutionshpp_for_sources(root_dir, year, day)
    generate_templates.create_maincpp_for_sources(root_dir, year, day)
    # tests folder
    generate_templates.create_cmakelists_for_tests(root_dir, year, day)
    generate_templates.create_inputtxt_for_tests(root_dir, year, day)
    generate_templates.create_solutions_for_tests(root_dir, year, day)
    generate_templates.create_unittestscpp_for_tests(root_dir, year, day)
    # day folder
    generate_templates.create_cmakelists_for_day(root_dir, year, day)
    generate_templates.create_readme_for_day(root_dir, year, day)
    generate_templates.create_explanation_for_day(root_dir, year, day)
    # year folder
    generate_templates.create_cmakelists_for_year(root_dir, year)
    # puzzles folder
    generate_templates.create_cmakelists_for_puzzles(root_dir)


def add_new_day(root_path: pathlib.Path, year: int, day: int, is_forced: bool) -> int:
    day_path = root_path / f"puzzles/{year}/{day}/"
    if not day_path.is_dir() or is_forced:
        shutil.rmtree(day_path, ignore_errors=True)
        __create_files_from_templates(root_path, year, day)
        print(f"Added new files in \"{day_path.absolute()}\" folder.")
        return 0
    else:
        utils.print_error_msg(
            f'Task skipped. Already-existing files in \"{day_path.absolute()}\" folder. Use \"--force\" option to overwrite the existing files.')
        return 1
