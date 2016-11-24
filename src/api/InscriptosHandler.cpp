//
// Created by milena on 24/11/16.
//

#include "InscriptosHandler.h"
#include "../Managers/MateriaManager.h"
#include "InvalidRequestException.h"

InscriptosHandler::InscriptosHandler() {

}

InscriptosHandler::~InscriptosHandler() {

}

Response *InscriptosHandler::handleGetRequest(http_message *httpMessage, string url) {
    Response* response = new Response();
    MateriaManager* materiaManager = new MateriaManager(this->db);

    try {
        long materiaID = this->getMateriaID(url);
        long cursoID = this->getCursoID(url);
        Curso* curso = materiaManager->getCurso(materiaID, cursoID);
    } catch (InvalidRequestException& e) {
        response->setBadRequestHeader();
        response->setErrorBody(e.getMessage());
    }


    delete materiaManager;
    return response;
}

long InscriptosHandler::getMateriaID(string url) {
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

long InscriptosHandler::getCursoID(string url) {
    vector<string> parsedUrl = this->parseUrl(url);
    if (parsedUrl.size() != 1) {
        throw InvalidRequestException("Cannot get user id from url.");
    }
    string cursoIDAsString = parsedUrl[1];
    try {
        long cursoID = stol(cursoIDAsString);
        return cursoID;
    } catch (invalid_argument e) {
        throw InvalidRequestException("Not a numeric id");
    }
}
