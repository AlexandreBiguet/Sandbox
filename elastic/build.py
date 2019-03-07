#!/usr/bin/env python3
# coding: utf-8

import datetime
import docopt
import subprocess as sub
import os
import pathlib
import sys
import platform

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
DIRNAME = 'flex'
DEFAULT_GENERATOR = 'Unix Makefiles'

class BuildInfo:

    def __init__(self,
                 src_dir, build_dir, release_dir, generator, cmake_options):

        self._release_dir = str(pathlib.Path(release_dir))
        self._src_dir = str(pathlib.Path(src_dir))
        self._build_dir = str(pathlib.Path(build_dir))
        self._generator = generator
        self._cmake_options = cmake_options

    @property
    def src_dir(self):
        return self._src_dir

    @property
    def build_dir(self):
        return self._build_dir

    @property
    def release_dir(self):
        return self._release_dir

    @property
    def generator(self):
        return self._generator

    @property
    def cmake_options(self):
        return self._cmake_options


def build(build_info, execute_unit_test=False):
    src_dir = '-H' + build_info.src_dir
    build_dir = '-B' + build_info.build_dir
    rel_dir = '-DCMAKE_INSTALL_PREFIX=' + build_info.release_dir
    # gen = '"' + build_info.generator() + '" '
    gen = build_info.generator
    options = build_info.cmake_options
    if options:
        print('options : ', options)
        sub.run(['cmake', src_dir, build_dir, rel_dir, '-G', gen, '-LH'] +
                options, check=True)
    else:
        sub.run(['cmake', src_dir, build_dir, '-G', gen, rel_dir], check=True)
    sub.run(['cmake', '--build', build_info.build_dir, '--', '-j4'],
            check=True)

    if execute_unit_test:
        sub.run(['cmake', '--build', build_info.build_dir, '--target',
                'check'], check=True)

    sub.run(['cmake', '--build', build_info.build_dir,
            '--target', 'install'], check=True)


def get_base_build_name():
    plat_infos = platform.uname()
    base = 'build_' + plat_infos.machine + '-' + plat_infos.system
    if 'Darwin' in plat_infos.system:
        return base + plat_infos.release
    return base


def main():

    base_dir = get_base_build_name()
    build_dir = base_dir + '/' + 'build_' + DIRNAME
    release_dir = base_dir + '/' + 'release'
    gen = DEFAULT_GENERATOR

    build_info = BuildInfo(src_dir=SCRIPT_DIR + '/' + DIRNAME,
                           build_dir=build_dir,
                           release_dir=release_dir,
                           generator=gen,
                           cmake_options=None)
    build(build_info)

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("Interrupted by user")
