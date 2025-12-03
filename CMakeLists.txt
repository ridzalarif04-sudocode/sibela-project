cmake_minimum_required(VERSION 3.10)


project(sibela)

# add_executable(sibela main.c)


find_package(ODBC REQUIRED)
set(PACKAGES
libs/utils.c
components/header.c
libs/login.c
model/model.c
update/update.c
views/drawView.c
views/homeView.c
views/loginView.c
views/landingView.c
views/memberView.c
data/initDb.c
data/staf.c
components/header.c
)

add_executable(sibela main.c ${PACKAGES})

# add_library(Raygui::DLL SHARED IMPORTED)
# set_target_properties(Raygui::DLL PROPERTIES
#     # IMPLIES the file you link against at *compile time* (the .a file)
#     IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/libs/dll/librayguidll.a"
    
#     # LOCATION points to the actual DLL required at *runtime*
#     IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libs/dll/raygui.dll"
    
#     # Tell CMake where to find the header files for this library
#     INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/libs/headers"
# )

set_target_properties(sibela PROPERTIES C_STANDARD 11)
target_include_directories(sibela PRIVATE ${PROJECT_SOURCE_DIR}/libs/headers)
if(WIN32)
    target_link_libraries(sibela PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/dll/libraylib.a  ${CMAKE_CURRENT_SOURCE_DIR}/libs/dll/libglfw3.a winmm gdi32 opengl32 ${ODBC_LIBRARIES})
else()
    target_link_libraries(sibela PRIVATE raylib ${ODBC_LIBRARIES})
endif()