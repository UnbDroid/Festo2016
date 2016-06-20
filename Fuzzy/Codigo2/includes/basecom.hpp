#ifndef BASECOM_HPP
#define BASECOM_HPP

#include "rec/robotino/com/all.h"
#include <iostream>

using namespace rec::robotino::com;

class BaseCom : public Com
{
public:
    BaseCom(const char * hostname){
        this->hostname = hostname;
    }

    void errorEvent( Error error, const char* errorString ){
        std::cerr << "Error: " << errorString << std::endl;
    }

    void connectedEvent(){
        std::cout << "Connected." << std::endl;
    }

    void connectionClosedEvent(){
        std::cout << "Connection closed." << std::endl;
    }

    void modeChangedEvent( bool isPassiveMode ){
        if( isPassiveMode ){
            std::cout << "Connected int passive mode." << std::endl;
        }
    }

    void start_connection(){
        // Connect
        std::cout << "Connecting..." << std::endl;
        this->setAddress(hostname);
        this->connect();
        std::cout << std::endl << "Connected" << std::endl;
    }

private:
    const char * hostname;

};



#endif              /* BASECOM_HPP */