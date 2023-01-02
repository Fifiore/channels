# Channels

## Content

- [Introduction](#introduction)
- [Requirements](#requirements)
- [How to build](#how-to-build)
- [How to launch unit tests](#how-to-launch-unit-tests)

## Introduction

Channels examples for future developments

## Requirements

- Conan >= 1.39 and < 2.0
- CMake 3.5.1 or later

## How to build

Create a subfolder in your project folder to generate build files:
```
cd <project_folder>
mkdir build
cd build
```

Retrieve depencencies with conan:
```
conan install .. --build=missing -s build_type=Release
```

Generate the project with cmake (Command for Visual Studio 2022):
```
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
```

Build:
```
cmake --build . --config Release
```

## How to launch unit tests

Execute channels_test




