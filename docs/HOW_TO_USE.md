# How to use this project

- [How to use this project](#how-to-use-this-project)
  - [Requirements](#requirements)
  - [Basic actions](#basic-actions)
    - [Manually](#manually)
      - [Execute a puzzle solution](#execute-a-puzzle-solution)
      - [Run the unit tests of all the solutions](#run-the-unit-tests-of-all-the-solutions)
    - [Using `build.py` script](#using-buildpy-script)
      - [Execute a puzzle solution](#execute-a-puzzle-solution-1)
      - [Run the unit tests of all the solutions](#run-the-unit-tests-of-all-the-solutions-1)
  - [Advanced actions](#advanced-actions)
    - [How to add a new puzzle to the project](#how-to-add-a-new-puzzle-to-the-project)
  - [How to extract puzzle instructions and input data from the webpage](#how-to-extract-puzzle-instructions-and-input-data-from-the-webpage)

## Requirements

First, it is important that you prepare the necessary software in your machine in order to be able to use this project.

Read [SETUP_DEV_ENVIRONMENT.md](./SETUP_DEV_ENVIRONMENT.md) page to help you execute the preparation steps.

## Basic actions

### Manually

#### Execute a puzzle solution

```bash
cmake -S . --preset <preset>
cmake --build --preset <preset> -j
cd ./out/build/<preset>/puzzles/<year>/<day>/sources/ && ./aoc_<year>_<day>
```

where:
* <preset> is the name of the preset, according to the ones available in [CMakePresets.json](/CMakePresets.json) file.
* <year> is the year (format 20XX) of the puzzle.
* <day> is the day (from 1 to 25) of the puzzle.

#### Run the unit tests of all the solutions

```bash
cmake -S . --preset <preset>
cmake --build --preset <preset> -j
ctest --preset <preset> -j
```

where:
* <preset> is the name of the preset, according to the ones available in [CMakePresets.json](/CMakePresets.json) file.
* <year> is the year (format 20XX) of the puzzle.
* <day> is the day (from 1 to 25) of the puzzle.

### Using `build.py` script

#### Execute a puzzle solution

```bash
python3 -m pipenv install
python3 -m pipenv shell
python3 scripts/build.py build --platform <platform>
python3 scripts/build.py run --year <year> --day <day>
exit
```

where:
* <platform> is the platform where this script is being executed. The valid options are `windows`, `linux` and `macos`.
* <year> is the year (format 20XX) of the puzzle.
* <day> is the day (from 1 to 25) of the puzzle.

**Note:** For more information, read [*"build project" subcommand* in BUILDPY_SCRIPT.md](BUILDPY_SCRIPT.md#build-project-subcommands).

#### Run the unit tests of all the solutions

```bash
python3 -m pipenv install
python3 -m pipenv shell
python3 scripts/build.py build --platform <platform>
python3 scripts/build.py test
exit
```

where:
* <platform> is the platform where this script is being executed. The valid options are `windows`, `linux` and `macos`.
* <year> is the year (format 20XX) of the puzzle.
* <day> is the day (from 1 to 25) of the puzzle.

**Note:** For more information, read [*"build project" subcommand* in BUILDPY_SCRIPT.md](BUILDPY_SCRIPT.md#build-project-subcommands).

## Advanced actions

### How to add a new puzzle to the project

```bash
python3 -m pipenv install
python3 -m pipenv shell
python3 scripts/build.py add_day --year <year> --day <day>
```

where:
* <year> is the year (format 20XX) of the puzzle.
* <day> is the day (from 1 to 25) of the puzzle.

**Note:** For more information, read [*"Add new puzzle" subcommand* in BUILDPY_SCRIPT.md](BUILDPY_SCRIPT.md#add-new-puzzle-subcommand).

## How to extract puzzle instructions and input data from the webpage

```bash
python3 -m pipenv install
python3 -m pipenv shell
python3 scripts/build.py get_input --year <year> --day <day> --session <sessionkey>
python3 scripts/build.py get_statement --year <year> --day <day> --session <sessionkey>
```

where:
* <year> is the year (format 20XX) of the puzzle.
* <day> is the day (from 1 to 25) of the puzzle.
* <sessionkey> is a long string of character which is obtained from the web-browser after logging in into the *Advent of Code* webpage.

**Note:** For more information, read [*"Get puzzle input" subcommand* in BUILDPY_SCRIPT.md](BUILDPY_SCRIPT.md#get-puzzle-input-subcommand) and [*"Get puzzle statement" subcommand* in BUILDPY_SCRIPT.md](BUILDPY_SCRIPT.md#get-puzzle-statement-subcommand).
