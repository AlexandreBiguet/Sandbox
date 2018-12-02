import subprocess as sub

def build(srcdir, builddir, releasedir):
    src_dir = '-H' + srcdir
    build_dir = '-B' + builddir
    rel_dir = '-DCMAKE_INSTALL_PREFIX=' + releasedir
    gen = 'Unix Makefiles'
    sub.run(['cmake', '-L', src_dir, build_dir, '-G', gen, rel_dir],
            check=True)

def packgen_lib():
    build('.', 'build/build_packgen', 'build/release')


def main():
    packgen_lib()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted by user')
