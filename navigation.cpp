#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <limits.h>

using namespace std;

// simple structure to store x and y coordinates of each location
struct Location {
    int x, y;
    
    // default constructor - sets coordinates to 0,0
    Location() {
        x = 0;
        y = 0;
    }
    
    // constructor with parameters - sets coordinates to given values
    Location(int x_val, int y_val) {
        x = x_val;
        y = y_val;
    }
};

// structure to represent a connection between two locations
struct Connection {
    string destination;  // name of the destination location
    int distance;        // distance to that destination
    
    // constructor to create a connection with destination and distance
    Connection(string dest, int dist) {
        destination = dest;
        distance = dist;
    }
};

class CampusNavigator {
private:
    // dynamic arrays to store all our location data
    vector<string> locationNames;     // stores names of all locations
    vector<Location> locationCoords;  // stores x,y coordinates for each location
    vector<vector<Connection> > adjacencyList;  // stores all connections between locations
    
    // helper function to find the index of a location by its name
    int findLocationIndex(const string& locationName) {
        // loop through all location names to find a match
        for (int i = 0; i < locationNames.size(); i++) {
            if (locationNames[i] == locationName) {
                return i;  // return the index if found
            }
        }
        return -1; // return -1 if not found
    }
    
    // calculate straight-line distance between two locations using pythagoras theorem
    int calculateDistance(const string& from, const string& to) {
        int fromIndex = findLocationIndex(from);
        int toIndex = findLocationIndex(to);
        
        // check if both locations exist
        if (fromIndex == -1 || toIndex == -1) {
            return 0;  // return 0 if either location doesn't exist
        }
        
        // get coordinates of both locations
        Location fromPos = locationCoords[fromIndex];
        Location toPos = locationCoords[toIndex];
        
        // calculate differences in x and y coordinates
        int dx = toPos.x - fromPos.x;
        int dy = toPos.y - fromPos.y;
        
        // use pythagoras theorem: distance = sqrt(dx^2 + dy^2)
        return (int)sqrt(dx * dx + dy * dy);
    }

public:
    // constructor - automatically sets up all locations and connections when object is created
    CampusNavigator() {
        initializeLocations();  // first add all locations
        buildGraph();          // then create all connections
    }
    
    // function to add all campus locations with their coordinates
    void initializeLocations() {
        // add each location name and its coordinates
        // coordinates are based on a campus map where (0,0) is top-left corner
        
        locationNames.push_back("N Block");
        locationCoords.push_back(Location(220, 300));
        
        locationNames.push_back("Faculty Block");
        locationCoords.push_back(Location(380, 200));
        
        locationNames.push_back("Chemical Engineering Block");
        locationCoords.push_back(Location(830, 690));
        
        locationNames.push_back("D Block");
        locationCoords.push_back(Location(500, 550));
        
        locationNames.push_back("Electrical Engineering Block");
        locationCoords.push_back(Location(500, 750));
        
        locationNames.push_back("C Block");
        locationCoords.push_back(Location(500, 620));
        
        locationNames.push_back("K Block");
        locationCoords.push_back(Location(1000, 740));
        
        locationNames.push_back("Architecture and Design Department");
        locationCoords.push_back(Location(870, 250));
        
        locationNames.push_back("Physics Department");
        locationCoords.push_back(Location(500, 850));
        
        locationNames.push_back("Pharmacy Department");
        locationCoords.push_back(Location(360, 300));
        
        locationNames.push_back("Chemical Labs");
        locationCoords.push_back(Location(1000, 850));
        
        locationNames.push_back("H Block");
        locationCoords.push_back(Location(700, 575));
        
        locationNames.push_back("IT Center");
        locationCoords.push_back(Location(700, 660));
        
        locationNames.push_back("Interdisciplinary Research Centre");
        locationCoords.push_back(Location(850, 175));
        
        locationNames.push_back("Virtual University");
        locationCoords.push_back(Location(320, 690));
        
        locationNames.push_back("Baradari");
        locationCoords.push_back(Location(340, 850));
        
        locationNames.push_back("Mosque");
        locationCoords.push_back(Location(550, 250));
        
        locationNames.push_back("Tuck Shop");
        locationCoords.push_back(Location(900, 580));
        
        locationNames.push_back("Student Services Center");
        locationCoords.push_back(Location(130, 430));
        
        locationNames.push_back("Football Ground");
        locationCoords.push_back(Location(830, 1000));
        
        locationNames.push_back("Cricket Ground");
        locationCoords.push_back(Location(250, 1000));
        
        locationNames.push_back("Sports Complex & Gym");
        locationCoords.push_back(Location(290, 550));
        
        locationNames.push_back("Faculty Parking");
        locationCoords.push_back(Location(700, 480));
        
        locationNames.push_back("Parking Gate 2");
        locationCoords.push_back(Location(0, 1000));
        
        locationNames.push_back("Parking Gate 3");
        locationCoords.push_back(Location(380, 100));
        
        locationNames.push_back("Cafe");
        locationCoords.push_back(Location(0, 450));
        
        locationNames.push_back("Gate 3");
        locationCoords.push_back(Location(500, 0));
        
        locationNames.push_back("Gate 2");
        locationCoords.push_back(Location(140, 1100));
        
        locationNames.push_back("O Block");
        locationCoords.push_back(Location(380, 450));
        
        locationNames.push_back("Basketball & Badminton Court");
        locationCoords.push_back(Location(700, 250));
        
        locationNames.push_back("Pharmacy Block");
        locationCoords.push_back(Location(830, 780));
        
        locationNames.push_back("Library");
        locationCoords.push_back(Location(770, 850));
        
        // resize the adjacency list to match the number of locations
        // this creates empty connection lists for each location
        adjacencyList.resize(locationNames.size());
    }
    
