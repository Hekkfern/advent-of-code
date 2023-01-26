import pathlib
import shutil


def clean_project(root_path: pathlib.Path) -> int:
    shutil.rmtree(root_path / ".idea", ignore_errors=True)
    shutil.rmtree(root_path / ".vs", ignore_errors=True)
    shutil.rmtree(root_path / ".vscode", ignore_errors=True)
    shutil.rmtree(root_path / "out", ignore_errors=True)
    shutil.rmtree(root_path / "Testing", ignore_errors=True)

    return 0
