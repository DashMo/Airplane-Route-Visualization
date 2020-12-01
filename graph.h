#pragma once
#include "routes.h"
#include "airport.h"
#include <map>
#include<unordered_map>
#include <vector>
#include <string>
#include "cs225/PNG.h"
using std::string;

class Graph {

    public:
        Graph(string &airportinfo, string &routesinfo, string &mapname); //constructor takes file names for airport database, routes database, and mercator map image
        void addEdge();
        void addVertex();
        void displayMap();
        ~Graph();

    private:
        //edge holds name of airport and name of destination airport, graph implementations and traversals, adjacency list
        std::unordered_map<int, Airport> airportMap; //hash map that maps airport name to airport object
        std::unordered_map<std::string, std::vector<int>> cities; //hash map that maps city name to vector of airport id's within that city
        PNG map; //will hold mercator map
};