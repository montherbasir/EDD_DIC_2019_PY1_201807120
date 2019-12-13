//
// Created by Monther on 12/12/2019.
//

#ifndef UNTITLED_ARTISTA_H
#define UNTITLED_ARTISTA_H


#include <string>
#include "Album.h"
#include "Matriz.h"

class Artista {
private:
    std::string nombre;
    Matriz<Album>* albumes;
public:
    Artista(const string &nombre, Matriz<Album> *albumes) : nombre(nombre), albumes(albumes) {}

    void setNombre(const string &nombre) {
        Artista::nombre = nombre;
    }

    void setAlbumes(Matriz<Album> *albumes) {
        Artista::albumes = albumes;
    }
};


#endif //UNTITLED_ARTISTA_H
