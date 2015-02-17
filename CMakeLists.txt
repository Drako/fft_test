PROJECT ( fft_test )
CMAKE_MINIMUM_REQUIRED ( VERSION 2.8.11 )

IF ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
ENDIF ()

ADD_LIBRARY ( fft STATIC dft.cxx dft.hxx )
IF ( UNIX )
    TARGET_LINK_LIBRARIES ( fft m )
ENDIF ()

ADD_LIBRARY ( signalgen STATIC signals.cxx signals.hxx )
IF ( UNIX )
    TARGET_LINK_LIBRARIES ( signalgen m )
ENDIF ()

ADD_EXECUTABLE ( fft_test main.cxx )
TARGET_LINK_LIBRARIES ( fft_test fft signalgen )