    // function to add a bidirectional connection between two locations
    void addConnection(const string& from, const string& to) {
        // find the index numbers for both locations
        int fromIndex = findLocationIndex(from);
        int toIndex = findLocationIndex(to);
        
        // check if both locations exist
        if (fromIndex != -1 && toIndex != -1) {
            // calculate the distance between these two locations
            int distance = calculateDistance(from, to);
            
            // add connection from first location to second
            adjacencyList[fromIndex].push_back(Connection(to, distance));
            // add connection from second location to first (bidirectional)
            adjacencyList[toIndex].push_back(Connection(from, distance));
        }
    }
    
    // function to create all connections between campus locations
    void buildGraph() {
        // define all the walkable paths between locations on campus
        // each connection represents a direct path between two locations
        
        addConnection("N Block", "Faculty Block");
        addConnection("N Block", "O Block");
        addConnection("N Block", "Student Services Center");
        addConnection("Faculty Block", "Pharmacy Department");
        addConnection("Faculty Block", "Mosque");
        addConnection("Faculty Block", "Parking Gate 3");
        addConnection("D Block", "C Block");
        addConnection("D Block", "Sports Complex & Gym");
        addConnection("D Block", "O Block");
        addConnection("C Block", "Electrical Engineering Block");
        addConnection("C Block", "H Block");
        addConnection("O Block", "Sports Complex & Gym");
        addConnection("O Block", "Pharmacy Department");
        addConnection("Chemical Engineering Block", "K Block");
        addConnection("Chemical Engineering Block", "Pharmacy Block");
        addConnection("K Block", "Chemical Labs");
        addConnection("K Block", "Tuck Shop");
        addConnection("Electrical Engineering Block", "Physics Department");
        addConnection("H Block", "IT Center");
        addConnection("H Block", "Faculty Parking");
        addConnection("H Block", "Tuck Shop");
        addConnection("IT Center", "Chemical Engineering Block");
        addConnection("Architecture and Design Department", "Interdisciplinary Research Centre");
        addConnection("Architecture and Design Department", "Basketball & Badminton Court");
        addConnection("Architecture and Design Department", "Tuck Shop");
        addConnection("Interdisciplinary Research Centre", "Basketball & Badminton Court");
        addConnection("Interdisciplinary Research Centre", "Mosque");
        addConnection("Basketball & Badminton Court", "Faculty Parking");
        addConnection("Basketball & Badminton Court", "Mosque");
        addConnection("Physics Department", "Baradari");
        addConnection("Physics Department", "Virtual University");
        addConnection("Virtual University", "Sports Complex & Gym");
        addConnection("Virtual University", "Cricket Ground");
        addConnection("Baradari", "Library");
        addConnection("Library", "Chemical Labs");
        addConnection("Library", "Pharmacy Block");
        addConnection("Pharmacy Block", "Chemical Labs");
        addConnection("Pharmacy Block", "Football Ground");
        addConnection("Baradari", "Physics Department");
        addConnection("Football Ground", "Cricket Ground");
        addConnection("Cricket Ground", "Sports Complex & Gym");
        addConnection("Sports Complex & Gym", "Student Services Center");
        addConnection("Gate 3", "Mosque");
        addConnection("Gate 3", "Faculty Block");
        addConnection("Gate 3", "Basketball & Badminton Court");
        addConnection("Gate 2", "Cricket Ground");
        addConnection("Gate 2", "Baradari");
        addConnection("Parking Gate 2", "Cricket Ground");
        addConnection("Parking Gate 2", "Gate 2");
        addConnection("Parking Gate 3", "Gate 3");
        addConnection("Cafe", "Student Services Center");
        addConnection("Cafe", "Parking Gate 2");
        addConnection("Faculty Parking", "Faculty Block");
        addConnection("Library", "Football Ground");
        addConnection("Library", "Physics Department");
        addConnection("Pharmacy Block", "Electrical Engineering Block");
        addConnection("Pharmacy Block", "IT Center");
        addConnection("IT Center", "Pharmacy Block");
        addConnection("Chemical Labs", "Football Ground");
        addConnection("Chemical Labs", "Library");
        addConnection("Pharmacy Department", "Student Services Center");
        addConnection("Library", "Tuck Shop");
        addConnection("Chemical Labs", "Tuck Shop");
        addConnection("Pharmacy Block", "Library");
        addConnection("Faculty Parking", "IT Center");
        addConnection("Architecture and Design Department", "Faculty Parking");
    }
    
