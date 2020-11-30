#pragma once
#include "routes.h"
#include "airport.h"
#include <std::map>
#include <std::vector>


class Graph {

    public:
        Graph(Routes edges[], int n, int N); //default constructor, may modify to take in two files
        void addEdge();
        void addVertex();
        void displayMap();
        ~Graph();

    private:
        //edge holds name of airport and name of destination airport, graph implementations and traversals, adjacency list
        Airport **head;
        std::map<std::string, Airport> airportMap;
}