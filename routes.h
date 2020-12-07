#pragma once
//#include "airport.h"
#include <string>


class Routes {

    public:
        Routes(int start, int end, double lat1, double lon1, double lat2, double lon2);

        
    //private:
        double dist; //holds distance between two airports (weight of edge)
        int source; //holds source airport ID
        int dest; //holds destination airport ID
        bool discovery;
        bool cross;
        
};