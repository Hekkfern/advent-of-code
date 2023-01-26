# Frequently Asked Questions

1. Why does it use `vcpkg` for managing external libraries?

This project requires getting external libraries to solve the puzzles: why re-invent the wheel if somebody else did?
CMake provides a method called `FetchContent` ([official documentation](https://cmake.org/cmake/help/latest/module/FetchContent.html)) which helps to download and use other CMake projects stored in remote version control servers.
On the other hand, there are some open-source projects whose goal is managing C++ dependencies more easily, as for instance, `vcpkg` ([link](https://vcpkg.io/en/index.html)) or `conan` ([link](https://conan.io/)).

`vcpkg` tool has been chosen as the C++ dependency manager of this project because of the high support in forums, easiness-to-use and the active community.

I would like to share an extract from CMake forums ([link](https://discourse.cmake.org/t/fetchcontent-vs-vcpkg-conan/6578/3)) where Craig Scott explains both options (`FetchContent` vs `vcpkg`/`conan`) in detail.

> Third party package managers like vcpkg, conan, etc. are dedicated to providing dependencies. They typically have “recipes” for how to provide each dependency and they effectively allow a project to say “give me this” and leave it up to the package manager to take care of the details of how that’s done. That’s a gross over-simplification, but it’s close enough for the purpose of discussion here. Package managers are generally well-suited to publicly available dependencies, but some do support private dependencies as well. Users are typically responsible for making the package manager available on their system in some way.
<br>
FetchContent provides a way for a project to say “give me this, and if not provided by other means, use this method to get it”. With CMake 3.23 and earlier, it was more like “give me this and use this method to get it”, but CMake 3.24 added support for integration with  `find_package()`  and dependency providers, so it now gives you the ability to try a package manager first, and if that doesn’t supply it, fall back to the download-and-build-from-source details.
<br>
CMake itself doesn’t get involved in defining “recipes” for dependencies for either method. For package managers, the package managers provide the “how”. For FetchContent, the project provides the “how” (with CMake 3.24 or later, it’s more like the “how, if nothing else provides it”).
<br>
FetchContent is often a good fit within organisations where they want to bring together multiple internal projects under active development into one build. Developers don’t have to install an extra tool and it has direct support for working across multiple repositories at once. With FetchContent, a dependency is only added to the build if something asks for it, which means you can use CMake cache variables to turn features on and off, and the build will not ask for a dependency that isn’t used.
<br>
Package managers take an additional step to set up, which some people don’t like, but others don’t mind. They usually require you to adapt your workflow in some way to accommodate how they expect the build to be done. These adjustments can range from quite minor to rather disruptive. Package managers can be a good fit for bringing in mature dependencies, especially popular ones that many projects use. The maintainers of these tools often put in a lot of work to fix and patch dependencies to make them more reliable to use, which can save you a lot of work (if they get it right!). People often underestimate the value these tools provide by curating and managing how the dependencies are built. A common weakness of package managers is that they usually want you to define your dependencies up front, so you can end up pulling in dependencies you may not actually need.
<br>
My general advice would be to use FetchContent for internal dependencies if they are being actively developed. If package managers don’t present any major issues for your situation, prefer to use those to provide public dependencies. If you are inside an organisation and you have some internal projects that are relatively mature, consider whether a package manager might still be appropriate for making those available to others within the company. New features available from CMake 3.24 should help with transitioning projects from FetchContent-provided to package manager-provided once a project matures, should that be desired.

2. Why is this project so focused on being compatible in multiple platforms?

*Advent of Code* solutions that can be found in public repositories into the Internet have the minimal implementation in order to be able to be compiled and run in the owner's machine. So, it is very common that those projects cannot run in your computer. Or they use specific features of the operating system, IDEs or compiler versions.

So, in order to get rid of all those problems, it has been decided that this project must work correctly in, at least, the most important operating systems and compilers.

It is expected that not all the platforms and compilers can be supported (because it would require a huge amount of work). So, if you consider that support for a specific platform should be provided, you can create a new PR and contribute to the project.

3. Which development environment should I use?

Low-experienced developers are recommended using *Visual Studio Code DevContainers* (read [*Visual Studio Code Dev Containers* section in SETUP_DEV_ENVIRONMENT.md](./SETUP_DEV_ENVIRONMENT.md#visual-studio-code-dev-containers)) because it provides a ready-to-use environment (based on Docker) which is guaranteed to work, and it also provides the IDE and tools to work on the project very easily.

Advanced developers are recommended using this project in the native operating systems of their computers (read [*In a native operating system* section in SETUP_DEV_ENVIRONMENT.md](./SETUP_DEV_ENVIRONMENT.md#in-a-native-operating-system)), as it guarantees the maximum performance and versatility.

4. Why aren't the puzzles parsing the whole input file first?

To generate the optimal solution to every puzzle, this project considers that parsing the input file should be considered part of the challenge too. So, all the benchmarks generated by the solutions include the time spent in parsing the input data.

Additionally, the goal of the solution implementations is to have a complexity (*Big O Notation*) of `O(n)`, i.e. the code only loops once in the input data.

Having a low complexity indicator is a good indicator that the performance of the implemented code is good, because it means that the code is not wasting CPU time looping around the same data again and again.

5. Why does the project force unit testing on every puzzle?

This project is concern on its quality assurance, so the code can evolve and be modified safely without caring about breaking the code base.

Also, the unit tests for each of the parts of every puzzle help the developers to validate their code solution against the examples provided in the *Advent of Code* webpage.

Another advantage of the usage of unit tests is that other developers can contribute to this project by suggesting better, easier and faster implementations to any of the puzzles, assuring that their contributions are compliant with the expected result.

6. Why does it use `CMake` instead of other build systems?

It has been decided to use `CMake` build system because a lot of IDEs have compatibility with it, as well as other tools. Also, it is one of the most common build systems, so finding documentation, books and support in forums is easier.

7. Why does it use `range-v3` library instead of C++20 STL `<ranges>`?

Due to how C++ standards are release, it is quite usual that some features are left out of the standard due to lack of time.

Some algorithms and features were not added to the C++20 standard (for instance, `std::accumulate()` with ranges instead of iterators). Also, some compilers haven't implemented some of these methods of the C++ standard yet; or they are still in a experimental phase.

For the reasons above, it has been decided to use `range-v3` library, which assures compatibility with all the platforms as well as implements some cutting-edge features not included in the C++ standard.

As C++20 STL `ranges` standard was based on the work done in the `range-v3` library, both solutions are very similar, so in the future, this project could be easily migrated in order to use the STL methods instead.
