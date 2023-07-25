#ifndef MYLIBRARY_H
#define MYLIBRARY_H

#include <vector>
#include "node.h"
#include <string>
#include <ctime>

vector<Node*>  loadDatabase();

void fetchAirportsData(const vector<string>& icao_names);

vector<Node*> get_flights_to_airport(string icao , vector<Node*>& arr);

bool thereExistsAZipFile(const string& zipName);

vector<Node*> get_flights_from_airport(string icao , vector<Node*>& arr);


vector<Node*> get_flights_by_aircraft(string aircraft , vector<Node*>& arr);

void freeArr(vector<Node *>& arr);

string convertEpochToReadable(const time_t epoch_time);

#endif