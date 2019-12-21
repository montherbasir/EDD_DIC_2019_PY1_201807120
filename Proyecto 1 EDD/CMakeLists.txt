# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.15)
#set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required
project(untitled)

set(CMAKE_CXX_STANDARD 17)



find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
add_executable(untitled main.cpp EDD/Lista.h EDD/Pila.h EDD/Cola.h EDD/Matriz.h Album.h Cancion.h Artista.h EDD/ListaDoble.h PlaylistStack.h PlaylistQueue.h PlaylistShuffle.h EDD/ListaDobleCircular.h PlaylistCircular.h EDD/Arbol.h Playlist.h EDD/ListaArtistas.h)
target_link_libraries(untitled ${JSONCPP_LIBRARIES})