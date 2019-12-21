
#include <iostream>
#include <json/json.h>
#include <memory>
#include <fstream>
#include "EDD/ListaDoble.h"
#include "EDD/Cola.h"
#include "EDD/Matriz.h"
#include "Album.h"
#include "Artista.h"
#include "PlaylistStack.h"
#include "PlaylistQueue.h"
#include "PlaylistShuffle.h"
#include "PlaylistCircular.h"
#include "EDD/ListaArtistas.h"
#include "EDD/Arbol.h"
#include <windows.h>

using namespace std;


Json::Value parseJson(const string &file) {
    ifstream infile{file};
    string rawJson{istreambuf_iterator<char>(infile), istreambuf_iterator<char>()};

    const auto rawJsonLength = static_cast<int>(rawJson.length());
    JSONCPP_STRING err;
    Json::Value root;

    Json::CharReaderBuilder builder;
    const unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err)) {
        cout << "error parsing revise la ruta" << endl;
        return 0;
    }

    return root;

}

ListaArtistas *cargarJson(const string &s, ListaArtistas *artistas) {

    Json::Value root = parseJson(s);

    for (int i = 0; i < root["Library"].size(); i++) {
        Json::Value artist = root["Library"][i]["Artist"];
        string name = artist["Name"].asString();
        //cout << "Artista: " << name << endl;
        double s=0;
        int n1=0;
        auto *art = new Artista(name, nullptr,0);
        auto *albumes = new Matriz<Album>(name);
        for (int j = 0; j < artist["Albums"].size(); j++) {
            Json::Value album = artist["Albums"][j];
            string name1 = album["Name"].asString();
            //cout << "   " << name1 << endl;
            string month = album["Month"].asString();
            //cout << "   " << month << endl;
            string year = album["Year"].asString();
            //cout << "   " << year << endl;
            auto *al = new Album(name1, month, stoi(year),0, nullptr,0);
            auto *canciones = new Lista<Cancion *>();
            double sum=0;
            int n=0;
            for (int k = 0; k < album["Songs"].size(); k++) {
                Json::Value song = album["Songs"][k];
                string name2 = song["Name"].asString();
                //cout << "       " << name2 << endl;
                string file = song["File"].asString();
                //cout << "       " << file << endl;
                string rating = song["Rating"].asString();
                //cout << "       " << rating << endl;
                auto *cancion = new Cancion(name2, file, month, name1, name, stoi(year), stod(rating));
                sum +=stod(rating);
                canciones->add_last(cancion);
                n++;
            }
            s+=sum;
            n1+=n;
            al->setRating(sum/n);
            al->setCanciones(canciones);
            albumes->insertar(al);
        }
        art->setAlbumes(albumes);
        art->setRating(s/n1);
        artistas->add_last(art);
    }
    return artistas;
}

void reproducirCancion(Cancion *cancion) {
    cout << "   -----------------------------------" << endl;
    cout << "                                      " << endl;
    cout << "             REPRODUCIENDO            " << endl;
    cout << "                                      " << endl;
    cout << "    " << cancion->getNombre() << endl;
    cout << "                                      " << endl;
    cout << "    Album: " << cancion->getAlbum() << endl;
    cout << "                                      " << endl;
    cout << "    Artista: " << cancion->getArtist() << endl;
    cout << "                                      " << endl;
    cout << "    Rating: " << to_string(cancion->getRating()) << endl;
    cout << "                                      " << endl;
    cout << "   -----------------------------------" << endl;
    cout << "Ingrese cualquier texto para salir" << endl;
}

