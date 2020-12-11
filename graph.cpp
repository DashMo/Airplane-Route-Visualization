#include "graph.h"
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include <iostream>
#include "cs225/HSLAPixel.h"
#include <cmath>
#include <algorithm>
using std::vector;
using std::cout;
using std::endl;
using cs225::HSLAPixel;
using std::ifstream;

//Graph Constructor, takes input files for airport and route information and creates graph structure
Graph::Graph(string airportList, string routesList, string mapname){
  maxID = 1;
  map.readFromFile(mapname); //stores mercator map into graph class
  
  ///////////////FIRST SECTION - parse airportList file to create vertices of graph//////////////
  ifstream airports(airportList); //opens file
  string line; //will hold each line read
  string word; //will hold each word parsed from the line
  
  while(getline(airports,line)){ //will keep iterating until all the lines are read 
    std::istringstream ss(line); //stringsream to parse line read
    vector<string> row; //vector will hold seperated data of the line
    while(getline(ss, word, ',')) { //gets each word in the line (they are comma seperated) and stores in vector
      row.push_back(word);
    }

    if(row[1].back() != '"'){  //handles exception where some of the airport names have a comma which messes with the stringstream delimiter which was looking for commas
      row[1] = row[1]+row[2];  //recombines the seperated airport name
      row.erase(row.begin() + 2);
    }
    if(row[2].back() != '"'){ //handles exception where some of the cities have a comma which messes with the stringstream delimiter which was looking for commas
      row[2] = row[2]+row[3]; //recombines the seperated city name
      row.erase(row.begin() + 3);
    }
    
    int airportID = stoi(row[0]); //first index holds the airport ID
    string airportName = row[1].substr(1,row[1].length()-2); //gets airport name and removes quotes
    string airportCity = row[2].substr(1,row[2].length()-2); //gets city name and removes quotes
    double lat = stod(row[6]); //gets latitude
    double lon = stod(row[7]); //gets longitude
    //cout<<airportID<<" "<<airportName<<" "<<airportCity<<" "<<lat<<" "<<lon<<endl<<endl;
    addAirport(lat,lon,airportName,airportID,airportCity);
  }

  /////////////Second Section - parse routeList file to add edges to graph///////////////
  ifstream routes(routesList); //opens file
    while(getline(routes,line)){ //will keep iterating until all the lines are read 
        std::istringstream ss(line); //stringsream to parse line read
        vector<string> row; //vector will hold seperated data of the line
        while(getline(ss, word, ',')) { //gets each word in the line (they are comma seperated) and stores in vector
            //cout<<word<<" ";
            row.push_back(word);
        }
        //cout<<endl;
        if(row[3]!="\\N" && row[5]!="\\N"){ //does not use entry if the entry is missing its airport ID for the source or destination airport
          int start = stoi(row[3]); //converts source airport ID to integer
          int end = stoi(row[5]); //converts destination airport ID to integer
          addRoute(start,end);
          
        }
    }
    //cout<<airportMap.size()<<" "<<routeList.size()<<endl;

}



//helper function that adds routes(edges) to graph based on parsed file
void Graph::addRoute(int start, int end){
  if(airportMap.find(start) != airportMap.end() && airportMap.find(end) != airportMap.end()){ //if the source and destination airports exist in the map, store the route
    Airport &begin = airportMap.at(start); //gets start and ending airports
    Airport &stop = airportMap.at(end);
    stop.increaseSize(); //increases size of airport for which the flight is incomings
    Routes path(start, end, begin.getLat(),begin.getLon(), stop.getLat(), stop.getLon()); //makes Route object (edge)
    routeList[start].push_back(path); //insert route into edgelist
  }
}


