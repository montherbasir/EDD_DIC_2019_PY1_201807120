//
// Created by Monther on 12/12/2019.
//

#ifndef UNTITLED_ALBUM_H
#define UNTITLED_ALBUM_H


#include <string>
#include <utility>
#include "Lista.h"
#include "Cancion.h"

class Album {
private:
    std::string nombre;
    std::string mes;
    int anio;
    Lista<Cancion>* canciones;
public:
    Album(std::string nombre, std::string mes, int anio, Lista<Cancion> *canciones) : nombre(std::move(nombre)),
                                                                                                   mes(std::move(mes)), anio(anio),
                                                                                                   canciones(
                                                                                                           canciones) {}


    const std::string &getNombre() const {
        return nombre;
    }

    void setNombre(const std::string &nombre) {
        Album::nombre = nombre;
    }

    const std::string &getMes() const {
        return mes;
    }

    void setMes(const std::string &mes) {
        Album::mes = mes;
    }

    int getAnio() const {
        return anio;
    }

    void setAnio(int anio) {
        Album::anio = anio;
    }

    Lista <Cancion> *getCanciones() const {
        return canciones;
    }

    void setCanciones(Lista <Cancion> *canciones) {
        Album::canciones = canciones;
    }
};


#endif //UNTITLED_ALBUM_H