    // dijkstra's algorithm - finds the shortest path by distance
    vector<string> dijkstraPath(const string& start, const string& end) {
        // find index numbers for start and end locations
        int startIndex = findLocationIndex(start);
        int endIndex = findLocationIndex(end);
        
        // check if both locations exist
        if (startIndex == -1 || endIndex == -1) {
            return vector<string>(); // return empty path if locations not found
        }
        
        int numLocations = locationNames.size();
        
        // create arrays to store algorithm data
        vector<int> distance(numLocations, INT_MAX);  // shortest distance to each location
        vector<int> previous(numLocations, -1);       // previous location in shortest path
        vector<bool> visited(numLocations, false);    // whether we've processed this location
        
        // distance to start location is 0
        distance[startIndex] = 0;
        
        // main dijkstra loop - process each location once
        for (int count = 0; count < numLocations - 1; count++) {
            // find the unvisited location with minimum distance
            int minDistance = INT_MAX;
            int minIndex = -1;
            
            for (int v = 0; v < numLocations; v++) {
                if (!visited[v] && distance[v] < minDistance) {
                    minDistance = distance[v];
                    minIndex = v;
                }
            }
            
            // if no reachable location found, break
            if (minIndex == -1) {
                break;
            }
            
            // mark this location as visited
            visited[minIndex] = true;
            
            // if we reached destination, we can stop
            if (minIndex == endIndex) {
                break;
            }
            
            // update distances to all neighbors of current location
            for (int i = 0; i < adjacencyList[minIndex].size(); i++) {
                Connection connection = adjacencyList[minIndex][i];
                int neighborIndex = findLocationIndex(connection.destination);
                
                // check if neighbor exists and hasn't been visited
                if (neighborIndex != -1 && !visited[neighborIndex]) {
                    // calculate new distance through current location
                    int newDistance = distance[minIndex] + connection.distance;
                    
                    // if this path is shorter, update the distance and previous location
                    if (newDistance < distance[neighborIndex]) {
                        distance[neighborIndex] = newDistance;
                        previous[neighborIndex] = minIndex;
                    }
                }
            }
        }
        
        // reconstruct the path by following previous pointers backwards
        vector<string> path;
        int current = endIndex;
        
        // trace back from end to start using previous array
        while (current != -1) {
            path.push_back(locationNames[current]);
            current = previous[current];
        }
        
        // check if we found a valid path
        if (path.empty() || path.back() != start) {
            return vector<string>(); // return empty if no path found
        }
        
        // reverse the path since we built it backwards
        reverse(path.begin(), path.end());
        return path;
    }
    
