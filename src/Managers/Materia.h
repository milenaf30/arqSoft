//
// Created by milena on 23/11/16.
//

#ifndef ARQSOFT_MATERIA_H
#define ARQSOFT_MATERIA_H


#include "../api/Curso.h"
#include <vector>
#include <string>

class Materia {
public:
    Materia(Json::Value jMateria);
    ~Materia();
    std::string nombre;
    Json::Value jMateria;
    long id;
    std::vector<Curso*> cursos;

    Curso *getCurso(long cursoID);
};


#endif //ARQSOFT_MATERIA_H
