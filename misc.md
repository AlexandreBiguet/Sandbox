# Misc

- Open the Docker VM on Macos :

```
screen ~/Library/Containers/com.docker.docker/Data/com.docker.driver.amd64-linux/tty
```

## Building ROS-melodic on macOS from source

- building ROS on macOS (part of) ([official](http://wiki.ros.org/kinetic/Installation/OSX/Homebrew/Source))

```
brew tap ros/deps
brew tap osrf/simulation   # Gazebo, sdformat, and ogre
brew tap homebrew/core # VTK5
```

```
pip install wxPython wstool rosdep rosinstall rosinstall_generator rospkg \
 catkin-pkg sphinx empy
```

```
sudo rosdep init
```

```
rosdep update
```

```
brew install qt pyqt opencv@3 pcl gazebo9 poco
```

```
./src/catkin/bin/catkin_make_isolated --install -DCMAKE_BUILD_TYPE=Release \
      -DCATKIN_ENABLE_TESTING=OFF \
      -DCMAKE_FIND_FRAMEWORK=LAST \
      -DCMAKE_CXX_STANDARD=11 \
      -DCMAKE_MACOSX_RPATH=ON  \
      -DCMAKE_INSTALL_RPATH=$(pwd)/install_isolated/lib
```
