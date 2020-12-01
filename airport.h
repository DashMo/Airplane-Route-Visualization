#pragma once
#include "routes.h"
#include <vector>
#include <string>
class Airport{
    public:
        Airport(double longitude, double latitude,std::string airportName,unsigned width, unsigned height); //constructs airport based on inputted longitude and latitude, needs width and height of Mercator png to calculate x and y coordinates
        void increaseSize();
    private:
        std::vector<Routes> routes; //edgelist of outgoing routes from this airport
        int x; //x coordinate for mapping onto PNG
        int y; //y coordinate for mapping onto PNG
        double lon; //longitude
        double lat; //latitude
        int size; //number of incoming routes (to keep track of popularity of airport)
        std::string name; //name of airport
        Airport* prev;

}