#!/usr/bin/env python3
# coding: utf-8


### build.py ---
##
## Filename: build.py
## Author: Alexandre BIGUET
## Created: Mer sep 13 21:16:33 2017 (+0200)
## Last-Updated: Mer sep 13 21:59:45 2017 (+0200)
##           By: Alexandre BIGUET
##     Update #: 38
##
## snmpp
##

import subprocess as Sub
import argparse as Arg
import sys, os
from glob import glob
try:
    from termcolor import colored
except ImportError:
    print(" ** You must install termcolor module as specified in the readme")
    print(" ** For exemple using pip for python3: ")
    print(" ** $ pip3 install termcolor")
    quit()

### The minimum version of python must be 3.5
if sys.version_info.major < 3 and sys.version_info.minor < 5 :
    print(" ** Python 3.5 (at least) is required for this script")
    quit()

pwd_full = os.path.dirname(os.path.realpath(__file__))
unobj = os.uname()
default_base_dir = pwd_full + "/Build-cmake"
default_build_dir = default_base_dir + "/build_" + unobj.machine +"-"+unobj.sysname + unobj.release
default_release_dir = default_base_dir + "/release"

def do_install(bdir,rdir):

    if (not os.path.isdir(bdir)):
        os.makedirs (bdir )

    os.chdir(bdir)
    Sub.run(["cmake", pwd_full, "-DCMAKE_INSTALL_PREFIX="+rdir])
    nproc = int (Sub.check_output(["getconf", "_NPROCESSORS_ONLN"]) )
    Sub.run(["make", "-j"+str(nproc), "install"])


parser = Arg.ArgumentParser()

parser.add_argument("--build-dir", metavar="<path>", type=str, nargs='?',
                    default=default_build_dir,
                    help="The path to the build directory. Default is Build-cmake/build/")

parser.add_argument("--release-dir", metavar="<path>", type=str, nargs='?',
                    default=default_release_dir,
                    help="The path to the release dir, i.e. where you want to "
                    "install the library. Default is Build-cmake/release/")

parser.add_argument("--clean",  action='store_true',
                    help="remove build and install directory. Default is"
                    " Build-cmake/build and Build-cmake/release")


args = parser.parse_args()

print(args)

if (args.clean ) :
    if (os.path.exists(default_base_dir) ):
        print(" {} directory exists".format(default_base_dir))
        Sub.run(["rm", "-rf", default_base_dir ])
    else:
        print(" Build-cmake/ directory does not exist: Nothing to clean ")
    quit()

do_install (args.build_dir, args.release_dir )

######################################################################
### build.py ends here
