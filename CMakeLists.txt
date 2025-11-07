cmake_minimum_required(VERSION 3.10)

project(DecodificadorPRT7 
    VERSION 1.0
    DESCRIPTION "Decodificador de Protocolo Industrial PRT-7"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/ListaDeCarga.cpp
    src/RotorDeMapeo.cpp
    src/TramaLoad.cpp
    src/TramaMap.cpp
    src/SerialPort.cpp
)

# Archivo ejecutable principal
add_executable(decodificador_prt7 ${SOURCES})

install(TARGETS decodificador_prt7 DESTINATION bin)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generando documentacion con Doxygen"
        VERBATIM)
endif()

