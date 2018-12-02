import subprocess as sub
import os

def build(srcdir, builddir, releasedir):
    src_dir = '-H' + srcdir
    build_dir = '-B' + builddir
    rel_dir = '-DCMAKE_INSTALL_PREFIX=' + releasedir
    gen = 'Unix Makefiles'
    current_env = os.environ.copy()
    current_env["CMAKE_PREFIX_PATH"] = releasedir + '/lib/cmake' + os.pathsep + current_env["CMAKE_PREFIX_PATH"]
    print(current_env["CMAKE_PREFIX_PATH"])
    sub.run(['cmake', '-L', src_dir, build_dir, '-G', gen, rel_dir],
            check=True, env=current_env)
    sub.run(['cmake', '--build', builddir, '--target', 'install'], check=True, env=current_env)

def packgen_lib():
    build('.', 'build/build_packgen', 'build/release')
    build('exec', 'build/build_exec', 'build/release')

def main():
    packgen_lib()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted by user')
