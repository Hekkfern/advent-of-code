# Setup a development environment

- [Setup a development environment](#setup-a-development-environment)
  - [In a native operating system](#in-a-native-operating-system)
    - [Windows OS](#windows-os)
    - [Linux OS](#linux-os)
      - [Ubuntu 22.04](#ubuntu-2204)
      - [Fedora 37](#fedora-37)
    - [MacOs OS](#macos-os)
  - [Out-of-the-box Docker images](#out-of-the-box-docker-images)
  - [Visual Studio Code Dev Containers](#visual-studio-code-dev-containers)


## In a native operating system

### Windows OS

Install [Git](https://git-scm.com/download/win) for Windows.

Install [Python](https://www.python.org/downloads/). The minimum required version is 3.7, although the most recent versions work correctly too. When the Python installer is executed, be sure that the `pip` package is also installed.

Install cppcheck.

Install [Visual Studio 2022 (Community Edition)](https://visualstudio.microsoft.com/vs/). Make sure you install, at least, the **Desktop Development for C++** package. After the installation finishes, open **Visual Studio Installer** and update Visual Studio to its latest version.

### Linux OS

#### Ubuntu 22.04

Install the following system packages:

```bash
sudo apt-get install -y curl wget tar zip unzip make ninja-build g++ cmake git python3 python3-pip ccache clang-format clang-tidy gdb pkg-config cppcheck
```

Also, some Python packages are needed:

```bash
python3 -m pip install --upgrade pipenv
```

#### Fedora 37

Install the following system packages:

```bash
sudo dnf install -y curl wget tar zip unzip make ninja-build gcc-c++ cmake git python3 python3-pip ccache clang-tools-extra gdb cppcheck
```

Also, some Python packages are needed:

```bash
python3 -m pip install --upgrade pipenv
```

### MacOs OS

Install [Homebrew](https://brew.sh/) for MacOS, as described in [Install Homebrew](https://docs.brew.sh/Installation) on its official webpage.

Install some development tools:

```bash
brew install cmake python3 ccache clang-format llvm git cppcheck
```

Install the latest version of **XCodes** from the **App Store**.

## Out-of-the-box Docker images

In [docker](/docker/) folder, there are some Dockerfiles which can be used as isolated, reusable development environments for this project. The [README.md](/docker/README.md) in there explains the suggested console commands to use Docker with those Dockerfiles.

The available Linux flavours are:

* [Alpine Linux](https://www.alpinelinux.org/)
* [Arch Linux](https://archlinux.org/)
* [Fedora](https://getfedora.org/)
* [Ubuntu](https://ubuntu.com/)

They have all the dependencies installed so the project repository can be cloned in there and start using it.

## Visual Studio Code Dev Containers

The official documentation about Visual Studio Code *devcontainers* can be read in [here](https://code.visualstudio.com/docs/devcontainers/containers).
