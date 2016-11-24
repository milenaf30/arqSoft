//
// Created by milena on 23/11/16.
//

#ifndef ARQSOFT_CURSO_H
#define ARQSOFT_CURSO_H

#include <string>
#include <vector>
#include <json/json.h>
#include "Dia.h"
#include "Alumno.h"

class Curso {
public:

    std::vector<std::string> profesores;
    std::vector<Dia*> calendario;
    std::vector<Alumno*> inscriptos;
    Json::Value jCurso;
    long id;
    Curso(Json::Value jcurso);
    ~Curso();

};


#endif //ARQSOFT_CURSO_H
