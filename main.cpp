#include "graph.h"
#include <iostream>
#include <fstream>
#include "cs225/PNG.h"
using std::cout;
//learned about input from terminal from GeeksForGeeks
int main(int argc, char *argv[]){
    std::cout << "There are " << argc << " arguments:\n";
 
    // Loop through each argument and print its number and value
    for (int count = 0; count < argc; ++count)
    {
        std::cout << count << ' ' << argv[count] << '\n';
    }
    
    Graph g(argv[1],argv[2],"MercatorMap.png");
    std::vector<Airport> path = g.findPath();

    g.drawPath(path);
    cs225::PNG pic = g.getMap();
    pic.writeToFile("ShortestRoute.png");
    g.drawMap();
    g.drawPath(path);
    pic = g.getMap();
    pic.writeToFile("TestMapV4.png");

    std::string filename = "GraphAirportList.txt";
    g.graphToFile(filename);
    return 1;
}