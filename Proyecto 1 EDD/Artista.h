//
// Created by Monther on 12/12/2019.
//

#ifndef UNTITLED_ARTISTA_H
#define UNTITLED_ARTISTA_H


#include <string>
#include <utility>
#include "Album.h"
#include "EDD/Matriz.h"

class Artista {
private:
    std::string nombre;
    Matriz<Album>* albumes;
public:
    Artista(string nombre, Matriz<Album> *albumes) : nombre(std::move(nombre)), albumes(albumes) {}

    const string &getNombre() const {
        return nombre;
    }

    Matriz<Album> *getAlbumes() const {
        return albumes;
    }

    void setNombre(const string &nombre_) {
        Artista::nombre = nombre_;
    }

    void setAlbumes(Matriz<Album> *albumes_) {
        Artista::albumes = albumes_;
    }
};


#endif //UNTITLED_ARTISTA_H
