#include "graph.h"
#include <iostream>
#include "cs225/PNG.h"
using std::cout;

int main(){

    Graph g("airports.dat.txt","routes.dat.txt","MercatorMap.png");
    //g.addRoute(3077,3797);
    //g.addRoute(3797,3093);
    //g.addRoute(3077,3093);
    //g.addRoute(3093,507);
    for(auto airport : g.search(3077,507)){
        cout<<airport.getName()<<" -> ";
    }
    cout<<std::endl;
    cs225::PNG pic = g.drawMap();
    pic.writeToFile("TestMapV3.png");
    return 1;
}