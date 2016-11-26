//
// Created by milena on 23/11/16.
//

#include <iostream>
#include "Curso.h"

Curso::Curso(Json::Value jcurso) {
    this->id = jcurso["cursoID"].asString();
    this->jCurso = jcurso;
    this->nombre = jcurso["nombre"].asString();
    this->profesores = jcurso["profesores"].asString();

    const Json::Value jcronograma = jcurso["dias"];
    for (int index = 0; index < jcronograma.size(); index++) {
        this->calendario.push_back(jcronograma[index].asString());
    }

    const Json::Value jAlumnos = jcurso["inscriptos"];
    for (int index = 0; index < jAlumnos.size(); index++) {
        Alumno* alumno = new Alumno(jAlumnos[index]);
        this->inscriptos.push_back(alumno);
    }

}

Curso::~Curso() {
    for (int index = 0; index < this->inscriptos.size(); index++) {
        delete(this->inscriptos[index]);
    }
}

Curso::Curso() {

}

void Curso::agregarAlumno(Alumno *inscripto) {
    this->inscriptos.push_back(inscripto);
    this->jCurso["inscriptos"].append(inscripto->jAlumno);
    //std::cout << this->jCurso.toStyledString();
}

