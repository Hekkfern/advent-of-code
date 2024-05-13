import pathlib
import re
import typing
import urllib.request

import bs4
import markdownify as md

from . import generate_templates as gtp
from . import utils
from .constants import RETURN_CODE_SUCCESS, RETURN_CODE_ERROR


def __parse_title(raw_statement: bs4.element.Tag) -> str:
    st = raw_statement
    raw_title: str = str(st.find("h2").contents[0])
    title: str = ""
    pattern = re.compile(r"^--- Day \d{1,2}: ([\w\ -_]*) ---$")
    result = pattern.search(raw_title)
    if len(result.groups()) > 0:
        title = result.group(1)
    return title


def __parse_statement(raw_statement: bs4.element.Tag) -> str:
    st = raw_statement
    st.find("h2").replaceWith('')  # delete h2
    return md.MarkdownConverter().convert_soup(st).strip()


def get_statement(root_path: pathlib.Path, year: int, day: int,
                  session: str) -> int:
    # Download data from server
    url: str = f"https://adventofcode.com/{year}/day/{day}"
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
    readme_path = root_path / f"puzzles/{year}/{day}/README.md"
    if not readme_path.is_file():
        utils.print_error_msg(
            'Missing folder structure for the selected puzzle. Use \"add_day\" subcommand first.')
        return RETURN_CODE_ERROR
    # Get webscrapper instance
    soup = bs4.BeautifulSoup(response.read(), 'html.parser')
    # Get parts
    contents: typing.List[str] = []
    article_tags = soup.find_all('article', 'day-desc')
    title = __parse_title(article_tags[0])
    contents.append(__parse_statement(article_tags[0]))
    if len(article_tags) > 1:
        contents.append(__parse_statement(article_tags[1]))
    else:
        contents.append("")

    # write file
    gtp.create_readme_for_day(root_path, year, day,
                              title, contents[0], contents[1])

    print(
        f'Puzzle instructions for puzzle {year} day {day} has been stored in {readme_path.absolute()}.')
    return RETURN_CODE_SUCCESS
