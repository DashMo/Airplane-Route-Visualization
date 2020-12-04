#include "graph.h"
#include <fstream>
#include <vector>
#include <iostream>
#include "cs225/HSLAPixel.h"
#include <cmath>
using std::vector;
using std::cout;
using std::endl;
using cs225::HSLAPixel;
using std::ifstream;
Graph::Graph(string airportList, string routesList, string mapname){
    
  map.readFromFile(mapname); //stores mercator map into graph class
  
  ifstream airports(airportList); //opens file
  string line; //will hold each line read
  string word; //will hold each word parsed from the line
  int count = 0;
  
  while(getline(airports,line) && count < 100000){ //will keep iterating until all the lines are read 
    std::istringstream ss(line); //stringsream to parse line read
    vector<string> row; //vector will hold seperated data of the line
    while(getline(ss, word, ',')) { //gets each word in the line (they are comma seperated) and stores in vector
      row.push_back(word);
    }
    // for(auto x : row)
    //   cout<<x<<"  ";
    // cout<<endl<<endl;
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
    cout<<airportID<<" "<<airportName<<" "<<airportCity<<" "<<lat<<" "<<lon<<endl<<endl;
    count++;

    cities[airportCity].push_back(airportID); //stores airportID within the correct city
    Airport airport(lat,lon,airportName, map.width(), map.height(),airportID); //creates airport object
    airportMap.insert(std::make_pair(airportID,airport)); //stores airport object into vertex map
    // if(count < 100000){
    //     bool check = true;
    //   //bool check = drawMap(result,lat,lon);
    //   if(!check){
    //     cout<<"ERROR "<<airportID<<endl;
    //     //return;
    //   }
    // }
    // else{
    // result.writeToFile("MapOutput2.png");
    // return;
    // }
  }
  //result.writeToFile("MapOutput2.png");
  ifstream routes(routesList); //opens file
    count = 0;
    while(getline(routes,line) && count < 100000){ //will keep iterating until all the lines are read 
        std::istringstream ss(line); //stringsream to parse line read
        vector<string> row; //vector will hold seperated data of the line
        while(getline(ss, word, ',')) { //gets each word in the line (they are comma seperated) and stores in vector
            cout<<word<<" ";
            row.push_back(word);
        }
        cout<<endl;
        if(row[3]!="\\N" && row[5]!="\\N"){ //does not use entry if the entry is missing its airport ID for the source or destination airport
          int start = stoi(row[3]); //converts source airport ID to integer
          int end = stoi(row[5]); //converts destination airport ID to integer
          
          if(airportMap.find(start) != airportMap.end() && airportMap.find(end) != airportMap.end()){ //if the source and destination airports exist in the map, store the route
              Airport &begin = airportMap.at(start); //gets start and ending airports
              Airport &stop = airportMap.at(end);
              stop.increaseSize(); //increases size of airport for which the flight is incomings
              Routes path(start, end, begin.getLat(),begin.getLon(), stop.getLat(), stop.getLon()); //makes Route object (edge)
              routeList[start].push_back(path); //insert route into edgelist
          }
        }
        // for(auto x : row)
        //     cout<<x<<"  ";
        // cout<<endl<<endl;
        count++;
    }
}

PNG Graph::drawMap(){
  PNG pic = map;
  for(auto list : routeList){ //iterates through all the airports' outgoing edgelists
    for(auto route : list.second) //iterates through all the edgelist's routes
      drawRoute(route, pic); //calls drawRoute to draw edge between the two airports
  }
  for(auto airport:airportMap){
    drawAirport(airport.second, pic); //draws each airport by passing in each airport from the map
  }
  return pic;
}

void Graph::drawRoute(Routes& route, PNG& pic){
  Airport& a1 = airportMap.at(route.source);
  Airport& a2 = airportMap.at(route.dest);
  int x1,x2,y1,y2,dx,dy;
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
  dx = x2 - x1;
  dy = y2 - y1;
  int j;
  for(int i = x1; i < x2; i++){
    j = y1 + dy*(i - x1) / dx;
    HSLAPixel & pixel = pic.getPixel(i, j);
    pixel = HSLAPixel(120,1,0.5,1);
  }
  return;
}

void Graph::drawAirport(Airport& airport, PNG& pic){
  unsigned width = pic.width();
  unsigned height = pic.height();
  int x = airport.getX();
  int y = airport.getY();
  if(y > (int)height || y < 0 || x > (int)width || x < 0){
    cout<<airport.getName()<<" has invalid coordinates and will not be mapped."<<endl;
    return;
  }
  //std::cout<<width<<" "<<height<<std::endl;
  //std::cout<<x<<" "<<y<<std::endl;
  double radius = log(airport.getSize());
  //std::cout<<"CHECK2"<<std::endl;

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
  
  if(y>(int)height){
    //std::cout<<x<<" "<<y<<" "<<lat<<" "<<lon<<std::endl;
    return;
  }

  for (unsigned i = leftbound; i < rightbound; i++) 
  {
    //std::cout<<"CHECK2"<<std::endl;
    for (unsigned j = lowerbound; j < upperbound; j++) 
    {
      if(j > height){
        cout<<airport.getX()<<" "<<airport.getY()<<" "<<airport.getID()<<endl;
        return;
      }
      HSLAPixel & pixel = pic.getPixel(i, j); //creates reference to pixel
      double distance = sqrt((x - i) * (x -i) + (y - j) * (y - j)); //calculates Euclidean distance from center
      //std::cout<<distance<<std::endl;
      if(distance < radius){ //if the distance is greater than 160 pixels, set it back to 160 because the luminance does not decrease past 80%
        pixel = HSLAPixel(0,1,0.5,1);
        //std::cout<<"CHECK"<<std::endl;
      }
      //pixel.l *= (1 - distance * .005); //pixel's luminance decreased by .005 for every pixel away form the center it is
      
    }
  }
}