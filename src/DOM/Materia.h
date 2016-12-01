//
// Created by milena on 23/11/16.
//

#ifndef ARQSOFT_MATERIA_H
#define ARQSOFT_MATERIA_H


#include "Curso.h"
#include <vector>
#include <string>

class Materia {
public:
    Materia(Json::Value jMateria);
    ~Materia();
    std::string nombre;
    Json::Value jMateria;
    std::string id;
    std::vector<Curso*> cursos;

    Curso *getCurso(std::string cursoID);

    void agregarInscripto(std::string cursoID, Alumno *alumno);

    void resetJson();
};


#endif //ARQSOFT_MATERIA_H
