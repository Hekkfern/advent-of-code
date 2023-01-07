FROM ubuntu:22.04

LABEL org.opencontainers.image.title="Advent of Code C++ dev environment"
LABEL org.opencontainers.image.description="Custom Docker image to solve Advent of Code puzzles in C++"

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install necessary packages
RUN apt-get update \
  && apt-get install -y curl wget tar zip unzip sudo bash-completion \
  && apt-get install -y build-essential g++ cmake git python3 python3-pip ccache clang-format clang-tidy gdb pkg-config cppcheck \
  && python3 -m pip install --upgrade pipenv

# Create "developer" user
ARG USERNAME=developer
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd -g ${USER_GID} ${USERNAME} \
  && useradd --create-home --no-log-init -u ${USER_UID} -g ${USER_GID} -G sudo ${USERNAME}

USER ${USERNAME}

WORKDIR /home/${USERNAME}
