# tejp2-jcrowe6-mahuja3-ajithks2
# Final Project
Final Project Video on Github as "Cs225FinalProjectPresentation.mp4"
## Where to Get Data
The database we utilized is the OpenFlights database. We used their Airports database and Routes database to create the graph. These two files are included in this github repository as "airports.dat.txt" and "routes.dat.txt".

## File Input Formatting
There are two files that must be inputted, the list of airports and the list of routes. Both of these have their own specific formatting.

#### Airport File formatting
The airports file is a .txt file that should contain information about each airport on a seperate line with the parameters of the airport in a comma seperated list. There should not be additional commas within any of the fields. The format should be:

AirportID,"Airport Name","City","Country","IATA","ICAO",Latitude,Longitude,Altitude,TimeZone,"DST","Tz database time","type","source"

Of this, the important fields are the Airport ID, Airport Name, City, Latitude, and Longitude. The remaining fields are not used by our code but should still be included (can just be nonsensical data) in order to follow the format of the OpenFlights Database we have used. The Airport ID's used should all be positive integers that are unique as they will be used as a key to identify the airports. Below is an example of 4 airports inputted with proper formatting(Note: Each airport should take only one line but the readme file is wrapping the text):


3077,"Hong Kong International Airport","Hong Kong","Hong Kong","HKG","VHHH",22.308901,113.915001,28,8,"U","Asia/Hong_Kong","airport","OurAirports"\
3797,"John F Kennedy International Airport","New York","United States","JFK","KJFK",40.63980103,-73.77890015,13,-5,"A","America/New_York","airport","OurAirports"\
507,"London Heathrow Airport","London","United Kingdom","LHR","EGLL",51.4706,-0.461941,83,0,"E","Europe/London","airport","OurAirports"\
3093,"Indira Gandhi International Airport","Delhi","India","DEL","VIDP",28.5665,77.103104,777,5.5,"N","Asia/Calcutta","airport","OurAirports"


#### Routes File formatting
The routes file is a .txt file that contains information about each route in a comma seperated list with each route on a seperate line. The format should be:

Airline,AirlineID,SourceAirport,SourceAirportID,DestinationAirport,DestinationAirportID,Codeshare,Stops,Equipment

Only the SourceAirportID and DestinationAirportID are important to us but the others should be included for the sake of matching the OpenFlights Database. The SourceAirportID and DestinationAirportID should match the unique Airport ID of the airport as written in the Airport file. Each route will only be added if the Source and Destination airports exist in the graph (which is determined by the airports file).

An example of some correctly formatted routes is below:

2B,410,KGD,2952,EGO,6156,,0,CR2\
2P,897,BSO,6019,MNL,2397,,0,DH4\
5Q,18232,AEP,2442,MVD,2816,,0,AT7\
9E,3976,JFK,3797,MSY,3861,,0,CR9

## Compiling and Running Program

First input 'make' to create the object files for the program.

Then, you can run the program by typing:
'./main [AirportListFilename] [RouteListFilename]'

For example, with the included dataset, you would type:
'./main airports.dat.txt routes.dat.txt'


This will start the program, which will parse the files to create the graph structure. It will then give a series of prompts asking for information in order to do a BFS to find the shortest number of flights from one airport to another. It will first ask for the starting city and provide a list of airports within that city. You can then select the airport by inputting the number that is listed next to the city you would like to start at. It will similarly get information for the destination airport.

Using this information, it will find the shortest path (in terms of number of flights) between the airport. It will draw this route onto a map which will be stored in "ShortestRoute.png". (Warning: The line algorithm we used to draw edges does not handle vertical lines very well. As a result if two airports in the path are directly on top of each other it may fail to draw a visible line). This shortest path will also be outputted to the console.

The program will then project the entire graph structure created onto the map, storing it in "OutputMap.png". For this map, the airports increases in size based on the number of incoming flights to that airport and the routes' colors range from green to red based on the distance of the flight (with green being the shortest and red the longest).

Finally, the program does a Breadth First Traversal of the entire graph and writes all of the airport names into the file "GraphAirportList.txt".

#### Compiling and Running Tests
To run the tests, simply do 'make test' and then './test'


