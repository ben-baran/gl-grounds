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

wget 'http://downloads.sourceforge.net/project/ogl-math/glm-0.9.6.3/glm-0.9.6.3.zip' -O glm.zip
unzip glm.zip -d glm_tmp
rm glm.zip
mv glm_tmp/glm glm
rm -rf glm_tmp

wget 'http://downloads.sourceforge.net/project/assimp/assimp-3.1/assimp-3.1.1_no_test_models.zip' -O assimp.zip
unzip assimp.zip -d assimp_tmp
rm assimp.zip
mv assimp_tmp/* assimp
rm -rf assimp_tmp

# Make glew
cd glew/auto
make

#Move SOIL to make namespace clearer
cd ..
mv SOIL/src SOIL/SOIL