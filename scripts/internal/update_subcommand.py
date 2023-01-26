import pathlib

import git

from . import utils
from .clean_subcommand import clean_project


def fetch_last_version(root_path: pathlib.Path, force: bool = False) -> int:
    clean_project(root_path)
    repo = git.Repo(root_path)
    if repo.is_dirty():
        if force:
            repo.git.reset(hard=True)
        else:
            utils.print_error_msg(
                "Pending changes to commit in the repository. Save them or discard them.")
            return 1
    repo.git.checkout("master")
    repo.remotes.origin.pull()
    print(f'Current commit is {repo.head.object.hexsha} in "master" branch')
    for submodule in repo.submodules:
        submodule.update(init=True)

    return 0
