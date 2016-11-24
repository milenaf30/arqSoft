//
// Created by milena on 23/11/16.
//

#include "MateriasHandler.h"
#include "../Managers/MateriaManager.h"
#include "MateriaInexistenteException.h"
#include "InvalidRequestException.h"

MateriasHandler::MateriasHandler() {}

MateriasHandler::~MateriasHandler() {}

Response *MateriasHandler::handleGetRequest(http_message *httpMessage, string url) {
    MateriaManager* materiaManager = new MateriaManager(nullptr);
    Response* response = new Response();

    try {
        long materiaID = this->getMateriaID(url);
        Materia* materia = materiaManager->getMateria(materiaID);
        response->setBody(materia->jMateria.toStyledString());
        response->setSuccessfulHeader();
        delete materia;
    }catch (MateriaInexistenteException& e) {
        response->setErrorBody("Materia Inexistente");
        response->setNotFoundHeader();
    }catch (InvalidRequestException& e) {
        response->setErrorBody("Error en mensaje");
        response->setBadRequestHeader();
    }

    delete materiaManager;
    return response;
}

long MateriasHandler::getMateriaID(string url) {
    vector<string> parsedUrl = this->parseUrl(url);
    if (parsedUrl.size() != 1) {
        throw InvalidRequestException("Cannot get user id from url.");
    }
    string materiaIDAsString = parsedUrl[0];
    try {
        long materiaID = stol(materiaIDAsString);
        return materiaID;
    } catch (invalid_argument e) {
        throw InvalidRequestException("Not a numeric id");
    }
}
