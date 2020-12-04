#include "airport.h"
#include <cmath>//
#include <string>

double calculateX(double lon, int width);
double calculateY(double lat, int height, int width);

Airport::Airport(double latitude, double longitude,std::string airportName,unsigned width, unsigned height,int airportID){
    lat = latitude;
    lon = longitude;
    x = (int)calculateX(longitude,width); //converts spherical coordinates to cartesian x
    y = (int)calculateY(latitude,height,width); //converts spherical coordinates to cartesian y
    name = airportName;
    size = 0;//initially has no routes set
    prev = NULL;
    ID = airportID;
}

double Airport::getLat(){
    return lat;
}

double Airport::getLon(){
    return lon;
}

int Airport::getX(){
    return x;
}

int Airport::getY(){
    return y;
}

int Airport::getID(){
    return ID;
}

int Airport::getSize(){
    return size;
}

std::string Airport::getName(){
    return name;
}

void Airport::increaseSize(){
    size++; //increases size by 1
}

//the following two code snippets were obtained from openstack to convert spherical longitude and langitude to cartesian cooridnates to plot onto 2D Mercator Map
//https://stackoverflow.com/questions/16080225/convert-lat-long-to-x-y-coordinates-c
double calculateX(double lon, int width)
{
    // width is map width
    double x = fmod((width*(180+lon)/360), (width +(width/2)));

    return x;
}

double calculateY(double lat, int height, int width)
{
    // height and width are map height and width
    double PI = 3.14159265359;
    double latRad = lat*PI/180;

    // get y value
    double mercN = log(tan((PI/4)+(latRad/2)));
    double y     = (height/2)-(width*mercN/(2*PI));
    return y;
}