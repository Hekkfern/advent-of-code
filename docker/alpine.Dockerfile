FROM alpine:3.17

LABEL org.opencontainers.image.title="Advent of Code C++ dev environment"
LABEL org.opencontainers.image.description="Custom Docker image to solve Advent of Code puzzles in C++"

# Install necessary packages
RUN apk update  \
    && apk add gcc cmake git python3 py3-pip ccache clang gdb cppcheck \
    && python3 -m pip install --upgrade pipenv

# Create "developer" user
ARG USERNAME=developer
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN addgroup -S -g ${USER_GID} ${USERNAME} \
    && adduser -S -D -u ${USER_UID} -G wheel ${USERNAME}

USER ${USERNAME}

WORKDIR /home/${USERNAME}
