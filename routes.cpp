#include "routes.h"
#include <cmath>
#include <iostream>

//https://stackoverflow.com/questions/27126714/c-latitude-and-longitude-distance-calculator used to calculate distance using longitude and latitude
double toRad(double degree) {
    return degree/180 * 3.14159265359;
}

double getDist(double lat1, double long1, double lat2, double long2) {
    double dist;
    dist = sin(toRad(lat1)) * sin(toRad(lat2)) + cos(toRad(lat1)) * cos(toRad(lat2)) * cos(toRad(long1 - long2));
    dist = acos(dist);
//        dist = (6371 * pi * dist) / 180;
    //got dist in radian, no need to change back to degree and convert to rad again.
    dist = 6371 * dist;

    return dist;
}



Routes::Routes(int start, int end, double lat1, double lon1, double lat2, double lon2){
    source = start; //stores names of source and destination airports
    dest = end;
    dist = getDist(lat1,lon1,lat2,lon2) / 1.6; //edge weight is the distance between the two airports, converted from km to miles
    //std::cout<<start<<" "<<end<<" "<<dist<<std::endl;
}


