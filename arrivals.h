#ifndef ARRIVALS_H
#define ARRIVALS_H

#include <vector>
#include "node.h"
#include <string>

void printArrivals(vector<Node*>& arr, string icao_name);
vector<Node*> arrivals(string icao, vector<Node*>& arr);

#endif