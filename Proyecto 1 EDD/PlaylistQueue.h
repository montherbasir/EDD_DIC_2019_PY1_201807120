//
// Created by Monther on 15/12/2019.
//

#ifndef UNTITLED_PLAYLISTQUEUE_H
#define UNTITLED_PLAYLISTQUEUE_H

#include <string>
#include <utility>
#include "Cancion.h"
#include "EDD/Cola.h"
class PlaylistQueue{
private:
    std::string name;
    std::string type;
    Cola<Cancion*> *canciones;

public:
    PlaylistQueue(std::string name, std::string type) : name(std::move(name)), type(std::move(type))
    {
        canciones = new Cola<Cancion*>();
    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name_) {
        PlaylistQueue::name = name_;
    }

    const std::string &getType() const {
        return type;
    }

    void setType(const std::string &type_) {
        PlaylistQueue::type = type_;
    }

    Cola<Cancion*> *getCanciones() const{
        return canciones;
    }

    void setCanciones(Cola<Cancion*>* canciones_) {
        PlaylistQueue::canciones = canciones_;
    }

    void addCancion(Cancion* cancion_){
        canciones->queue(cancion_);
    }
};
#endif //UNTITLED_PLAYLISTQUEUE_H
