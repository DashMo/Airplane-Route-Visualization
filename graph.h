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
        PNG drawMap();
        void drawRoute(Routes& route, PNG& pic);
        void drawAirport(Airport& airport, PNG& pic);
        //~Graph();
        vector<Airport> BFS(Airport startNode, Airport endNode);

    private:
        //edge holds name of airport and name of destination airport, graph implementations and traversals, adjacency list
        std::unordered_map<int, Airport> airportMap; //hash map that maps airport ID to airport object
        std::unordered_map<int,std::vector<Routes>> routeList; //edgelist holding all the routes, key is airport ID and return value is vector of outgoing routes
        std::unordered_map<std::string, std::vector<int>> cities; //hash map that maps city name to vector of airport id's within that city
        cs225::PNG map; //will hold mercator map
        // std::vector<Airport> path;
        int maxID;
};