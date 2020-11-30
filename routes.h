#pragma once
#include "airport.h"




class Routes {

    public:
        Routes(string source, string dest);

        
    private:
        double dist; //holds distance between two airports (weight of edge)
        std::string source; //holds source airport name
        std::string dest; //holds destination airport name
    
}