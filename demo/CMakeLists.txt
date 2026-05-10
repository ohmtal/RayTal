cmake_minimum_required(VERSION 3.24)
# -----------------------------------------------------------------------------
# Project settings:

project(RayFluxDemo)
set(PROJECT_SRC
    # src/main_class.cpp
    src/main_callbacks.cpp
)


# -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
# ------------- RayFlux
set(RAYFLUX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" CACHE PATH "Path to RayFlux")
# later as lib .... add_subdirectory()
set(RAYFLUX_SRC
  ${RAYFLUX_DIR}/RayFlux/Core.h
  ${RAYFLUX_DIR}/RayFlux/Settings.h
  ${RAYFLUX_DIR}/RayFlux/Main.h
  ${RAYFLUX_DIR}/RayFlux/Tools.cpp
  ${RAYFLUX_DIR}/RayFlux/Tools.h
  ${RAYFLUX_DIR}/RayFlux/Main.cpp
  ${RAYFLUX_DIR}/RayFlux/TypeDef.h
  ${RAYFLUX_DIR}/RayFlux/Settings.cpp
  ${RAYFLUX_DIR}/RayFlux/Gui.h
  ${RAYFLUX_DIR}/RayFlux/Gui.cpp
  ${RAYFLUX_DIR}/RayFlux/ResourceManager.h
  ${RAYFLUX_DIR}/RayFlux/ResourceManager.cpp
)

# ------------- RayLib
# set(PLATFORM "SDL" CACHE STRING "raylib platform" FORCE)
set(RAYLIB_DIR "${RAYFLUX_DIR}/lib/raylib" CACHE PATH "Path to RayLib")
message( STATUS "\n Set Raylib to: " ${RAYLIB_DIR} )

if(NOT EXISTS "${RAYLIB_DIR}/CMakeLists.txt")
  message(FATAL_ERROR
    "\n" ${RAYLIB_DIR}
    "\n ********** RayLib not found! *************"
  )
else()

  add_subdirectory("${RAYLIB_DIR}" "${CMAKE_BINARY_DIR}/raylib_build")

  # target_compile_definitions( raylib PUBLIC PLATFORM_DESKTOP_SDL)

endif()


# ------------- Main
add_executable(${PROJECT_NAME}
    ${RAYFLUX_SRC}
    ${PROJECT_SRC}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${RAYFLUX_DIR}
    ${RAYLIB_DIR}/src
    ${RAYFLUX_DIR}/lib/rayspice/
)


target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_DEFINE_MATH_OPERATORS)



set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
)
