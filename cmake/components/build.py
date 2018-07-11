#!/usr/bin/env python3
# coding: utf-8

# @Author: Alexandre Biguet <alexandrebiguet>
# @Date:   11 - Jul - 2018
# @Last modified by:   alexandrebiguet
# @Last modified time: 11 - Jul - 2018

import sys
import os
import docopt
import subprocess as sub

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
BUILD_DIR = SCRIPT_DIR + '/build-cmake'
BUILD_DIR_A = BUILD_DIR + '/build-projA'
BUILD_DIR_B = BUILD_DIR + '/build-projB'
RELEASE_DIR = BUILD_DIR + '/release'
SRC_DIR_A = SCRIPT_DIR + '/projA'
SRC_DIR_B = SCRIPT_DIR + '/projB'

usage = """
build.py

Usage:
    build.py projA
    build.py projB
    build.py clean

Options:
  --help     Show this screen
  --version  Show version
"""

class BuildInfo:

    def __init__(self,
                 src_dir, build_dir, release_dir, generator, cmake_options):

        self._release_dir = release_dir
        self._src_dir = src_dir
        self._build_dir = build_dir
        self._generator = generator
        self._cmake_options = cmake_options

    def src_dir(self):
        return self._src_dir

    def build_dir(self):
        return self._build_dir

    def release_dir(self):
        return self._release_dir

    def generator(self):
        return self._generator

    def cmake_options(self):
        return self._cmake_options


def build(build_info):
    src_dir = '-H' + build_info.src_dir()
    build_dir = '-B' + build_info.build_dir()
    rel_dir = '-DCMAKE_INSTALL_PREFIX=' + build_info.release_dir()
    # gen = '"' + build_info.generator() + '" '
    gen = build_info.generator()
    options = build_info.cmake_options()
    if options:
        print('options : ', options)
        sub.run(['cmake', src_dir, build_dir, rel_dir, '-G', gen] + options,
                check=True)
    else:
        sub.run(['cmake', src_dir, build_dir, '-G', gen, rel_dir], check=True)
    sub.run(['cmake', '--build', build_info.build_dir()], check=True)
    sub.run(['cmake', '--build', build_info.build_dir(), '--target', 'install'],
            check=True)



def main():

    arglist = []
    cmake_options = []
    for arg in sys.argv[1:]:
        if arg.startswith('-D'):
            cmake_options.append(arg)
        else:
            arglist.append(arg)

    arguments = docopt.docopt(usage, argv=arglist, version='build.py 1.0')

    if arguments['projA']:
        info = BuildInfo(SRC_DIR_A, BUILD_DIR_A, RELEASE_DIR, 'Unix Makefiles',
                         cmake_options)
        build(info)

    if arguments['projB']:
        info = BuildInfo(SRC_DIR_B, BUILD_DIR_B, RELEASE_DIR, 'Unix Makefiles',
                         cmake_options)
        build(info)

    if arguments['clean']:
        sub.run(['rm', '-rf', BUILD_DIR])


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted by user')
