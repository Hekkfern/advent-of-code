import pathlib
import urllib.request

from . import utils


def get_input(root_path: pathlib.Path, year: int, day: int, session: str) -> int:
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
        return 1
    # Check if the selected puzzle folder structure exists
    input_path = root_path / f"puzzles/{year}/{day}/sources/input.txt"
    if not input_path.is_file():
        utils.print_error_msg(
            'Missing folder structure for the selected puzzle. Use \"add_day\" subcommand first.')
        return 1
    # Save into file
    with open(input_path, "wb") as f:
        f.write(response.read().strip())

    print(
        f'Input data for puzzle {year} day {day} has been stored in {input_path.absolute()}.')
    return 0
