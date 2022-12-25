FROM ubuntu:22.04

LABEL org.opencontainers.image.title="Advent of Code C++ dev environment"
LABEL org.opencontainers.image.description="Custom Docker image to solve Advent of Code puzzles in C++"
LABEL org.opencontainers.image.authors="hector.fernandez.carmona@gmail.com"

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install necessary packages
RUN apt-get update \
  && apt-get -y install curl wget tar zip unzip sudo bash-completion \
  && apt-get -y install build_essentials g++ cmake git python3 python3-pip ccache clang-format clang-tidy gdb pkg-config valgrind systemd-coredump \
  && python3 -m pip install --upgrade pip

RUN echo "alias python='python3'" >> ~/.bashrc

# Install vcpkg
RUN wget -O vcpkg.tar.gz https://github.com/microsoft/vcpkg/archive/master.tar.gz \
  && mkdir /opt/vcpkg \
  && tar xf vcpkg.tar.gz --strip-components=1 -C /opt/vcpkg \
  && /opt/vcpkg/bootstrap-vcpkg.sh \
  && ln -s /opt/vcpkg/vcpkg /usr/local/bin/vcpkg \
  && rm -f vcpkg.tar.gz

# Create "developer" user
ARG USERNAME=developer
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd -g ${USER_GID} ${USERNAME} \
  && useradd --create-home --no-log-init -u ${USER_UID} -g ${USER_GID} -G sudo ${USERNAME}

USER ${USERNAME}

WORKDIR /home/${USERNAME}
