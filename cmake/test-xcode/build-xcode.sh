#!/bin/bash

set -e

script_dir=$(cd `dirname "${BASH_SOURCE[0]}"` && pwd)
name_prg_dir="project"
previous_dir=$PWD

printf "\n---- [ $name_prg_dir ] ---- \n"

script_dir=$(cd `dirname "${BASH_SOURCE[0]}"` && pwd)

BASE_DIR=$script_dir/build_Xcode
BUILD_DIR=$BASE_DIR/build_$name_prg_dir

base_dir=${BASE_DIR}
release_dir=$base_dir/release
build_dir=${BUILD_DIR}

if test -d $release_dir/include/$name_prg_dir; then
    rm -rf $release_dir/include/$name_prg_dir
fi

PKG_CONFIG_PATH="$release_dir/lib/pkgconfig:${PKG_CONFIG_PATH}"
export PKG_CONFIG_PATH

################################################################################
### Running cmake with all the arguments given to the script

printf "\n---- Running cmake ---- \n"

cmake -E make_directory $build_dir && cmake -E chdir $build_dir \
    cmake $script_dir/$name_prg_dir -G Xcode -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_INSTALL_PREFIX=$release_dir $*

printf "\n---- All right ---- \n"

#
# build-xcode.sh ends here