    // bfs algorithm - finds path with minimum number of steps (locations)
    vector<string> bfsPath(const string& start, const string& end) {
        // find index numbers for start and end locations
        int startIndex = findLocationIndex(start);
        int endIndex = findLocationIndex(end);
        
        // check if both locations exist
        if (startIndex == -1 || endIndex == -1) {
            return vector<string>(); // return empty path if locations not found
        }
        
        int numLocations = locationNames.size();
        
        // create arrays for bfs algorithm
        vector<bool> visited(numLocations, false);  // track which locations we've seen
        vector<int> previous(numLocations, -1);     // track how we got to each location
        queue<int> q;  // queue to store locations to visit next
        
        // start bfs from the starting location
        visited[startIndex] = true;
        q.push(startIndex);
        
        // main bfs loop - explore locations level by level
        while (!q.empty()) {
            int current = q.front();  // get next location to process
            q.pop();  // remove it from queue
            
            // if we reached destination, we can stop
            if (current == endIndex) {
                break;
            }
            
            // visit all neighbors of current location
            for (int i = 0; i < adjacencyList[current].size(); i++) {
                Connection connection = adjacencyList[current][i];
                int neighborIndex = findLocationIndex(connection.destination);
                
                // if neighbor exists and hasn't been visited yet
                if (neighborIndex != -1 && !visited[neighborIndex]) {
                    visited[neighborIndex] = true;    // mark as visited
                    previous[neighborIndex] = current; // remember how we got here
                    q.push(neighborIndex);            // add to queue for future processing
                }
            }
        }
        
        // reconstruct the path by following previous pointers backwards
        vector<string> path;
        int current = endIndex;
        
        // trace back from end to start using previous array
        while (current != -1) {
            path.push_back(locationNames[current]);
            current = previous[current];
        }
        
        // check if we found a valid path
        if (path.empty() || path.back() != start) {
            return vector<string>(); // return empty if no path found
        }
        
        // reverse the path since we built it backwards
        reverse(path.begin(), path.end());
        return path;
    }
    
    // calculate total distance of a given path
    int getPathDistance(const vector<string>& path) {
        int totalDistance = 0;
        
        // go through each consecutive pair of locations in the path
        for (int i = 0; i < path.size() - 1; i++) {
            string currentLocation = path[i];
            string nextLocation = path[i + 1];
            int currentIndex = findLocationIndex(currentLocation);
            
            // find the connection from current to next location
            if (currentIndex != -1) {
                // look through all connections from current location
                for (int j = 0; j < adjacencyList[currentIndex].size(); j++) {
                    Connection connection = adjacencyList[currentIndex][j];
                    // if this connection goes to our next location
                    if (connection.destination == nextLocation) {
                        totalDistance = totalDistance + connection.distance;
                        break; // found the connection, no need to keep looking
                    }
                }
            }
        }
        
        return totalDistance;
    }
    
    // function to print the path in a readable format to terminal
    void printPath(const vector<string>& path, const string& algorithm, int distance) {
        // check if path is empty
        if (path.empty()) {
            cerr << "No path found!" << endl;
            return;
        }
        
        // print algorithm used and total distance
        cerr << "Algorithm used: " << algorithm << endl;
        cerr << "Total distance: " << distance << " units" << endl;
        cerr << "Path: ";
        
        // print each location in the path connected with arrows
        for (int i = 0; i < path.size(); i++) {
            cerr << path[i];
            // add arrow after each location except the last one
            if (i < path.size() - 1) {
                cerr << " -> ";
            }
        }
        cerr << endl;  // add new line at the end
    }

