# Engine (Shared lib)
project(Engine VERSION 0.0.1)

# get all cpp-files
file(GLOB_RECURSE SRC_FILES src/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} ${SRC_FILES})

# define symbols
add_definitions(-DKAIM_EXPORT)
add_definitions(-D_DEBUG)

# Windows Platorm
if(WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32 glew32 SDL2 SDL2main SDL2_image SDL2_ttf SDL2_mixer SDL2_net)
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Windows/includes)
    target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Windows/libs)
endif(WIN32)

#Precompiled Headers
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp)

#Add includce directory
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)