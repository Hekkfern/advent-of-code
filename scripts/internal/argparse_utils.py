import argparse


def ranged_int(lowest: int = -1, highest: int = 1):
    """Check whether a number is in expected range."""

    def type_func(value: str):
        int_value = int(value)
        if not (lowest <= int_value <= highest):
            raise argparse.ArgumentTypeError("Not in range.")
        return int_value

    return type_func


def aoc_year():
    """Check if a number can be a valid AoC year."""

    def type_func(value: str):
        int_value = int(value)
        if int_value < 2015:
            raise argparse.ArgumentTypeError("Not a valid year.")
        return int_value

    return type_func
