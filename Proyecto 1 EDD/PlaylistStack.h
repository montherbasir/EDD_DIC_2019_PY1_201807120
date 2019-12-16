//
// Created by Monther on 15/12/2019.
//

#ifndef UNTITLED_PLAYLISTSTACK_H
#define UNTITLED_PLAYLISTSTACK_H

#include <string>
#include <utility>
#include "EDD/Pila.h"
#include "Cancion.h"

class PlaylistStack{
private:
    std::string name;
    std::string type;
    Pila<Cancion*> *canciones;

public:
    PlaylistStack(std::string name, std::string type) : name(std::move(name)), type(std::move(type))
    {
        canciones = new Pila<Cancion*>();
    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name_) {
        PlaylistStack::name = name_;
    }

    const std::string &getType() const {
        return type;
    }

    void setType(const std::string &type_) {
        PlaylistStack::type = type_;
    }

    Pila<Cancion*>* getCanciones() const{
        return canciones;
    }

    void setCanciones(Pila<Cancion*> *canciones_) {
        PlaylistStack::canciones = canciones_;
    }

    void addCancion(Cancion* cancion_){
        canciones->push(cancion_);
    }

};

#endif //UNTITLED_PLAYLISTSTACK_H