    // generate json output containing all locations and their coordinates
    // json is a text format that websites can easily read and understand
    string getLocationsJSON() {
        stringstream ss;  // stringstream helps us build strings piece by piece
        ss << "{\"locations\":[";
        
        // create a copy of location names and sort them alphabetically
        vector<string> sortedLocations = locationNames;
        sort(sortedLocations.begin(), sortedLocations.end());
        
        // add all location names to json
        for (int i = 0; i < sortedLocations.size(); i++) {
            ss << "\"" << sortedLocations[i] << "\"";
            // add comma between items except after the last one
            if (i < sortedLocations.size() - 1) {
                ss << ",";
            }
        }
        ss << "],\"coordinates\":{";
        
        // add coordinates for each location
        for (int i = 0; i < locationNames.size(); i++) {
            // add comma before each item except the first one
            if (i > 0) {
                ss << ",";
            }
            // add location name and its x,y coordinates
            ss << "\"" << locationNames[i] << "\":{\"x\":" << locationCoords[i].x << ",\"y\":" << locationCoords[i].y << "}";
        }
        ss << "}}";
        return ss.str();  // convert stringstream to regular string
    }
    
    // generate json output for a path with algorithm info and distance
    string getPathJSON(const vector<string>& path, const string& algorithm, int distance) {
        stringstream ss;  // stringstream helps us build strings piece by piece
        
        // start building json with algorithm type and total distance
        ss << "{\"algorithm\":\"" << algorithm << "\",\"distance\":" << distance << ",\"path\":[";
        
        // add all location names in the path
        for (int i = 0; i < path.size(); i++) {
            ss << "\"" << path[i] << "\"";
            // add comma between items except after the last one
            if (i < path.size() - 1) {
                ss << ",";
            }
        }
        ss << "],\"coordinates\":[";
        
        // add coordinates for each location in the path
        for (int i = 0; i < path.size(); i++) {
            int locationIndex = findLocationIndex(path[i]);
            // if location exists, add its coordinates
            if (locationIndex != -1) {
                Location coord = locationCoords[locationIndex];
                ss << "{\"x\":" << coord.x << ",\"y\":" << coord.y << "}";
                // add comma between items except after the last one
                if (i < path.size() - 1) {
                    ss << ",";
                }
            }
        }
        ss << "]}";
        return ss.str();  // convert stringstream to regular string
    }
};

// main function - this is where the program starts running
int main(int argc, char* argv[]) {
    // create a campus navigator object
    CampusNavigator nav;
    
    // if no command line arguments provided, return all locations
    if (argc == 1) {
        cout << nav.getLocationsJSON() << endl;
        return 0;
    }
    
    // check if correct number of arguments provided
    if (argc != 4) {
        cout << "{\"error\":\"Usage: program <source> <destination> <algorithm>\"}" << endl;
        return 1;
    }
    
    // get command line arguments
    string source = argv[1];      // starting location
    string destination = argv[2]; // ending location
    string algorithm = argv[3];   // which algorithm to use
    
    vector<string> path;  // will store the path we find
    
    // choose algorithm based on user input
    if (algorithm == "dijkstra") {
        // use dijkstra for shortest distance path
        path = nav.dijkstraPath(source, destination);
    } else if (algorithm == "bfs") {
        // use bfs for minimum number of steps path
        path = nav.bfsPath(source, destination);
    } else {
        // invalid algorithm specified
        cout << "{\"error\":\"Invalid algorithm. Use 'dijkstra' or 'bfs'\"}" << endl;
        return 1;
    }
    
    // check if a path was found
    if (path.empty()) {
        cout << "{\"error\":\"No path found\"}" << endl;
        return 1;
    }
    
    // additional check to make sure path is valid
    if (path.size() == 1 && path[0] != source) {
        cout << "{\"error\":\"No path found\"}" << endl;
        return 1;
    }
    
    // calculate total distance of the path
    int distance = nav.getPathDistance(path);
    
    // print the path to terminal for user to see
    nav.printPath(path, algorithm, distance);

    // output the path in json format for the frontend
    cout << nav.getPathJSON(path, algorithm, distance) << endl;
    
    return 0;  // program completed successfully
}