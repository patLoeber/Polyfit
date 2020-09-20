cmake_minimum_required(VERSION 2.8)
project(
    "Polyfit-Boost-demo"
    LANGUAGES CXX
    VERSION 7.1.0)

set(exename "Polyfit-Boost-demo")

include(GNUInstallDirs)

# use our own library - installed 
find_package(Polyfit CONFIG REQUIRED)

# find boost
#Set(Boost_DEBUG ON)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    Set(Boost_COMPILER "-clang50") # doh!
endif()
if(NOT BOOST_ROOT)
  set(BOOST_ROOT $ENV{BOOST_ROOT} CACHE PATH "Boost Root Directory")
endif(NOT BOOST_ROOT)
set(Boost_NO_SYSTEM_PATHS ON)
if(USE_STATIC_BOOST)
    # static boost on windows add "lib" prefix
    # thus can coexist with dll version
    set(Boost_USE_STATIC_LIBS ON)
else()
    set(Boost_USE_STATIC_LIBS OFF)
    add_definitions("-DBOOST_ALL_DYN_LINK")
endif()
set(Boost_USE_MULTITHREADED ON)
# turn on __declspec(dllimport) modifiers
# Find boost in "module" mode, not CONFIG mode - not BoostConfig.cmake
find_package(Boost 1.74.0 EXACT REQUIRED COMPONENTS
    headers
    )

add_executable(${exename})
target_link_libraries(${exename} PUBLIC
    Polyfit::Polyfit
    Boost::headers
    )
target_sources(${exename} PRIVATE
    main.cpp
)

install(TARGETS ${exename}
    RUNTIME DESTINATION bin)
