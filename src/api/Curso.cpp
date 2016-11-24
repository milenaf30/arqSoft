//
// Created by milena on 23/11/16.
//

#include "Curso.h"

Curso::Curso(Json::Value jcurso) {
    this->id = jcurso["cursoID"].asLargestInt();
    this->jCurso = jcurso;

    const Json::Value jprofesores = jcurso["profesores"];
    for (int index = 0; index < jprofesores.size(); index++) {
        this->profesores.push_back(jprofesores[index].asString());
    }

    const Json::Value jcronograma = jcurso["cronograma"];
    for (int index = 0; index < jcronograma.size(); index++) {
        Dia* dia = new Dia(jcronograma[index]);
        this->calendario.push_back(dia);
    }

    const Json::Value jAlumnos = jcurso["inscriptos"];
    for (int index = 0; index < jAlumnos.size(); index++) {
        Alumno* alumno = new Alumno(jAlumnos[index]);
        this->inscriptos.push_back(alumno);
    }

}

Curso::~Curso() {

}
