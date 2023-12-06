# How the framework works

All the framework developed for this project is based on CMake variables which configure the project to behave differently according to the provided values.

The variables exposed by the project to modify the CMake configuration are:

* `GENERATE_PROJECTS`: selects which kind of projects to generate by CMake.
  * `ALL`: the unit tests projects are generated as well as the solution executables.
  * `EXES`: only the solution executables are generated.
  * `UNITTESTS`: only the unit tests projects are generated.
* `GENERATE_YEARS`: selects which *Advent of Code* year wants to generate or filter.
  * `""`: an empty string means that all the available puzzle solutions are generated.
  * `"2022"`: only the available puzzles of this year are generated.
  * `"2021;2022"`: only the available puzzles of both selected years are generated.
* `USE_CCACHE`: Use `ccache` program in the project if it is available.
  * `ON`: use `ccache` if it is available.
  * `OFF`: don't use `ccache` even if it is available.
* `USE_CPPCHECK`: Use `cppcheck` program in the project if it is available.
  * `ON`: use `cppcheck` if it is available.
  * `OFF`: don't use `cppcheck` even if it is available.

Also, some groups of variables are configured based on the selected CMake preset.

The available CMake presets and its characteristics are:

| Preset name           | Platform | Compiler | Generator      | Sanitizer           |
|-----------------------|----------|----------|----------------|---------------------|
| `windows-x64-debug`   | Windows  | -        | Ninja          | None                |
| `windows-x64-release` | Windows  | -        | Ninja          | None                |
| `windows-x64-asan`    | Windows  | -        | Ninja          | Address             |
| `linux-x64-debug`     | Linux    | GCC      | Unix Makefiles | None                |
| `linux-x64-release`   | Linux    | GCC      | Unix Makefiles | None                |
| `linux-x64-asan`      | Linux    | GCC      | Unix Makefiles | Address             |
| `linux-x64-tsan`      | Linux    | GCC      | Unix Makefiles | Thread              |
| `linux-x64-lsan`      | Linux    | GCC      | Unix Makefiles | Leak                |
| `linux-x64-ubsan`     | Linux    | GCC      | Unix Makefiles | Undefined Behaviour |
| `macos-x64-debug`     | macOS    | GCC      | Unix Makefiles | None                |
| `macos-x64-release`   | macOS    | GCC      | Unix Makefiles | None                |
| `macos-x64-asan`      | macOS    | GCC      | Unix Makefiles | Address             |
| `macos-x64-tsan`      | macOS    | GCC      | Unix Makefiles | Thread              |
| `macos-x64-lsan`      | macOS    | GCC      | Unix Makefiles | Leak                |
| `macos-x64-ubsan`     | macOS    | GCC      | Unix Makefiles | Undefined Behaviour |

Also, these presets can be extended with the options above. For example, `cmake -S . --preset windows-x64-debug -DUSE_CPPCHECK=OFF -DGENERATE_YEARS="2022"`.
