//
// Created by milena on 23/11/16.
//

#ifndef ARQSOFT_INVALIDREQUESTEXCEPTION_H
#define ARQSOFT_INVALIDREQUESTEXCEPTION_H


#include <exception>
#include <string>

class InvalidRequestException : public  std::exception{
public:
    InvalidRequestException(const std::string& message) : errorMessage(message) {}
    ~InvalidRequestException() {}

    std::string getMessage() const {
        return(errorMessage);
    }

private:
    std::string errorMessage;
};


#endif //ARQSOFT_INVALIDREQUESTEXCEPTION_H
