#!/usr/bin/env bash

# Downloads dependencies for this project

# Delete any previous versions
rm -r glew
rm -r glfw
rm -r glm
rm -r SOIL

# Get any new versions
git clone https://github.com/nigels-com/glew.git glew
git clone https://github.com/glfw/glfw glfw
git clone https://github.com/epatel/SOIL SOIL

wget 'http://sourceforge.net/projects/ogl-math/?source=typ_redirect' -O glm.zip
unzip glm.zip -d glm
rm glm.zip