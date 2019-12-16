//
// Created by Monther on 12/12/2019.
//

#ifndef UNTITLED_ALBUM_H
#define UNTITLED_ALBUM_H


#include <string>
#include <utility>
#include "EDD/Lista.h"
#include "Cancion.h"

class Album {
private:
    std::string nombre;
    std::string mes;
    int anio;
    double rating{};
    Lista<Cancion*>* canciones;
public:
    double getRating() const {
        return rating;
    }

    void setRating(double rating_) {
        Album::rating = rating_;
    }

    Album(std::string nombre, std::string mes, int anio, Lista<Cancion*> *canciones) : nombre(std::move(nombre)),
                                                                                                   mes(std::move(mes)), anio(anio),
                                                                                                   canciones(
                                                                                                           canciones) {}


    const std::string &getNombre() const {
        return nombre;
    }

    void setNombre(const std::string &nombre_) {
        Album::nombre = nombre_;
    }

    const std::string &getMes() const {
        return mes;
    }

    void setMes(const std::string &mes_) {
        Album::mes = mes_;
    }

    int getAnio() const {
        return anio;
    }

    void setAnio(int anio_) {
        Album::anio = anio_;
    }

    Lista <Cancion*> *getCanciones() const {
        return canciones;
    }

    void setCanciones(Lista <Cancion*> *canciones_) {
        Album::canciones = canciones_;
    }
};


#endif //UNTITLED_ALBUM_H
