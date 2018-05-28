#!/usr/bin/env python3
# coding: utf-8

# @Author: Alexandre Biguet <alexandrebiguet>
# @Date:   28 - May - 2018
# @Last modified by:   alexandrebiguet
# @Last modified time: 28 - May - 2018

import subprocess as sub
import argparse as arg
import os

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))

def main():
    parser = arg.ArgumentParser()
    parser.add_argument("--pack1", help="build and install pack1", action='store_true')
    parser.add_argument("--pack2", help="build and install pack2", action='store_true')
    args = parser.parse_args()

    if(args.pack1):
        print("Building and installing pack1")
        pack = "pack1"
        srcdir = "-H" + SCRIPT_DIR + "/" + pack
        bdir = SCRIPT_DIR + "/builds/build_" + pack
        buildir = "-B" + bdir
        reldir = "-DCMAKE_INSTALL_PREFIX=" + SCRIPT_DIR + "/builds/installation"
        sub.run(["cmake", srcdir, buildir, reldir], check=True)
        sub.run(["cmake", "--build", bdir], check=True)
        sub.run(["cmake", "--build", bdir, "--target", "install"], check=True)

    if(args.pack2):
        print("Building and installing pack2")
        pack = "pack2"
        srcdir = "-H" + SCRIPT_DIR + "/" + pack
        bdir = SCRIPT_DIR + "/builds/build_" + pack
        buildir = "-B" + bdir
        reldir = "-DCMAKE_INSTALL_PREFIX=" + SCRIPT_DIR + "/builds/installation"
        cpath = "-DCMAKE_PREFIX_PATH=" + SCRIPT_DIR + "/builds/installation/lib/cmake"
        sub.run(["cmake", srcdir, buildir, reldir, cpath], check=True)
        sub.run(["cmake", "--build", bdir], check=True)
        sub.run(["cmake", "--build", bdir, "--target", "install"], check=True)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("---> Aborted")
