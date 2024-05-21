# Base image: https://hub.docker.com/_/microsoft-vscode-devcontainers
FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-20.04

# Avoid warnings by switching to noninteractive
ENV DEBIAN_FRONTEND=noninteractive

# Configure apt and install packages
RUN apt-get update

# Install C++ tools
RUN apt-get -y install build-essential cmake cppcheck valgrind gdb clang-format clang-tidy clang-tools clang libclang-dev

# Install ALSA, MESA and X11
RUN apt-get -y install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev

# Install MinGW
RUN apt-get -y install mingw-w64

#export directories as environment variables
ENV WORKSPACE_PATH=/workspaces/tower_defense
ENV TASKS_PATH=$WORKSPACE_PATH/tools/tasks
ENV CMAKE_SCRIPTS_PATH=$WORKSPACE_PATH/tools/cmake

#export toolchain files as environment variables
ENV MINGW_WINDOWS_TOOLCHAIN_PATH=$CMAKE_SCRIPTS_PATH/toolchains/mingw-w64-x86_64.cmake
ENV GCC_LINUX_TOOLCHAIN_PATH=$CMAKE_SCRIPTS_PATH/toolchains/gcc-x86_64-linux.cmake