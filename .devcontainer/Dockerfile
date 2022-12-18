FROM ubuntu:22.04

LABEL description="Custom image to solve Advent of Code puzzles in C++"

RUN apt-get update && \
    apt-get -y install g++ cmake git python3 python3-pip ccache clang-format clang-tidy && \
    # Python reqs
    python3 -m pip install --upgrade pip

RUN echo "alias python='python3'" >> ~/.bashrc

ARG UID=1000
ARG GID=1000

RUN groupadd -g "${GID}" developer \
  && useradd --create-home --no-log-init -u "${UID}" -g "${GID}" developer

USER developer

WORKDIR /home/developer
