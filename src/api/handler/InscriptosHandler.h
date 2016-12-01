//
// Created by milena on 24/11/16.
//

#ifndef ARQSOFT_INSCRIPTOSHANDLER_H
#define ARQSOFT_INSCRIPTOSHANDLER_H


#include "Handler.h"

class InscriptosHandler: public Handler {
    ~InscriptosHandler();

    Response* handleGetRequest(http_message* httpMessage, string url);
    Response* handlePostRequest(http_message* httpMessage) ;
    Response* handleDeleteRequest(http_message* httpMessage, string url) ;
    Response* handlePutRequest(http_message* httpMessage, string url) ;

    string getCursoID(string url);
    long getMateriaID(string url);

public:
    InscriptosHandler();
};


#endif //ARQSOFT_INSCRIPTOSHANDLER_H
