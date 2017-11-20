#
#  Flags.cmake
#  snmpp
#
#  Created by Alexandre Biguet on 13/10/2017 at 23:47.
#

################################################################################
## This functions sets the compiler flags depending on the options given at
## configuration time.

macro( SetCompilerFlags )

    if( NO_WARNINGS AND CLANG_WEVERYTHING )
        message(FATAL_ERROR "NO_WARNINGS and CLANG_EVERYTHING options cannot "
                "be true at the same time")
    endif()

    if( CLANG_WEVERYTHING )

        CHECK_CXX_COMPILER_FLAG(-Weverything COMPILER_SUPPORTS_EVERYTHING )

        if ( COMPILER_SUPPORTS_EVERYTHING )
            set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything" )
        endif()

    else()

        if ( NOT NO_WARNINGS )

            CHECK_CXX_COMPILER_FLAG( -W COMPILER_SUPPORTS_W )
            CHECK_CXX_COMPILER_FLAG( -Wall COMPILER_SUPPORTS_WALL )
            CHECK_CXX_COMPILER_FLAG( -Wextra COMPILER_SUPPORTS_WEXTRA )

            if( COMPILER_SUPPORTS_W  )
                set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W")
            endif()

            if( COMPILER_SUPPORTS_WALL )
                set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
            endif()

            if( COMPILER_SUPPORTS_WEXTRA )
                set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra" )
            endif()

        endif()

    endif()

endmacro()

# Flags.cmake ends here
