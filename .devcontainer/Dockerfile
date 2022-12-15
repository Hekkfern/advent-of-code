FROM ubuntu:22.04

LABEL description="Custom image for Advent of Code puzzles"

RUN apt-get update && \
    apt-get -y install g++ cmake git python3 python3-pip ccache clang-format && \
    # Python reqs
    python3 -m pip install --upgrade pip

RUN echo "alias python='python3'" >> ~/.bashrc

WORKDIR ~/
