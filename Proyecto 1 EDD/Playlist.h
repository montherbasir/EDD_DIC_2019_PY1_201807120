//
// Created by Monther on 19/12/2019.
//

#ifndef UNTITLED_PLAYLIST_H
#define UNTITLED_PLAYLIST_H

#include <string>
#include <utility>
#include <iostream>
#include "Cancion.h"

class Playlist{
    std::string name;
    std::string type;
public:
    Playlist(std::string name, std::string type) : name(std::move(name)), type(std::move(type)) {}

    virtual void addCancion(Cancion* cancion_)=0;

    virtual void reproducir()=0;

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name_) {
        Playlist::name = name_;
    }

    const std::string &getType() const {
        return type;
    }

    void setType(const std::string &type_) {
        Playlist::type = type_;
    }
};

#endif //UNTITLED_PLAYLIST_H
