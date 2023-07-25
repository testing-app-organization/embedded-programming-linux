#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <vector>
#include "node.h"
#include <string>

void printAirplaneFlights(vector<Node*>& arr, const string& airplane);
void printAirplaneArrivalFlights(vector<Node*>& arr, const string& airport);
vector<Node*> airplaneFlights(const string& icao_name, vector<Node*>& arr);

#endif