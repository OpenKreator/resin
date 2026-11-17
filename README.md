
# Resin

**Description**:  Resin is an open-source 3D texturing and painting application designed to eventually help creators achieve similar results to those produced by professional software like Adobe Substance 3D Painter.

**Status**:  Early development (Pre-alpha). Development is currently just focused on the applications foundation and making the graphical interface and rendering system.

## Installation

**Prerequisites**
- [Qt Online Installer](https://doc.qt.io/qt-6/qt-online-installation.html) (Qt 6.12.0 with the required Qt modules and a compatible MSCV kit)
- [Cmake](https://cmake.org/download/) (3.19 or newer)
- Visual Studio Build Tools - MSVC C++ build tools and Windows SDK.
- [Git](https://git-scm.com/) (Command line tool)
- [Ninja](https://github.com/ninja-build/ninja/releases) (if using the Ninja build system)

The following Qt modules are required
* Qt Core
* Qt Widgets
* Qt OpenGL
* Qt OpenGLWidgets

C++ standard: **C++ 17**

### Building with Qt Creator

1. Clone the Resin repository
   ```sh
   git clone https://github.com/OpenKreator/resin.git
   ```
2. Open **Qt Creator**.
3. Select **File** -> **Open File or Project**.
4. Navigate to the cloned repository and select `CMakeLists.txt`.
5. Select a configured Qt kit with a compatible MSVC compiler.
6. Once configuration is complete, build and run Resin using the **Run button**.

### Building with Cmake

1. Clone the Resin repository: (x64 native tools command prompt for vs 2022 recommended)
   ```sh
   git clone https://github.com/OpenKreator/resin.git
   cd resin
   ```
2. Configure the project using **Ninja**:
```sh
   cmake -S . -B build -G Ninja
   ```
3. If CMake cannot find your Qt installation automattically, specify its installation path:
```sh
   cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/Qt/6.12.0/msvc2022_64"
   ```
4. Build the application:
```sh
   cmake --build build
   ```
4. The generated executable will be located in the build directory depending on the selected build config.

<!-- ## Usage will be here when the application is usable-->

## Getting help

If you have questions, concerns, or encounter bugs while building or running Resin, please open an issue in the [GitHub Issue Tracker](https://github.com/OpenKreator/resin/issues).

When submitting an issue, please include:
* A description of the issue.
* Steps to reproduce the problem.
* Any relevant error messages or build output.
* Your operating system and development environment.

Please provide as much detail as possible to help identify and resolve the issue.

## Getting involved

Resin is an open source project in its early stages of development, and contributions, feedbeack, and suggestions are welcome.

<!-- Add [CONTRIBUTING](CONTRIBUTING.md)-->


## Open source licensing info

Resin is licensed under the **GNU General Public License v3.0 (GPL-3.0-only)**

You are free to use, study, modify, and redistribute Resin, including for commercial purposes, under the terms of the GPL-3.0 license.

See the [LICENSE](LICENSE.md) file for the full license text.

Third-party libraries included in the project retain their respective licenses.