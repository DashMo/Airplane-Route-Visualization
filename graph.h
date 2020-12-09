#pragma once
#include "routes.h"
#include "airport.h"
#include <map>
#include<unordered_map>
#include <vector>
#include <list>
#include <string>
#include "cs225/PNG.h"
using std::string;
using cs225::PNG;
class Graph {

    public:
        Graph(string airportinfo, string routesinfo, string mapname); //constructor takes file names for airport database, routes database, and mercator map image
        void addRoute(int start, int end); //helper function that adds Route object
        void addAirport(double latitude, double longitude,std::string airportName, int airportID,std::string airportCity); //helper function that adds Airport object

        void drawMap(); //draws graph onto map
        PNG getMap(); //returns map store in graph object
        void drawRoute(Routes& route, PNG& pic); //helper function for draw map which draws edges
        void drawPath(std::vector<Airport>); //draws a path of edges based on input vector, used for drawing shortest number of flights to reach destination
        void drawAirport(Airport& airport, PNG& pic); //helper function for draw map which draws vertices
       
        std::vector<int> graphToFile(std::string& filename); //uses a breadth first traversal to cover the entire graph and print all airports stored in the graph in the order they are traversed
        void BreadthFirstTraversal(std::vector<bool>& visited, std::vector<int>& path, int AirportID);
        
        std::vector<Airport> BFS(Airport startNode, Airport endNode); //breadth first search that finds the shortest number of flights between two airports and returns the path
        std::vector<Airport> findPath(); //wrapper for BFS that accepts user input, will return shortest path (shortest number of flights)
        std::vector<Airport> findPath(int start, int end); //wrapper for BFS that takes in two airport ID's and finds shortest path between them in terms of number of flights, mainly used for testing

    private:
        //edge holds name of airport and name of destination airport, graph implementations and traversals, adjacency list
        std::unordered_map<int, Airport> airportMap; //hash map that maps airport ID to airport object
        std::unordered_map<int,std::vector<Routes>> routeList; //edgelist holding all the routes, key is airport ID and return value is vector of outgoing routes
        std::unordered_map<std::string, std::vector<int>> cities; //hash map that maps city name to vector of airport id's within that city
        cs225::PNG map; //will hold mercator map
        int maxID; //largest integer val for the airport IDs.
};