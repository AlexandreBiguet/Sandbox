# Misc

- Open the Docker VM on Macos :

```
screen ~/Library/Containers/com.docker.docker/Data/com.docker.driver.amd64-linux/tty
```

- building ROS on macOS (part of) ([official](http://wiki.ros.org/kinetic/Installation/OSX/Homebrew/Source))

```
./src/catkin/bin/catkin_make_isolated --install -DCMAKE_BUILD_TYPE=Release \
      -DCATKIN_ENABLE_TESTING=Off \
      -DCMAKE_FIND_FRAMEWORK=LAST \
      -DCMAKE_CXX_STANDARD=11 \
      -DCMAKE_MACOSX_RPATH=ON  \
      -DCMAKE_INSTALL_RPATH=$(pwd)/install_isolated/lib
```
