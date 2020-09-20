cmake_minimum_required(VERSION 3.12)
# https://dominikberner.ch/cmake-interface-lib/

project(
    "Polyfit"
    LANGUAGES CXX
    VERSION 7.1.0
    DESCRIPTION "C++ implementation of polyfit, with optional weighting like in numpy.  Two implementations, one with boost/ublas lib, and one with the Eigen lib."
    HOMEPAGE_URL "https://github.com/dand-oss/Polyfit")

set(libname "Polyfit")

add_library(${libname} INTERFACE)
# add alias so the project can be uses with add_subdirectory
add_library(${libname}::${libname} ALIAS ${libname})

include(GNUInstallDirs)

target_include_directories(
  ${libname}
  INTERFACE $<BUILD_INTERFACE:${${libname}_SOURCE_DIR}/lib>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(${libname} INTERFACE cxx_std_11)

install(TARGETS ${libname}
        EXPORT ${libname}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${libname}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${libname}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${libname}Config.cmake"
  INSTALL_DESTINATION
  ${CMAKE_INSTALL_DATAROOTDIR}/${libname}/cmake)

install(EXPORT ${libname}_Targets
    FILE ${libname}Targets.cmake
    NAMESPACE ${libname}::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${libname}/cmake)

install(FILES "${PROJECT_BINARY_DIR}/${libname}Config.cmake"
    "${PROJECT_BINARY_DIR}/${libname}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${libname}/cmake)

install(FILES
    ${PROJECT_SOURCE_DIR}/PolyfitBoost.hpp
    ${PROJECT_SOURCE_DIR}/PolyfitEigen.hpp
    DESTINATION include)

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")

include(CPack)

# build the demos
#add_subdirectory(demo-boost)
#add_subdirectory(demo-eigen)
