### CMakeLists.txt --- 
## 
## Filename: CMakeLists.txt
## Author: Alexandre BIGUET
## Created: Mer sep 13 21:08:00 2017 (+0200)
## Last-Updated: Mer sep 13 21:08:09 2017 (+0200)
##           By: Alexandre BIGUET
##     Update #: 3
## 
## snmpp
## 

set( UTILS_SOURCES
        "Utils/Tools.cpp"
        "Utils/Tools.hpp")
add_library( ${UTILS_OBJ} OBJECT ${UTILS_SOURCES} )

set( MATH_SOURCES
        "Math/Core/Quantity.hpp"
        "Math/Core/Variable.hpp"
        "Math/Core/Variables.hpp"
        "Math/Core/FuncBase.hpp" )
add_library( ${MATH_OBJ} OBJECT ${MATH_SOURCES} )

######################################################################
### CMakeLists.txt ends here
