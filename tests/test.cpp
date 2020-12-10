#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../cs225/PNG.h"

// #include "../edge.h"
// #include "../NetworkFlow.h"

#include <iostream>

TEST_CASE("Graph a - 10 -> b  has flow of 10.", "[valgrind][weight=1]") {
  //Graph g = Graph(true,true);

  
}
TEST_CASE("bfsConnected", "[valgrind][weight=1]")
{
	Graph g("fakefile", "fakefile2", "fakefile3"); //need to make a connected graph
    g.addAirport((double)15.5, (double)18.8,"fakeairport1", 3077,"fakecity1");
    g.addAirport((double)25.5, (double)28.8,"fakeairport2", 3678,"fakecity2");
    g.addAirport((double)35.5, (double)38.8,"fakeairport3", 3077,"fakecity3");
    g.addAirport((double)45.5, (double)48.8,"fakeairport4", 3093,"fakecity4");
    g.addAirport((double)55.5, (double)58.8,"fakeairport4", 507,"fakecity4");
    g.addAirport((double)65.5, (double)68.8,"fakeairport4", 3799,"fakecity4");
    g.addRoute(3077,3799);
    g.addRoute(3799,3093);
    g.addRoute(3093,507);
    g.addRoute(507,798);
    int start = 3077;
    int end = 798;
    std::vector<Airport> path = g.findPath(start, end);
    int expectedID = 3678;

    REQUIRE(expectedID == path.at(4).getID());
}

TEST_CASE("bfsUnconnected", "[valgrind][weight=1]")
{
	Graph g("fakefile", "fakefile2", "fakefile3"); //need to make a unconnected graph
    g.addAirport((double)15.5, (double)18.8,"fakeairport1", 3077,"fakecity1");
    g.addAirport((double)25.5, (double)28.8,"fakeairport2", 3678,"fakecity2");
    g.addAirport((double)35.5, (double)38.8,"fakeairport3", 3077,"fakecity3");
    g.addAirport((double)45.5, (double)48.8,"fakeairport4", 3093,"fakecity4");
    g.addAirport((double)55.5, (double)58.8,"fakeairport4", 507,"fakecity4");
    g.addAirport((double)65.5, (double)68.8,"fakeairport4", 3799,"fakecity4");
    g.addRoute(3077,3678);
    g.addRoute(3799,3093);
    g.addRoute(3087,3098);
    g.addRoute(3093,507);
    int start = 3077;
    int end = 3093;
    std::vector<Airport> path = g.findPath(start, end);
    int expectedEndID = 3678;

    REQUIRE(expectedEndID == path.at(1).getID());
}