void reproducirArtista(ListaArtistas *artistas_) {
    ART:
    string s;
    cout << endl;
    cout << "Selecciones un artista: " << endl;
    cout << "0: Salir" << endl;
    artistas_->ordenarNombre();
    for (int i = 0; i < artistas_->getSize(); i++) {
        cout << i + 1 << ": " << artistas_->get_element_at(i)->getNombre() << endl;
    }

    try {
        getline(cin, s);
        if (stoi(s) == 0) {
            return;
        }
        if (stoi(s) > artistas_->getSize()) {
            goto ART;
        }
        Artista *art = artistas_->get_element_at(stoi(s) - 1);
        ING:
        cout << endl;
        cout << "Albumes" << endl;
        art->imprimirAlbumes();
        Album alb = *new Album("", "", 0,0,nullptr,0);
        s = "";
        cout << endl;
        cout << "Ingrese el nombre de un album: " << endl;
        getline(cin, s);
        if (s == "0") {
            goto ART;
        }
        try {
            alb = art->buscarAlbum(s);
            SNG:
            cout << endl;
            cout << "Seleccione una cancion: " << endl;
            cout << "0: Salir" << endl;
            for (int i = 0; i < alb.getCanciones()->getSize(); i++) {
                cout << i + 1 << ": " << alb.getCanciones()->get_element_at(i)->getNombre() << endl;
            }
            s = "";
            getline(cin, s);

            if (s == "0") {
                goto ING;
            }

            if(stoi(s)<=alb.getCanciones()->getSize()){
                Cancion *cancion = alb.getCanciones()->get_element_at(stoi(s) - 1);
                reproducirCancion(cancion);

                s = "";
                getline(cin, s);
            }

            goto SNG;

        } catch (...) {
            goto ING;
        }
    } catch (...) {
        goto ART;
    }

}

void reproducirCanciones(ListaArtistas *artistas_) {
    CAN:
    int x = 0;
    auto *songs = new ListaDoble<Cancion *>();
    cout << "Seleccione una cancion:" << endl;
    string s;
    cout << "0: Salir" << endl;
    for (int i = 0; i < artistas_->getSize(); i++) {
        Artista *art = artistas_->get_element_at(i);
        for (int j = 0; j < art->getAlbumes()->getAllCanciones()->getSize(); j++) {
            songs->add_last(art->getAlbumes()->getAllCanciones()->get_element_at(j));
            cout << ++x << ": " << art->getAlbumes()->getAllCanciones()->get_element_at(j)->getNombre() << endl;
        }
    }

    try {
        getline(cin, s);
        if (s == "0") {
            return;
        }
        if(stoi(s)<=songs->getSize()) {
            reproducirCancion(songs->get_element_at(stoi(s) - 1));
            s = "";
            getline(cin, s);
        }
        goto CAN;
    } catch (...) {
        goto CAN;
    }

}

bool iequals(const string &a, const string &b) {
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}


int getType(const string &a) {
    if (iequals(a, "Stack")) {
        return 1;
    }
    if (iequals(a, "Queue")) {
        return 2;
    }
    if (iequals(a, "Shuffle")) {
        return 3;
    }
    if (iequals(a, "Circular")) {
        return 4;
    }
    return 0;
}


void plStack(string s, Json::Value root, Arbol* playlists){
    cout << "STACK" << endl;
    auto *playlist = new PlaylistStack(s,"Stack");
    for (int i = 0; i < root["Songs"].size(); i++) {

        Json::Value song = root["Songs"][i];
        int year =stoi(song["Year"].asString());
        //cout << "       " << to_string(year) << endl;
        string month = song["Month"].asString();
        //cout << "       " << month << endl;
        string album = song["Album"].asString();
        //cout << "       " << album << endl;
        string name = song["Song"].asString();
        //cout << "       " << name << endl;
        string artist = song["Artist"].asString();
        //cout << "       " << artist << endl;
        auto *cancion = new Cancion(name,"",month,album,artist,year,0);

        playlist->addCancion(cancion);
    }
    playlists->add(playlist);
    //playlist->reproducir();
}

