//
// Created by milena on 23/11/16.
//

#include <json/json.h>
#include <iostream>
#include "MateriaManager.h"
#include "../Exceptions/MateriaInexistenteException.h"
#include "../DOM/Materia.h"
#include "../Exceptions/MateriaYaExisteException.h"
#include "../Exceptions/CursoInexistenteException.h"

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

    //La información obtenido no tiene datos de inscriptos al curso.
    jMateria = this->getJsonFromString(informacion_materia);
    Materia* materia = new Materia(jMateria);

    //Se recupera la información de la base de datos.
    for(int i = 0; i<materia->cursos.size(); i++) {
        //fixme: Se esta actualizando el json de cada curso a mano para que tenga la informacion de los alumnos.
        //No deberia ser asi.
        std::vector<Alumno*> inscriptos = this->getInscriptosCurso(materia->id, materia->cursos[i]->id);
        for (int index = 0; index < inscriptos.size(); index++) {
            Alumno* alumno = inscriptos[index];
            materia->cursos[i]->agregarAlumno(alumno);
        }
    }

    return materia;
}

Materia * MateriaManager::getMateriaResume(long materiaID) {

    Json::Value jMateria;
    std::string informacion_materia;
    try {
        this->db->getKey(MATERIAID + std::to_string(materiaID), &informacion_materia);

    } catch (std::exception& e){
        throw MateriaInexistenteException();
    }

    //La información obtenido no tiene datos de inscriptos al curso.
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

/// Obtiene los inscriptos al curso de la materia,
/// guardados en la base de datos bajo la key "materiaID_<materiaID>:cursoID_<cursoID>".
/// El json tiene el cuerpo { "inscriptos":[{"nombre":<nombre>, "padrón":<nro_padron>}]
/// \param materiaID
/// \param cursoID
/// \return vector de todos los alumnos inscriptos al curso de la materia. Devuelve un vector vacio si aun no hay inscriptos.
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
    std::string output;
    if (this->db->existsKey(MATERIAID + materia->id, &output)) {
        throw MateriaYaExisteException();
    }

    Json::Value materia_input;
    materia_input["nombre"] = materia->nombre;
    materia_input["id"] = materia->id;
    for (int i = 0; i < materia->cursos.size(); i++) {
        //Se decide guardar cierta información.
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

void MateriaManager::agregarInscriptoAlCurso(Materia *materia, std::string cursoID, Alumno *alumno) {

    materia->agregarInscripto(cursoID, alumno);
    this->updateInscriptosCurso(materia->id, materia->getCurso(cursoID));
    std::cout << materia->jMateria << std::endl;

}

/// Actualiza en la bdd la información de los inscriptos al curso, pisando la existente o agregando una nueva clave
/// si no existiese previamente.
/// \param materiaID materia a la que pertenece el curso
/// \param curso objeto con la información del curso
void MateriaManager::updateInscriptosCurso(std::string materiaID, Curso *curso) {
    Json::Value inscriptos;
    inscriptos["inscriptos"] = curso->jCurso["inscriptos"];
    std::string sCurso = getStringFromJson(inscriptos);
    this->db->puTKey(MATERIAID + materiaID + ":" + CURSOID + curso->id, &sCurso);

}
