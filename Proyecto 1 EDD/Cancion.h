//
// Created by Monther on 12/12/2019.
//

#ifndef UNTITLED_CANCION_H
#define UNTITLED_CANCION_H


#include <string>
#include <utility>

class Cancion {
private:
    std::string nombre;
    std::string file;
    std::string month;
    std::string album;
    std::string artist;
    int year;
    double rating;
public:
    Cancion(std::string nombre, std::string file, double rating) : nombre(std::move(nombre)), file(std::move(file)),
                                                                                 rating(rating) {}

    Cancion(const std::string &nombre, const std::string &file, const std::string &month, const std::string &album,
            const std::string &artist, int year, double rating) : nombre(nombre), file(file), month(month),
                                                                  album(album), artist(artist), year(year),
                                                                  rating(rating) {}

    const std::string &getNombre() const {
        return nombre;
    }

    void setNombre(const std::string &nombre_) {
        Cancion::nombre = nombre_;
    }

    const std::string &getFile() const {
        return file;
    }

    void setFile(const std::string &file_) {
        Cancion::file = file_;
    }

    double getRating() const {
        return rating;
    }

    void setRating(double rating_) {
        Cancion::rating = rating_;
    }

    const std::string &getMonth() const {
        return month;
    }

    void setMonth(const std::string &month_) {
        Cancion::month = month_;
    }

    const std::string &getAlbum() const {
        return album;
    }

    void setAlbum(const std::string &album_) {
        Cancion::album = album_;
    }

    const std::string &getArtist() const {
        return artist;
    }

    void setArtist(const std::string &artist_) {
        Cancion::artist = artist_;
    }

    int getYear() const {
        return year;
    }

    void setYear(int year_) {
        Cancion::year = year_;
    }
};


#endif //UNTITLED_CANCION_H
