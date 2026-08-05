#pragma once
#include <string>
#include <vector>
#include <algorithm>
class Map {
    std::string location = "Gorkha Palace";
    std::vector<std::string> discovered{"Gorkha Palace"};
public:
    const std::string& getLocation() const { return location; }
    void setLocation(const std::string& value) { location=value; if(std::find(discovered.begin(),discovered.end(),value)==discovered.end()) discovered.push_back(value); }
    const std::vector<std::string>& getDiscoveredLocations() const { return discovered; }
};