void plShuffle(string s, Json::Value root, Arbol* playlists){
    cout << "SHUFFLE" << endl;
    auto *playlist = new PlaylistShuffle(s,"Shuffle");
    for (int i = 0; i < root["Songs"].size(); i++) {

        Json::Value song = root["Songs"][i];
        int year =stoi(song["Year"].asString());
        //cout << "       " << to_string(year) << endl;
        string month = song["Month"].asString();
        //cout << "       " << month << endl;
        string album = song["Album"].asString();
        //cout << "       " << album << endl;
        string name = song["Song"].asString();
        //cout << "       " << name << endl;
        string artist = song["Artist"].asString();
        //cout << "       " << artist << endl;
        auto *cancion = new Cancion(name,"",month,album,artist,year,0);

        playlist->addCancion(cancion);
    }
    playlists->add(playlist);
    //playlist->reproducir();
}

void plQueue(string s, Json::Value root, Arbol* playlists){
    cout << "QUEUE" << endl;
    auto *playlist = new PlaylistQueue(s,"Queue");
    for (int i = 0; i < root["Songs"].size(); i++) {

        Json::Value song = root["Songs"][i];
        int year =stoi(song["Year"].asString());
        //cout << "       " << to_string(year) << endl;
        string month = song["Month"].asString();
        //cout << "       " << month << endl;
        string album = song["Album"].asString();
        //cout << "       " << album << endl;
        string name = song["Song"].asString();
        //cout << "       " << name << endl;
        string artist = song["Artist"].asString();
        //cout << "       " << artist << endl;
        auto *cancion = new Cancion(name,"",month,album,artist,year,0);

        playlist->addCancion(cancion);
    }
    playlists->add(playlist);
    //playlist->reproducir();
}

void plCircular(string s, Json::Value root, Arbol* playlists){
    cout << "CIRCULAR" << endl;
    auto *playlist = new PlaylistCircular(s,"Circular");
    for (int i = 0; i < root["Songs"].size(); i++) {

        Json::Value song = root["Songs"][i];
        int year =stoi(song["Year"].asString());
        //cout << "       " << to_string(year) << endl;
        string month = song["Month"].asString();
        //cout << "       " << month << endl;
        string album = song["Album"].asString();
        //cout << "       " << album << endl;
        string name = song["Song"].asString();
        //cout << "       " << name << endl;
        string artist = song["Artist"].asString();
        //cout << "       " << artist << endl;
        auto *cancion = new Cancion(name,"",month,album,artist,year,0);

        playlist->addCancion(cancion);
    }
    playlists->add(playlist);
    //playlist->reproducir();
}

void cargarPlaylist(Arbol* playlists) {
    cout << "Ingrese la ruta del archivo json: " << endl;
    //string s=R"(C:\Users\Monther\Downloads\Playlist_Rock.json)";
    string s;
    getline(cin, s);
    cout << endl;

    Json::Value root = parseJson(s);
    const size_t last_slash_idx = s.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        s.erase(0, last_slash_idx + 1);
    }

    const size_t period_idx = s.rfind('.');
    if (std::string::npos != period_idx)
    {
        s.erase(period_idx);
    }

    cout << "Playlist cargada" <<endl;
    cout << "Nombre: " << s <<endl;

    int type = getType(root["Type"].asString());

    if(type==1){
        plStack(s, root, playlists);
    }else if(type==2) {
        plQueue(s, root, playlists);
    }else if(type==3) {
        plShuffle(s, root, playlists);
    }else if(type==4) {
        plCircular(s, root, playlists);
    }

}

void reproducirPlaylist(Arbol *playlists){
    if(!playlists->isEmpty()){
        string c;
        cout << "Playlists:"<<endl;
        cout <<"0: Salir"<<endl;
        playlists->imprimir();
        cout<<"Ingrese el nombre de la playlist"<<endl;
        getline(cin,c);
        playlists->buscar(c)->reproducir();
    }else{
        cout<<"Cargue una playlist primero"<<endl;
    }

}

