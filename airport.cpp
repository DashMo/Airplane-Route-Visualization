#include "airport.h"

Airport::Airport(double longitude, double latitude,std::string airportName){
    lat = latitude;
    lon = longitude;
    x = getX(longitude,latitude); //converts spherical latitude to cartesian x
    y = getY(longitdue,latitude); //converts spherical longitude to cartesian y
    name = airportName;
    size = 0;//initially has no routes set
}


//the following two code snippets were obtained from openstack to convert spherical longitude and langitude to cartesian cooridnates to plot onto 2D Mercator Map
//https://stackoverflow.com/questions/16080225/convert-lat-long-to-x-y-coordinates-c
double getX(double lon, int width)
{
    // width is map width
    double x = fmod((width*(180+lon)/360), (width +(width/2)));

    return x;
}

double getY(double lat, int height, int width)
{
    // height and width are map height and width
    double PI = 3.14159265359;
    double latRad = lat*PI/180;

    // get y value
    double mercN = log(tan((PI/4)+(latRad/2)));
    double y     = (height/2)-(width*mercN/(2*PI));
    return y;
}