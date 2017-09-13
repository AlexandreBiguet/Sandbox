### CMakeLists.txt --- 
## 
## Filename: CMakeLists.txt
## Author: Alexandre BIGUET
## Created: Mer sep 13 21:08:20 2017 (+0200)
## Last-Updated: Mer sep 13 21:08:55 2017 (+0200)
##           By: Alexandre BIGUET
##     Update #: 6
## 
## snmpp
## 

file( GLOB SOURCES "*.cpp" )

add_library( ${FAKE_OBJ} OBJECT ${SOURCES} )
set_property( TARGET ${FAKE_OBJ} PROPERTY POSITION_INDEPENDENT_CODE 1 )


######################################################################
### CMakeLists.txt ends here