void discRep(ListaArtistas* artistas){
    string s;
    cout << endl;
    cout << "Selecciones un artista: " << endl;
    cout << "0: Salir" << endl;
    artistas->ordenarNombre();
    for (int i = 0; i < artistas->getSize(); i++) {
        cout << i + 1 << ": " << artistas->get_element_at(i)->getNombre() << endl;
    }
    getline(cin, s);
    if (stoi(s) == 0) {
        return;
    }
    if (stoi(s) > artistas->getSize()) {
        return;
    }
    artistas->get_element_at(stoi(s) - 1)->getAlbumes()->generarStringGraph();
}

void top5Art(ListaArtistas* artistas){
    string s;
    cout << endl;
    cout << "0: Salir" << endl;
    artistas->ordenarRating();

    artistas->generarReporte();
}

void reportes(Arbol* playlists, ListaArtistas* artistas){
    cout << "Seleccione un reporte:" <<endl;
    cout << "0: Salir" << endl;
    cout << "1: Reporte de artistas" << endl;
    cout << "2: Discography report" << endl;
    cout << "3: Album report" << endl;
    cout << "4: Playlists report" << endl;
    cout << "5: Top 5 albums by artist" << endl;
    cout << "6: Top 5 artists" << endl;
    string x;
    getline(cin,x);
    try {
        switch (stoi(x)) {
            case 0:
                return;
            case 1:
                artistas->ordenarNombre();
                artistas->generarReporte();
                return;
                break;
            case 2:
                discRep(artistas);
                    break;
            case 3:
                cargarPlaylist(playlists);
                break;
            case 4:
                playlists->graficar();
                break;
            case 6:
                top5Art(artistas);
                break;
        }
    } catch (const std::exception &exc) {
        cout << exc.what() ;
    }
}


int main() {

    auto *artistas = new ListaArtistas();
    auto *playlists = new Arbol();
//    auto *m = new Matriz<Album>("Monther");
//    m->insertarColumna(10);
//    m->insertarColumna(11);
//    m->insertarColumna(13);
//    m->insertarColumna(1);
//    m->insertarColumna(100);
//    m->insertarColumna(0);
//    m->insertarColumna(100);
//    m->insertarColumna(10);
//
//    m->insertarFila("Enero");
//    m->insertarFila("Marzo");
//    m->insertarFila("diciembre");
//    m->insertarFila("julio");
//    m->insertarFila("Marzo");

//    m->insertar(new Album("M1","mayo",2019, nullptr));
//    m->insertar(new Album("M2","agosto",2019, nullptr));
//    m->insertar(new Album("M3","mayo",2018, nullptr));
//    m->insertar(new Album("M4","marzo",2020, nullptr));
//    m->insertar(new Album("M5","marzo",2020, nullptr));
//
//    m->imprimirCol();
//    m->imprimirFilas();

    cout << "Bienvenido a Music++" << endl;
    cout << "Ingrese la ruta del archivo json: " << endl;
    //string s=R"(C:\Users\Monther\Downloads\Library.json)";
    string s;
    getline(cin, s);
    cout << endl;
    artistas = cargarJson(s, artistas);

    string x;
    while (x != "0") {
        cout << "MENU:" << endl;
        cout << "0: Salir" << endl;
        cout << "1: Reproducir por artista" << endl;
        cout << "2: Reproducir por canciones" << endl;
        cout << "3: Cargar playlist" << endl;
        cout << "4: reproducir playlist" << endl;
        cout << "5: Reportes" << endl;
        getline(cin, x);



        try {
            switch (stoi(x)) {
                case 0:
                    break;
                case 1:
                    reproducirArtista(artistas);
                    break;
                case 2:
                    reproducirCanciones(artistas);
                    break;
                case 3:
                    cargarPlaylist(playlists);
                    break;
                case 4:
                    reproducirPlaylist(playlists);
                    break;
                case 5:
                    reportes(playlists,artistas);
                    break;
            }
        } catch (const std::exception &exc) {
            cout << exc.what() ;
            continue;
        }


    }

    return 0;
}
