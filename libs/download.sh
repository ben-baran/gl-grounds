#!/usr/bin/env bash

# Downloads dependencies for this project

# Delete any previous versions
rm -rf glew
rm -rf glfw
rm -rf glm
rm -rf SOIL
rm -rf assimp

# Get any new versions
git clone https://github.com/nigels-com/glew.git glew
git clone https://github.com/glfw/glfw.git glfw
git clone https://github.com/epatel/SOIL.git SOIL
git clone https://github.com/g-truc/glm.git glm
git clone https://github.com/assimp/assimp.git assimp