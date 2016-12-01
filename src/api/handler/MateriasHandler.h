//
// Created by milena on 23/11/16.
//

#ifndef ARQSOFT_MATERIASHANDLER_H
#define ARQSOFT_MATERIASHANDLER_H


#include "Handler.h"

class MateriasHandler: public  Handler{

    ~MateriasHandler();

    Response* handleGetRequest(http_message* httpMessage, string url);
    Response* handlePostRequest(http_message* httpMessage);
    Response* handleDeleteRequest(http_message* httpMessage, string url);
    Response* handlePutRequest(http_message* httpMessage, string url);


    long getMateriaID(string basic_string);

public:
    MateriasHandler();


};


#endif //ARQSOFT_MATERIASHANDLER_H