//helper function that adds airports(vertices) to graph based on parsed file
void Graph::addAirport(double latitude, double longitude,std::string airportName, int airportID,std::string airportCity){
    cities[airportCity].push_back(airportID); //stores airportID within the correct city
    Airport airport(latitude,longitude,airportName, map.width(), map.height(),airportID); //creates airport object
    airportMap.insert(std::make_pair(airportID,airport)); //stores airport object into vertex map
    if(airportID > maxID)
      maxID = airportID;
}



//function that iterates through graph to project all the vertices and edges onto map
void Graph::drawMap(){
  cout<<"Drawing Map..."<<endl;
  PNG & pic = map;
  for(auto list : routeList){ //iterates through all the airports' outgoing edgelists
    for(auto route : list.second) //iterates through all the edgelist's routes
      drawRoute(route, pic); //calls drawRoute to draw edge between the two airports
  }
  for(auto airport:airportMap){
    drawAirport(airport.second, pic); //draws each airport by passing in each airport from the map
  }
  cout<<"Finished Drawing Map"<<endl<<endl;
}

//simple getter function to return graph object's map
PNG Graph::getMap(){
  return map;
}

//draws the edge between two airports onto the map
void Graph::drawRoute(Routes& route, PNG& pic){
  Airport& a1 = airportMap.at(route.source); //gets the two airports
  Airport& a2 = airportMap.at(route.dest);
  int x1,x2,y1,y2,dx,dy;
  int saturation;
  //calculate color of route edge based on its distance, ranges from green being the shortest distance to red being the largest distance
  if(route.dist > 7000) 
    saturation = 0;
  else{
    saturation = 120 - (route.dist / 7000 * 120); //this calculation ensures that the distance is scaled to the range 0-120 which is the color range from red to green
  }
  


  //initializes variables so that the airport with the larger x coordinate is stored in x2 and y2
  if(a1.getX() < a2.getX()){ 
    x1 = a1.getX();
    x2 = a2.getX();
    y1 = a1.getY();
    y2 = a2.getY();
  }
  else{
    x1 = a2.getX();
    x2 = a1.getX();
    y1 = a2.getY();
    y2 = a1.getY();
  }

  dx = x2 - x1; //calculates difference in x
  dy = y2 - y1; //calculates difference in y
  int j;
  for(int i = x1; i < x2; i++){ //iterates through all the pixels in the horizantal range of the line
    j = y1 + dy*(i - x1) / dx; //uses a form of the slope formula to calculate height/y-value of the pixel to be drawn on the map based on the x
    HSLAPixel & pixel = pic.getPixel(i, j); //accesses pixel
    pixel = HSLAPixel(saturation,1,0.5,1); //changes pixel color to draw the line
  }
  return;
}

//almost the same as drawRoute but is used to draw shortest path which uses a set color rather than color based on distance
void Graph::drawPath(std::vector<Airport> airports){
  if(airports.size() > 1){
  for(size_t i = 0; i < airports.size()-1;i++){ //iterates through vector and draws all the edges of the path
    Airport& a1 = airports[i]; //gets the two airports
    Airport& a2 = airports[i+1];
    int x1,x2,y1,y2,dx,dy;
  
    //initializes variables so that the airport with the larger x coordinate is stored in x2 and y2
    if(a1.getX() < a2.getX()){ 
      x1 = a1.getX();
      x2 = a2.getX();
      y1 = a1.getY();
      y2 = a2.getY();
    }
    else{
      x1 = a2.getX();
      x2 = a1.getX();
      y1 = a2.getY();
      y2 = a1.getY();
    }

    dx = x2 - x1; //calculates difference in x
    dy = y2 - y1; //calculates difference in y
    int j;
    for(int i = x1; i < x2; i++){ //iterates through all the pixels in the horizantal range of the line
      j = y1 + dy*(i - x1) / dx; //uses a form of the slope formula to calculate height/y-value of the pixel to be drawn on the map based on the x
      HSLAPixel & pixel = map.getPixel(i, j); //accesses pixel
      pixel = HSLAPixel(240,1,0.5,1); //changes pixel color to draw the line
    }
  }
  }
  return;
}



