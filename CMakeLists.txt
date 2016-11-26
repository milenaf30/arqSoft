cmake_minimum_required(VERSION 2.8)
project(arqSoft)

set (CMAKE_CXX_FLAGS " -std=c++0x")
set (TARGET arqSoft)

# set this variable to specify a common place where CMake should put all executable files
# (instead of CMAKE_CURRENT_BINARY_DIR)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

include_directories ("${PROJECT_SOURCE_DIR}/src/jsoncpp")
include_directories ("${PROJECT_SOURCE_DIR}/src/Mongoose")
include_directories ("${PROJECT_SOURCE_DIR}/src/leveldb/db")
include_directories ("${PROJECT_SOURCE_DIR}/src/leveldb/include")
include_directories ("${PROJECT_SOURCE_DIR}/src/leveldb/leveldb/util")
include_directories ("${PROJECT_SOURCE_DIR}/src/leveldb/leveldb/port")


link_directories("${CMAKE_BINARY_DIR}/lib")


add_subdirectory(src/leveldb)
add_subdirectory(src/Mongoose)
add_subdirectory(src/jsoncpp)
add_subdirectory(src/googletest)

set(SOURCE_FILES
        src/main.cpp
        src/api/WebHandler.h
        src/api/WebHandler.cpp
        src/api/Response.cpp
        src/api/handler/Handler.h
        src/api/handler/Handler.cpp
        src/api/Response.h
        src/DB/DBWrapper.h
        src/DB/DBWrapper.cpp
    src/Mongoose/mongoose.c
    src/Mongoose/mongoose.h src/api/MateriasHandler.cpp src/api/MateriasHandler.h src/Managers/MateriaManager.cpp src/Managers/MateriaManager.h src/api/MateriaInexistenteException.cpp src/api/MateriaInexistenteException.h src/api/InvalidRequestException.cpp src/api/InvalidRequestException.h src/api/Curso.cpp src/api/Curso.h src/api/Dia.cpp src/api/Dia.h src/Managers/Manager.cpp src/Managers/Manager.h src/Managers/Materia.cpp src/Managers/Materia.h src/api/InscriptosHandler.cpp src/api/InscriptosHandler.h src/api/Alumno.cpp src/api/Alumno.h src/Managers/CursoInexistenteException.cpp src/Managers/CursoInexistenteException.h src/Managers/MateriaYaExisteException.cpp src/Managers/MateriaYaExisteException.h src/DbBuilder.cpp src/DbBuilder.h)

add_executable(arqSoft ${SOURCE_FILES})

target_link_libraries (${TARGET} Mongoose)
target_link_libraries (${TARGET} JsonCpp)
target_link_libraries (${TARGET} leveldb)
