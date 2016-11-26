//
// Created by milena on 24/11/16.
//

#ifndef ARQSOFT_DBBUILDER_H
#define ARQSOFT_DBBUILDER_H

#include <string>
#include <bits/basic_string.h>
#include "Managers/Materia.h"
#include "DB/DBWrapper.h"

class DbBuilder {
public:
    DbBuilder();
    ~DbBuilder();
    void set_upDB();
    Json::Value procesar_cursos(std::string value, Materia *materia);

    std::string *namedb;
    DBWrapper *db;

    void split2(const std::string &s, char delim, std::vector<std::string> &elems);

    std::vector<std::string> split(const std::string &s, char delim);

    std::vector<std::string> cargar_materias();

    void cargar_alumnos(std::vector<std::string> materias_disponibles);

    std::string crear_padron();
};


#endif //ARQSOFT_DBBUILDER_H
