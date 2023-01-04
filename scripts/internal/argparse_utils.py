import argparse


def ranged_int(lowest: int = -1, highest: int = 1):
    """Check a numeric is in expected range."""

    def type_func(value: str):
        int_value = int(value)
        if not (lowest <= int_value <= highest):
            raise argparse.ArgumentTypeError("Not in range.")
        return int_value

    return type_func
