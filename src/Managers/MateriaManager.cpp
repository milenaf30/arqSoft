//
// Created by milena on 23/11/16.
//

#include <json/json.h>
#include <iostream>
#include "MateriaManager.h"
#include "../api/MateriaInexistenteException.h"
#include "Materia.h"
#include "MateriaYaExisteException.h"
#include "CursoInexistenteException.h"

#define MATERIAID "materiaID_"
#define CURSOID "cursoID_"

MateriaManager::MateriaManager(DBWrapper *db) {
    this->db = db;
}

MateriaManager::~MateriaManager() {

}

Materia * MateriaManager::getMateria(long materiaID) {

    Json::Value jMateria;
    std::string informacion_materia;
    try {
        this->db->getKey(MATERIAID + std::to_string(materiaID), &informacion_materia);

    } catch (std::exception& e){
        throw MateriaInexistenteException();
    }

    jMateria = this->getJsonFromString(informacion_materia);
    Materia* materia = new Materia(jMateria);
    for(int i = 0; i<materia->cursos.size(); i++) {
        materia->cursos[i]->inscriptos = this->getInscriptosCurso(materia->id, materia->cursos[i]->id);
        for (int index = 0; index < materia->cursos[i]->inscriptos.size(); index++) {
            Alumno* alumno = materia->cursos[i]->inscriptos[index];
            materia->cursos[i]->jCurso["inscriptos"].append(alumno->jAlumno);
        }
    }

    return materia;
}


Json::Value MateriaManager::getJsonFromString(std::string basic_string) {
    Json::Reader reader;
    Json::Value jvalue;
    reader.parse(basic_string.c_str(), jvalue);
    return  jvalue;
}

std::string getStringFromJson(Json::Value jstring) {
    Json::FastWriter fastWriter;
    return fastWriter.write(jstring);
}

Curso *MateriaManager::getCurso(long materiaID, std::string cursoID) {
    Materia* materia = this->getMateria(materiaID);
    return materia->getCurso(cursoID);

}

std::vector<Alumno*> MateriaManager::getInscriptosCurso(std::string materiaID, std::string cursoID) {
    std::string output;
    std::vector<Alumno*> inscriptos;
    if (!this->db->existsKey(MATERIAID + materiaID + ":" +  CURSOID + cursoID, &output)) {
        return inscriptos; //aun no hay inscriptos en el curso
    }
    Json::Value inscriptos_curso = getJsonFromString(output)["inscriptos"];
    for (int i = 0; i < inscriptos_curso.size(); i++) {
        Alumno* inscripto = new Alumno(inscriptos_curso[i]);
        inscriptos.push_back(inscripto);
    }
    return  inscriptos;
}

void MateriaManager::saveMateria(Json::Value jMateria) {
    Materia* materia = new Materia(jMateria);

    Json::Value materia_input;
    std::string output;
    if (this->db->existsKey(MATERIAID + materia->id, &output)) {
        throw MateriaYaExisteException();
    }

    materia_input["nombre"] = materia->nombre;
    materia_input["id"] = materia->id;
    for (int i = 0; i < materia->cursos.size(); i++) {
        Json::Value jcurso_input;
        jcurso_input["dias"] = materia->cursos[i]->jCurso["dias"];
        jcurso_input["cursoID"] = materia->cursos[i]->jCurso["cursoID"];
        jcurso_input["profesores"] = materia->cursos[i]->jCurso["profesores"];
        materia_input["cursos"].append(jcurso_input);

        if (materia->cursos[i]->inscriptos.size() != 0) {
            Json::Value jcurso;
            jcurso["inscriptos"] = materia->cursos[i]->jCurso["inscriptos"];
            std::string sCursoInscriptos = getStringFromJson(jcurso);
            this->db->puTKey(MATERIAID + materia->id + ":" + CURSOID + materia->cursos[i]->id, &sCursoInscriptos);
        }

    }
    std::string sMateria = getStringFromJson(materia_input);
    if (materia->id != "") this->db->puTKey(MATERIAID + materia->id, &sMateria);



}

void MateriaManager::updateMateria(Json::Value jMateria) {
    Materia* materia = new Materia(jMateria);
    std::string output;
    if (!this->db->existsKey(MATERIAID + materia->id, &output)) {
        throw MateriaInexistenteException();
    }

    std::string sMateria = getStringFromJson(materia->jMateria);
    if (materia->id != "") this->db->puTKey(MATERIAID + materia->id, &sMateria);
}

void MateriaManager::agregarInscriptoAlCurso(std::string materiaID, std::string cursoID, Alumno *alumno) {

    Materia* materia = this->getMateria(std::stol(materiaID));
    materia->agregarInscripto(cursoID, alumno);
    this->updateInscriptosCurso(materiaID, materia->getCurso(cursoID));
    //std::cout << materia->jMateria << std::endl;

}

void MateriaManager::updateInscriptosCurso(std::string materiaID, Curso *curso) {
    std::string output;
    Json::Value inscriptos;
    inscriptos["inscriptos"] = curso->jCurso["inscriptos"];
    std::string sCurso = getStringFromJson(inscriptos);
    this->db->puTKey(MATERIAID + materiaID + ":" + CURSOID + curso->id, &sCurso);

}
