//
// Created by milena on 23/11/16.
//

#include <json/json.h>
#include <iostream>
#include "MateriaManager.h"
#include "../api/MateriaInexistenteException.h"
#include "Materia.h"
#include "MateriaYaExisteException.h"

#define MATERIAID "materiaID_"

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

void MateriaManager::saveMateria(Json::Value jMateria) {
    Materia* materia = new Materia(jMateria);
    std::string output;
    if (this->db->existsKey(MATERIAID + materia->id, &output)) {
        throw MateriaYaExisteException();
    }

    std::string sMateria = getStringFromJson(materia->jMateria);
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
   // Json::Value jMateria= materia->jMateria;
    materia->agregarInscripto(cursoID, alumno);
    //jMateria["cursos"]["inscriptos"].append(alumno->jAlumno);
    this->updateMateria(materia->jMateria);
    //std::cout << materia->jMateria << std::endl;

}