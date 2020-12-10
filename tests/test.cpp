#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../cs225/PNG.h"
#include <algorithm>
// #include "../edge.h"
// #include "../NetworkFlow.h"

#include <iostream>

TEST_CASE("Breadth First Traversal covers all nodes of connected graph", "[valgrind][weight=1]") {
    Graph g("fakefile", "fakefile2", "MercatorMap.png"); 
    g.addAirport((double)15.5, (double)18.8,"airport1", 1,"city1");
    g.addAirport((double)25.5, (double)28.8,"airport2", 2,"city2");
    g.addAirport((double)35.5, (double)38.8,"airport3", 3,"city3");
    g.addAirport((double)45.5, (double)48.8,"airport4", 4,"city4");
    g.addAirport((double)55.5, (double)58.8,"airport5", 5,"city5");
    g.addAirport((double)65.5, (double)68.8,"airport6", 6,"city6");
    g.addRoute(1,2);
    g.addRoute(2,3); //1,2, and 3 are connected
   
    g.addRoute(4,6); //4, 5, and 6 are connected
    g.addRoute(5,6);

    std::string filename = "tests/testBreadthFirstTraversalConnected.txt";
    std::vector<int> traverse = g.graphToFile(filename); //graphToFile uses the BreadthFirstTraversal function to traverse all the nodes and writes them to a file
    std::sort(traverse.begin(),traverse.end()); //breadth first traversal might traverse out of order so need to sort nodes for comparison with expected

    std::vector<int> expected = {1,2,3,4,5,6};

    REQUIRE(expected == traverse);
}


TEST_CASE("Breadth First Traversal covers all nodes of disconnected graph", "[valgrind][weight=1]") {
    Graph g("fakefile", "fakefile2", "MercatorMap.png"); 
    g.addAirport((double)15.5, (double)18.8,"airport1", 1,"city1");
    g.addAirport((double)25.5, (double)28.8,"airport2", 2,"city2");
    g.addAirport((double)35.5, (double)38.8,"airport3", 3,"city3");
    g.addAirport((double)45.5, (double)48.8,"airport4", 4,"city4");
    g.addAirport((double)55.5, (double)58.8,"airport5", 5,"city5");
    g.addAirport((double)65.5, (double)68.8,"airport6", 6,"city6");
    g.addRoute(1,2);
    g.addRoute(2,3);
    g.addRoute(3,5);
    g.addRoute(4,1);
    g.addRoute(4,6);
    g.addRoute(5,6);
    g.addRoute(2,4);

    std::string filename = "tests/testBreadthFirstTraversalDisconnected.txt";
    std::vector<int> traverse = g.graphToFile(filename); //graphToFile uses the BreadthFirstTraversal function to traverse all the nodes and writes them to a file
    std::sort(traverse.begin(),traverse.end()); //breadth first traversal might traverse out of order so need to sort nodes for comparison with expected

    std::vector<int> expected = {1,2,3,4,5,6};

    REQUIRE(expected == traverse);
}


TEST_CASE("Graph can read in file input"){
  Graph g("airports4.txt", "routes4.txt", "MercatorMap.png"); //reads in files containing 4 airports and some routes connecting them, the routes are repeated many times so that the size of the airports increases for the drawMap test later
  std::string filename = "tests/testGraphReadFromFile.txt";
  std::vector<int> traverse = g.graphToFile(filename); //graphToFile uses the BreadthFirstTraversal function to traverse all the nodes and writes them to a file
  std::sort(traverse.begin(),traverse.end()); //breadth first traversal might traverse out of order so need to sort nodes for comparison with expected

  std::vector<int> expected = {507,3077,3093,3797};

  REQUIRE(expected == traverse);
}


TEST_CASE("Check if bfs finds shortest path on connected graph", "[valgrind][weight=1]")
{
	Graph g("fakefile", "fakefile2", "MercatorMap.png"); 
    g.addAirport((double)15.5, (double)18.8,"airport1", 1,"city1");
    g.addAirport((double)25.5, (double)28.8,"airport2", 2,"city2");
    g.addAirport((double)35.5, (double)38.8,"airport3", 3,"city3");
    g.addAirport((double)45.5, (double)48.8,"airport4", 4,"city4");
    g.addAirport((double)55.5, (double)58.8,"airport5", 5,"city5");
    g.addAirport((double)65.5, (double)68.8,"airport6", 6,"city6");
    //multiple paths to airport 6 from 1
    g.addRoute(1,2);
    g.addRoute(2,3);
    g.addRoute(3,4);
    g.addRoute(4,1);
    g.addRoute(4,5);
    g.addRoute(5,6);
    g.addRoute(2,4);


    int start = 1;
    int end = 6;
    std::vector<Airport> path = g.findPath(start, end);

    std::vector<int> pathID; //makes vector of airport ID's using our path because it is easier to compare to our expected path
    for(auto airport : path){
      pathID.push_back(airport.getID());
    }

    std::vector<int> expectedPath = {1,2,4,5,6};

    REQUIRE(expectedPath == pathID);
}


TEST_CASE("BFS should only find path if routes are in the correct direction", "[valgrind][weight=1]")
{
	Graph g("airports4.txt", "fakefile2", "MercatorMap.png"); //need to make a unconnected graph
    
    g.addAirport((double)15.5, (double)18.8,"airport1", 1,"city1");
    g.addAirport((double)25.5, (double)28.8,"airport2", 2,"city2");
    g.addAirport((double)35.5, (double)38.8,"airport3", 3,"city3");
    g.addAirport((double)45.5, (double)48.8,"airport4", 4,"city4");
    g.addAirport((double)55.5, (double)58.8,"airport5", 5,"city5");
    g.addAirport((double)65.5, (double)68.8,"airport6", 6,"city6");
    //There is a path from 6 to 1 but not a path from 1 to 6
    g.addRoute(1,2);
    g.addRoute(2,3);
    g.addRoute(3,1);
    g.addRoute(2,1);
  
    g.addRoute(4,2);
    g.addRoute(4,5);
    g.addRoute(5,6);
    g.addRoute(6,4); 


    int start = 1;
    int end = 6;
    std::vector<Airport> path = g.findPath(start, end);
    std::vector<int> pathID; //makes vector of airport ID's using our path because it is easier to compare to our expected path
    for(auto airport : path){
      pathID.push_back(airport.getID());
    }
    std::vector<int> expectedPath = {}; 
    REQUIRE(expectedPath == pathID); //there should be no path from 1 to 6

    int start2 = 6;
    int end2 = 1;
    std::vector<Airport> path2 = g.findPath(start2, end2);
    std::vector<int> pathID2; //makes vector of airport ID's using our path because it is easier to compare to our expected path
    for(auto airport : path2){
      pathID2.push_back(airport.getID());
    }
    std::vector<int> expectedPath2 = {6,4,2,1}; 
    REQUIRE(expectedPath2 == pathID2); //there should be a path from 1 to 6
}


