# CMakeList.txt: arquivo de projeto de CMake de nível superior, fazer configuração global
# e inclua subprojetos aqui.
#
cmake_minimum_required (VERSION 3.28)

# Habilite a Recarga Dinâmica para compiladores MSVC, se houver suporte.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(MesonLib LANGUAGES CXX VERSION 0.0.1)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(FETCHERS_LOCATION "Set Repo and File Fetcher location" ".")

function(set_msvc_debug_improvements TARGET_NAME)
    if(MSVC)
        target_compile_options(${TARGET_NAME} PRIVATE
            $<$<CONFIG:Debug>:/Od>
            $<$<CONFIG:Debug>:/Zi>
        )

        target_link_options(${TARGET_NAME} PRIVATE
            $<$<CONFIG:Debug>:/DEBUG>
        )
    endif()
endfunction()

include(FetchContent)

if(USES_VCPKG)
    set(VCPKG_CURRENT_PREFIX ${VCPKG_PREFIX_PATH}/${VCPKG_TARGET_TRIPLET})
    list(APPEND CMAKE_PREFIX_PATH ${VCPKG_CURRENT_PREFIX})
    set(VCPKG_ROOT_PREFIX ${VCPKG_CURRENT_PREFIX})
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(VCPKG_CURRENT_PREFIX ${VCPKG_CURRENT_PREFIX}/debug)
    endif()
    if(WIN32)
        set(ARTIFACT_PREFIX ${VCPKG_CURRENT_PREFIX})
    endif()
endif()

include(InstallRequiredSystemLibraries)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(MESONLIB_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(MESONLIB_VERSION_CONFIG "${MESONLIB_GENERATED_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(MESONLIB_PROJECT_CONFIG "${MESONLIB_GENERATED_DIR}/${PROJECT_NAME}Config.cmake")
set(MESONLIB_TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(MESONLIB_CONFIG_INSTALL_DIR "share/cmake/${PROJECT_NAME}")
set(MESONLIB_NAMESPACE "Mesonlib::")
set(MESONLIB_VERSION ${PROJECT_VERSION})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${MESONLIB_VERSION_CONFIG}" VERSION ${MESONLIB_VERSION} COMPATIBILITY SameMajorVersion
)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in" "${MESONLIB_PROJECT_CONFIG}" @ONLY)

# Install cmake config files
install(
  FILES "${MESONLIB_PROJECT_CONFIG}" "${MESONLIB_VERSION_CONFIG}"
  DESTINATION "${MESONLIB_CONFIG_INSTALL_DIR}")

install(
  EXPORT "${MESONLIB_TARGETS_EXPORT_NAME}"
  NAMESPACE "${MESONLIB_NAMESPACE}"
  DESTINATION "${MESONLIB_CONFIG_INSTALL_DIR}")

# Inclua subprojetos.
add_subdirectory("src")