void Graph::drawAirport(Airport& airport, PNG& pic){
  unsigned width = pic.width();
  unsigned height = pic.height();
  int x = airport.getX(); //gets coordinates of the airport
  int y = airport.getY();
  if(y > (int)height || y < 0 || x > (int)width || x < 0){ //if the airport's coordinates are outside the range of the map, prints an error and returns
    cout<<airport.getName()<<" has invalid coordinates and will not be mapped."<<endl;
    return;
  }

  double radius = 0.5 * log(airport.getSize()) + 2; //the radius of the airport increases logarithmically based on the number of incoming flights to it; it is a logarathmic increase so that a massive airport doesnt just cover the map

  //series of if-else statements calculate the range of pixels in the PNG to iterate through, this allows us to not have to iterate through the whole PNG for each vertex drawn
  unsigned leftbound,rightbound,upperbound,lowerbound;
  if(x - radius -1 > 0)
    leftbound = x - radius -1;
  else 
    leftbound = 0;
  
  if(x + radius + 1 < width)
    rightbound = x + radius +1;
  else 
    rightbound = width;

  if(y - radius -1 > 0)
    lowerbound = y - radius -1;
  else 
    lowerbound = 0;
  
  if(y + radius + 1 < height)
    upperbound = y + radius +1;
  else 
    upperbound = height;
  
  for (unsigned i = leftbound; i < rightbound; i++) //iterates through x range of pixels
  {
    for (unsigned j = lowerbound; j < upperbound; j++) //iterates through y range of pixels
    {
      HSLAPixel & pixel = pic.getPixel(i, j); //creates reference to pixel
      double distance = sqrt((x - i) * (x -i) + (y - j) * (y - j)); //calculates Euclidean distance from center
      if(distance < radius){ //if the distance is within the radius(size of airport), color that pixel
        pixel = HSLAPixel(240,1,0.5,1);
      }
    }
  }
}


//uses a breadth first traversal to cover the entire graph and print all airports stored in the graph in the order they are traversed
std::vector<int> Graph::graphToFile(std::string& filename){ 
  std::vector<int> output;
  std::vector<bool> visited(maxID + 1, false);

  for(size_t i = 0; i < visited.size();i++){ //loops through all airportIDs to make sure that BFS is called for parts of the graph that are disconnected from the rest
    if(!visited[i]){
      BreadthFirstTraversal(visited, output, i); //calls bfs traversal on node i and passes in visited boolean array and the vector to store the output in
    }
  }
  //outputs Breadth First Traversal to file with the name and ID of each airport on a seperate line
  std::ofstream MyFile(filename);
    //cout<<output.size();
    for(int airportID : output){
      MyFile<<airportMap.at(airportID).getName()<<" (" << airportID << ")"<<std::endl;
    }
  
  
  MyFile.close();

  return output; //returns vector of airportID's traversed, mainly used for testing
}

//traversal to acess all airports(vertices) in the graph, stores the airportID's in the inputted path vector
void Graph::BreadthFirstTraversal(std::vector<bool>& visited,std::vector<int>& path, int AirportID){
  std::queue<int> q; //queue for bfs
  int current;
  
  if(airportMap.find(AirportID) != airportMap.end()){ //makes sure that the inputted vertice to start at actually exists
    q.push(AirportID); //adds vertice to queue
    visited[AirportID] = true; //marks airport as visited
    while(!q.empty()){ //iterates until queue is empty
      current = q.front(); //gets next airport from queue
      path.push_back(current); //stores airport into vector 
      q.pop();
      if(routeList.find(current) != routeList.end()){ //iterates through the current airport's adjacency list
        for(auto route : routeList.at(current)){ 
          if(!visited[route.dest]) //if one of the adjacent airports hasnt yet been visited, adds it to the queue
            q.push(route.dest);
          //cout<<"CHECK 3"<<endl;
          visited[route.dest] = true;
        }
      }
    }
  }
}

