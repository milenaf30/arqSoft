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

    Curso();

    std::string profesores;
    std::vector<std::string> calendario;
    std::vector<Alumno*> inscriptos;
    Json::Value jCurso;
    std::string id;
    std::string nombre;
    Curso(Json::Value jcurso);
    ~Curso();

    void agregarAlumno(Alumno *inscripto);
};


#endif //ARQSOFT_CURSO_H
