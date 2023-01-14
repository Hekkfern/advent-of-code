# Setup a development environment

- [Prerequisites](#prerequisites)
    - [Windows platform](#windows-platform)
    - [Linux platform](#linux-platform)
    - [MacOs platform](#macos-platform)

## Windows OS

Install [Git](https://git-scm.com/download/win) for Windows.

Install [Python](https://www.python.org/downloads/). The minimum required version is 3.7, although installing one of the most recent versions is strongly suggested.

Install **Visual Studio 2022 Community Edition** from the its official [webpage](https://visualstudio.microsoft.com/vs/community/). Make sure you install, at least, the **Desktop Development for C++** package.

Open **Visual Studio Installer** and update **Visual Studio** to its latest version.

## Linux OS (Ubuntu)

Install some packages:

```bash
sudo apt install -y git cmake make g++ ccache clang-format clang-tidy python3 python3-pip
```

## MacOs OS

Install [Homebrew](https://brew.sh/) for macOS, as described in [Install Homebrew](https://docs.brew.sh/Installation) on its official webpage.

Install some development tools:

```bash
brew install cmake python3 cppcheck ccache clang-format llvm git
```

Install the latest version of **XCodes** software from the **App Store**.
