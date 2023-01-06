<a name="readme-top"></a>

<!-- PROJECT SHIELDS -->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Hekkfern/advent-of-code">
    <img src="docs/images/logo.png" alt="Logo" width="300" height="300">
  </a>

<h3 align="center">Advent Of Code C++ Challenge</h3>

  <p align="center">
    <i>Advent Of Code</i> solutions made in C++ language
    <br />
    <a href="https://github.com/Hekkfern/advent-of-code/discussions">Discuss</a>
    ·
    <a href="https://github.com/Hekkfern/advent-of-code/issues">Report Bug</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

## About The Project

This project has been created with the main goal to provide a easy-to-use development platform to solve [Advent of code](https://adventofcode.com/) puzzles in C++.



Features:

* C++ 20 standard
* `CMake`-based project: feel free to split your logic into several files and classes as you wish.
* Quality tools: `clang-tidy`, sanitizers, compiler warnings, ...
* `vcpkg` already integrated: import and use any C++ library very easily from
  the [vcpkg catalog](https://vcpkg.io/en/packages.html).
* Unit-testing with `Catch2` library: create unit tests to validate the example inputs, or to validate that your future changes don't break your code.
* Multi-platform: designed to be usable in Windows, Linux and MacOs.
* Dockerization: if you don't want to pollute your computer with all the required development tools, there is a Docker
  image available to start developing in a matter of seconds.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

Tested on:

| Platform | OS | Characteristics |
|---|---|---|
| Windows | Windows 10 | cmake X.X.X and MSVC v143 |
| Linux | Ubuntu 22.04 | cmake X.X.X and GCC X.X.X |
| Linux | Manjaro 22 | cmake X.X.X and GCC X.X.X |
| Apple | macOS Monterey 12.6.1  (Intel processor) | cmake 3.25.1 and AppleClang 13.1.6.13160021 |

<!-- GETTING STARTED -->

## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

First read this section to install the necessary tools in your computer to be able to use this project.

#### Windows OS

Install [Git](https://git-scm.com/download/win) for Windows.

Install [Python](https://www.python.org/downloads/). The minimum required version is 3.7, although the most recent versions work correctly too. When the Python installer is executed, be sure that the `pip` package is also installed.

Install [Visual Studio 2022 (Community Edition)](https://visualstudio.microsoft.com/vs/). Make sure you install, at least, the **Desktop Development for C++** package. After the installation finishes, open **Visual Studio Installer** and update Visual Studio to its latest version.

#### Linux OS (Ubuntu 22.04)

Install the following packages:

```bash
sudo apt-get -y install build-essential g++ cmake git python3 python3-pip ccache clang-format clang-tidy gdb pkg-config
```

#### MacOs OS

Install [Homebrew](https://brew.sh/) for MacOS, as described in [Install Homebrew](https://docs.brew.sh/Installation) on its official webpage.

Install some development tools:

```bash
brew install cmake python3 ccache clang-format llvm git
```

Install the latest version of **XCodes** from the **App Store**.

### Installation

Clone the repo and all its submodules:

```bash
git clone --recursive https://github.com/Hekkfern/advent-of-code.git
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE INSTRUCTIONS -->

## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos
work well in this space. You may also link to more resources.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTRIBUTING -->

## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any
contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also
simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->

## License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->

## Contact

If you want to suggest anything or discuss some ideas about this project, feel free to open a topic
in [Discussions](https://github.com/Hekkfern/advent-of-code/discussions)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- MARKDOWN LINKS & IMAGES -->

[contributors-shield]: https://img.shields.io/github/contributors/Hekkfern/advent-of-code.svg?style=for-the-badge
[contributors-url]: https://github.com/Hekkfern/advent-of-code/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Hekkfern/advent-of-code.svg?style=for-the-badge
[forks-url]: https://github.com/Hekkfern/advent-of-code/network/members
[stars-shield]: https://img.shields.io/github/stars/Hekkfern/advent-of-code.svg?style=for-the-badge
[stars-url]: https://github.com/Hekkfern/advent-of-code/stargazers
[issues-shield]: https://img.shields.io/github/issues/Hekkfern/advent-of-code.svg?style=for-the-badge
[issues-url]: https://github.com/Hekkfern/advent-of-code/issues
[license-shield]: https://img.shields.io/github/license/Hekkfern/advent-of-code.svg?style=for-the-badge
[license-url]: https://github.com/Hekkfern/advent-of-code/blob/master/LICENSE.txt
