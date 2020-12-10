#include "graph.h"
#include <iostream>
#include <fstream>
#include "cs225/PNG.h"
using std::cout;
//learned about input from terminal from GeeksForGeeks
int main(int argc, char *argv[]){
    if(argc < 3){
        cout<<"Not enough arguments. Need both the airportList file name and routeList filename."<<std::endl;
        return 1;
    }
    Graph g(argv[1],argv[2],"MercatorMap.png"); //uses first and second arguments inputted to main as the filenames for the airportlist and routeslist
    std::vector<Airport> path = g.findPath(); //calls findPath() to get user input for BFS 

    g.drawPath(path); //draws path onto map
    cs225::PNG pic = g.getMap();
    pic.writeToFile("ShortestRoute.png"); //returns shortest path drawn on map in this file
    g.drawMap(); //draws entire graph onto map
    g.drawPath(path); 
    pic = g.getMap(); //gets the map
    pic.writeToFile("OutputMap.png"); //writes the map png to this file 

    std::string filename = "GraphAirportList.txt"; //uses Breadth First Traversal to cover all nodes and write them to this file
    g.graphToFile(filename);
    return 1;
}