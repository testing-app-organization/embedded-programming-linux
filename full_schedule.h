#ifndef FULLSCHEDULE_H
#define FULLSCHEDULE_H

#include <vector>
#include "node.h"
#include <string>

void printFullSchedule(vector<Node*>& arr, string icao);
vector<Node*> full_schedule(string icao, vector<Node*>& arr);

#endif