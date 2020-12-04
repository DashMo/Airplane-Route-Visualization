#include "graph.h"
#include <iostream>
#include "cs225/PNG.h"
using std::cout;

int main(){

    Graph g("airports.dat.txt","routes.dat.txt","MercatorMap.png");
    cs225::PNG pic = g.drawMap();
    //pic.writeToFile("TestMap.png");
    return 1;
}