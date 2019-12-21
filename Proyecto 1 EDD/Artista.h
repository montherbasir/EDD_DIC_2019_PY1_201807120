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
    double rating;
public:
    Artista(string nombre, Matriz<Album> *albumes, double rating_) : nombre(std::move(nombre)), albumes(albumes), rating(rating_) {}

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

    void imprimirAlbumes(){
        albumes->imprimirAlbumes();
    }

    Album buscarAlbum(const string& nombre_){
        return albumes->buscarAlbum(nombre_);
    }

    double getRating() const {
        return rating;
    }

    void setRating(double rating_) {
        Artista::rating = rating_;
    }


    void getRated() {

    }

};


#endif //UNTITLED_ARTISTA_H
