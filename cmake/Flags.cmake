#
#  Flags.cmake
#  snmpp
#
#  Created by Alexandre Biguet on 13/10/2017 at 23:47.
#  Copyright © 2017 UAVIA. All rights reserved.
#

################################################################################
## This functions sets the compiler flags depending on the options given at
## configuration time.

function( SetCompilerFlags )

    if( NO_WARNINGS AND CLANG_WEVERYTHING )
        message(FATAL_ERROR "NO_WARNINGS and CLANG_EVERYTHING options cannot "
                "be true at the same time")
    endif()

    if( CLANG_WEVERYTHING )

        CHECK_CXX_COMPILER_FLAG(-Weverything COMPILER_SUPPORTS_EVERYTHING )

        if ( COMPILER_SUPPORTS_EVERYTHING )
            set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything" PARENT_SCOPE)
        endif()

    else()
        if ( NOT NO_WARNINGS )
            set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra" PARENT_SCOPE)
        endif()
    endif()

endfunction()

# Flags.cmake ends here