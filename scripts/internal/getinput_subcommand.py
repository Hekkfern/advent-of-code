import pathlib
import urllib.request

from . import utils
from .constants import RETURN_CODE_SUCCESS, RETURN_CODE_ERROR


def get_input(root_path: pathlib.Path, year: int, day: int,
              session: str) -> int:
    # Download data from server
    url: str = f"https://adventofcode.com/{year}/day/{day}/input"
    request = urllib.request.Request(
        url,
        headers={
            "Cookie": f"session={session}"
        })
    response = urllib.request.urlopen(request)
    if response.status != 200:
        utils.print_error_msg(
            'Error while trying to connect to the \"Advent of Code\" webpage. Check the input parameters of the script and make sure that the session key is valid.')
        return RETURN_CODE_ERROR
    # Check if the selected puzzle folder structure exists
    input_path = root_path / f"puzzles/{year}/{day}/sources/input.txt"
    if not input_path.is_file():
        utils.print_error_msg(
            'Missing folder structure for the selected puzzle. Use \"add_day\" subcommand first.')
        return RETURN_CODE_ERROR
    # Save into file
    with open(input_path, "wb") as f:
        f.write(response.read().strip())

    print(
        f'Input data for puzzle {year} day {day} has been stored in {input_path.absolute()}.')
    return RETURN_CODE_SUCCESS