//BFS that returns the path with the shortest number of flights between the starting and ending airport
std::vector<Airport> Graph::BFS(Airport startNode, Airport endNode) {

  std::vector<Airport> path;
  std::vector<int> prevArray(maxID + 1); //should we initialize this all to a certain value or does that not matter?
  std::vector<bool> visited(maxID + 1, false);
  
  
  Airport backTrackNode = startNode;
  Airport currentNode = startNode;
  std::queue<Airport> q; //queue for bfs

  q.push(startNode); 
  visited.at(startNode.getID()) = true;

  while (!q.empty()) {
    backTrackNode = currentNode;
    currentNode = q.front();
    q.pop();
    if (currentNode.getID() == endNode.getID()) {
      //backtrack using prev node to get path and push in vector 
      path.push_back(currentNode);
      while (currentNode.getID() != startNode.getID()) {
        currentNode = airportMap.at(prevArray.at(currentNode.getID()));
        path.push_back(currentNode);
      }
      //currentNode = airportMap.at(prevArray.at(currentNode.getID()));
      std::reverse(path.begin(),path.end());
      break;
      
    } else {
      //add all not visited neighbors
      if(routeList.find(currentNode.getID()) != routeList.end()){
        vector<Routes> neighbors = routeList.at(currentNode.getID());
    
        for (Routes neighbor : neighbors) {
          Airport& next = airportMap.at(neighbor.dest);
          if (visited[next.getID()] == false) {
            q.push(next);
            visited[next.getID()] = true;
            prevArray.at(next.getID()) = currentNode.getID();
          }
        }
      }
    }
  }
  return path;
}

//wrapper that takes user input to call BFS to find shortest path
std::vector<Airport> Graph::findPath(){
  //get user input to find the start airport
  cout<<"Please enter your starting city: ";
  string city;
  std::getline(std::cin,city);
  cout<<city<<endl;
  if(cities.find(city) == cities.end()){
    cout<<"Invalid City"<<endl;
    return std::vector<Airport>();
  }
  std::vector<int> airportList = cities.at(city);
  for(size_t i = 0; i < airportList.size(); i++){
    cout<<i<<" - "<<airportMap.at(airportList[i]).getName()<<endl;
  }

  cout<<"Please select your starting airport (type in number from list): "<<endl;
  string name;
  std::getline(std::cin,name);
  int airport = std::stoi(name);
  int start = airportList[airport];

  //get user input to find second airport
  cout<<"Please enter your destination city: ";
  string city2;
  std::getline(std::cin,city2);
  cout<<city2<<endl;
  if(cities.find(city2) == cities.end()){
    cout<<"Invalid City"<<endl;
    return std::vector<Airport>();
  }
  airportList = cities.at(city2);
  for(size_t i = 0; i < airportList.size(); i++){
    cout<<i<<" - "<<airportMap.at(airportList[i]).getName()<<endl;
  }
  
  cout<<"Please select your destination airport (type in number from list): "<<endl;
  std::getline(std::cin,name);
  airport = std::stoi(name);
  int end = airportList[airport];

  //calls BFS using the starting and ending airports
  std::vector<Airport> path = BFS(airportMap.at(start),airportMap.at(end));
  if(path.empty()){
    cout<<"No routes were found"<<endl; //returns empty vector if no paths were found to destination
    return path;
  }
  cout<<"The shortest route has "<< path.size() - 1<< " flights."<<endl; //otherwise outputs the shortest path and returns it as a vector as well
  cout<<"The route with the shortest number of flights is: ";
  for(size_t i = 0; i < path.size()-1; i++){
    cout<<path[i].getName()<<" -> ";
  }
  cout<<path[path.size()-1].getName()<<endl<<endl;

  return path;
}

//used for testing to input start and end airportID's for BFS
std::vector<Airport> Graph::findPath(int start, int end){
  return BFS(airportMap.at(start),airportMap.at(end)); 
}