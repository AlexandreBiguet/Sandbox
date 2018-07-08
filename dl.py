#!/usr/bin/env python3

import argparse as arg
import os
import subprocess as sub


def dl_mnist(force=False):

    path = os.path.dirname(os.path.realpath(__file__)) + '/data/mnist'

    print('Downloading mnist data into : ', path)

    if not force:
        if os.path.exists(path):
            if os.listdir(path):
                print('The {} exists and is not empty. Abort'.format(path))
                return

    os.makedirs(path, exist_ok=True)

    if not os.path.exists(path + '/train-images-idx3-ubyte.gz'):
        sub.run(['wget', '-P', path,
                 'http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz'],
                check=True)
    
    if not os.path.exists(path + '/train-labels-idx1-ubyte.gz'):
        sub.run(['wget', '-P', path,
                 'http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz'],
                check=True)
    
    if not os.path.exists(path + '/t10k-images-idx3-ubyte.gz'):
        sub.run(['wget', '-P', path,
                 'http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz'],
                check=True)

    if not os.path.exists(path + '/t10k-labels-idx1-ubyte.gz'):
        sub.run(['wget', '-P', path,
                 'http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz'],
                check=True)


def main():
    parser = arg.ArgumentParser()

    parser.add_argument('--mnist',
                        help='download the mnist datasets into data directory',
                        action='store_true')

    parser.add_argument('--force',
                        help='Force downloading the datasets',
                        action='store_true')

    args = parser.parse_args()

    if args.mnist:
        dl_mnist(force=args.force)
    

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted')
