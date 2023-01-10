FROM archlinux:base

LABEL org.opencontainers.image.title="Advent of Code C++ dev environment"
LABEL org.opencontainers.image.description="Custom Docker image to solve Advent of Code puzzles in C++"

# Install necessary packages
RUN pacman -Syuq --noconfirm curl wget tar zip unzip sudo bash-completion \
  && pacman -Syuq --noconfirm gcc cmake git python python-pip ccache clang gdb cppcheck \
  && python3 -m pip install --upgrade pipenv

# Create "developer" user
ARG USERNAME=developer
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd -g ${USER_GID} ${USERNAME} \
  && useradd --create-home --no-log-init -u ${USER_UID} -g ${USER_GID} -G wheel ${USERNAME}

USER ${USERNAME}

WORKDIR /home/${USERNAME}
