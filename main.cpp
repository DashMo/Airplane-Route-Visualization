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
    g.addRoute(3077,3797);
    g.addRoute(3797,3093);
    g.addRoute(3077,3093);
    g.addRoute(3093,507);
    //std::vector<Airport> path = g.findPath();
    // for(auto airport : g.findPath(3077,507)){
    //     cout<<airport.getName()<<" -> ";
    // }
    // cout<<std::endl;
    // g.drawPath(path);
    // cs225::PNG pic = g.getMap();
    // pic.writeToFile("ShortestRoute.png");
    // g.drawMap();
    // g.drawPath(path);
    // pic = g.getMap();
    // pic.writeToFile("TestMapV3.png");
    // return 1;
    // std::ofstream myFile;
    // myFile.open ("newFile.txt");
    std::string filename = "newFile.txt";
    g.graphToFile(filename);
    // myFile.close();
    return 1;
}