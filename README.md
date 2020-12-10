# tejp2-jcrowe6-mahuja3-ajithks2
# Final Project

## File Input Formatting
There are two files that must be inputted, the list of airports and the list of routes. Both of these have their own specific formatting.

### Airport File formatting
The airports file should contain information about each airport on a seperate line with the parameters of the airport in a comma seperated list. The format should be:

AirportID,"Airport Name","City","Country","IATA","ICAO",Latitude,Longitude,Altitude,TimeZone,"DST","Tz database time","type","source"

Of this, the important fields are the Airport ID, Airport Name, City, Latitude, and Longitude. The remaining fields are not used by our code but should still be included (can just be nonsensical data) in order to follow the format of the OpenFlights Database we have used. The Airport ID's used should all be positive integers that are unique as they will be used as a key to identify the airports. Below is an example of 4 airports inputted with proper formatting:


3077,"Hong Kong International Airport","Hong Kong","Hong Kong","HKG","VHHH",22.308901,113.915001,28,8,"U","Asia/Hong_Kong","airport","OurAirports"
3797,"John F Kennedy International Airport","New York","United States","JFK","KJFK",40.63980103,-73.77890015,13,-5,"A","America/New_York","airport","OurAirports"
507,"London Heathrow Airport","London","United Kingdom","LHR","EGLL",51.4706,-0.461941,83,0,"E","Europe/London","airport","OurAirports"
3093,"Indira Gandhi International Airport","Delhi","India","DEL","VIDP",28.5665,77.103104,777,5.5,"N","Asia/Calcutta","airport","OurAirports"

