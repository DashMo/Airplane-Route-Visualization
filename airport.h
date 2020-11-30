#pragma once
#include "routes.h"
#include <vector>

class Airport{
    public:
        Airport(double longitude, double latitude,std::string airportName); //constructs airport based on inputted longitude and latitude
        void increaseSize();
    private:
        std::vector<Routes> routes; //edgelist of outgoing routes from this airport
        int x; //x coordinate for mapping onto PNG
        int y; //y coordinate for mapping onto PNG
        double lon; //longitude
        double lat; //latitude
        int size; //number of incoming routes (to keep track of popularity of airport)
        std::string name; //name of airport

}