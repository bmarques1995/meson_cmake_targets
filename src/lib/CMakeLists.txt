set(TARGET_NAME "mesonlib")
set(TARGET_NAME2 "mesonlog")
set(TARGET_NAME3 "mesonmod")

macro(reset_build_dir TARGET_NAME)

    set(OUTPUT_PREFIX_DIR ${PROJECT_BINARY_DIR})

    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_PREFIX_DIR}/bin")
    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_PREFIX_DIR}/bin")
    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_PREFIX_DIR}/bin")
    set_target_properties(${TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_PREFIX_DIR}/lib")
    set_target_properties(${TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_PREFIX_DIR}/lib")
    set_target_properties(${TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_PREFIX_DIR}/lib")
    set_target_properties(${TARGET_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_PREFIX_DIR}/lib")
    set_target_properties(${TARGET_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_PREFIX_DIR}/lib")
    set_target_properties(${TARGET_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_PREFIX_DIR}/lib")

endmacro()

file(GLOB_RECURSE MESON_LIB_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "code/*.hh")
file(GLOB_RECURSE MESON_LIB_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "code/*.cc")

add_library(${TARGET_NAME} ${MESON_LIB_SRCS} ${MESON_LIB_HDRS})

#target_link_libraries(${TARGET_NAME} PUBLIC)

target_include_directories(${TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/code>
												 $<INSTALL_INTERFACE:include/mesonlib/code>)

set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 20)

set(OUTPUT_PREFIX_DIR ${PROJECT_BINARY_DIR})

reset_build_dir(${TARGET_NAME})

target_compile_definitions(${TARGET_NAME} PRIVATE MESON_LIB_EXPORTS)

if(WIN32)
    target_compile_definitions(${TARGET_NAME} PUBLIC MESON_LIB_WINDOWS)
else()
    target_compile_definitions(${TARGET_NAME} PUBLIC MESON_LIB_UNIX)
endif()

if(BUILD_SHARED_LIBS)
    target_compile_definitions(${TARGET_NAME} PUBLIC MESON_LIB_SHARED)
endif()

file(GLOB_RECURSE MESON_LOG_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "code2/*.hh")
file(GLOB_RECURSE MESON_LOG_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "code2/*.cc")

add_library(${TARGET_NAME2} ${MESON_LOG_SRCS} ${MESON_LOG_HDRS})

#target_link_libraries(${TARGET_NAME} PUBLIC)

target_include_directories(${TARGET_NAME2} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/code2>
												 $<INSTALL_INTERFACE:include/mesonlib/code2>)

target_link_libraries(${TARGET_NAME2} PUBLIC ${TARGET_NAME})

set_target_properties(${TARGET_NAME2} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${TARGET_NAME2} PROPERTIES CXX_STANDARD 20)

reset_build_dir(${TARGET_NAME2})

target_compile_definitions(${TARGET_NAME2} PRIVATE MESON_LOG_EXPORTS)

if(WIN32)
    target_compile_definitions(${TARGET_NAME2} PUBLIC MESON_LOG_WINDOWS)
else()
    target_compile_definitions(${TARGET_NAME2} PUBLIC MESON_LOG_UNIX)
endif()

if(BUILD_SHARED_LIBS)
    target_compile_definitions(${TARGET_NAME2} PUBLIC MESON_LOG_SHARED)
endif()

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/code2/Log.hh" "${CMAKE_CURRENT_SOURCE_DIR}/code2/Exporter.hh" DESTINATION "include/mesonlib/code2")

file(GLOB_RECURSE MESON_MOD_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "module/*.hh")
file(GLOB_RECURSE MESON_MOD_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "module/*.cc")

add_library(${TARGET_NAME3} MODULE ${MESON_MOD_SRCS} ${MESON_MOD_HDRS})

#target_link_libraries(${TARGET_NAME} PUBLIC)

target_include_directories(${TARGET_NAME3} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/module>
												 $<INSTALL_INTERFACE:include/mesonlib/module>)

target_link_libraries(${TARGET_NAME3} PUBLIC ${TARGET_NAME2})

set_target_properties(${TARGET_NAME3} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${TARGET_NAME3} PROPERTIES CXX_STANDARD 20)

reset_build_dir(${TARGET_NAME3})

target_compile_definitions(${TARGET_NAME3} PRIVATE MESON_MOD_EXPORTS)

if(WIN32)
    target_compile_definitions(${TARGET_NAME3} PUBLIC MESON_MOD_WINDOWS)
else()
    target_compile_definitions(${TARGET_NAME3} PUBLIC MESON_MOD_UNIX)
endif()

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/module/Hello.hh" "${CMAKE_CURRENT_SOURCE_DIR}/module/Exporter.hh" DESTINATION "include/mesonlib/module")

install(
  EXPORT "${MESONLIB_TARGETS_EXPORT_NAME}"
  NAMESPACE "${MESONLIB_NAMESPACE}"
  DESTINATION "${MESONLIB_CONFIG_INSTALL_DIR}")

install(TARGETS ${TARGET_NAME} ${TARGET_NAME2} ${TARGET_NAME3}
        EXPORT ${MESONLIB_TARGETS_EXPORT_NAME} 
		RUNTIME DESTINATION "bin"
        ARCHIVE DESTINATION "lib"
        LIBRARY DESTINATION "lib")