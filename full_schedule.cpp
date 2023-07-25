#include <iostream>
#include <fstream>
#include <algorithm>
#include "myLibrary.h"
#include "full_schedule.h"


void printFullSchedule(vector<Node*>& arr, string icao_name)
{
    if(arr.empty()){
        cout << "There is no info about airport " << icao_name << " in db." << endl;
    }
    else
    {
        cout << icao_name << ":" <<endl;
        for (int i = 0; i < arr.size() - 1; i++)
        {
            if (arr[i]->getEstDepartureAirport() == icao_name)
                cout << "FLight #" << arr[i]->getCallSign() << " departing to " << arr[i]->getEstArrivalAirport()
                << " from " << convertEpochToReadable(arr[i]->getFirstSeen()) << endl;
            else
                cout << "FLight #" << arr[i]->getCallSign() << " arriving from " << arr[i]->getEstDepartureAirport() 
                << " at " << convertEpochToReadable(arr[i]->getFirstSeen()) << endl;
        }
    }
}

vector<Node*> full_schedule(string icao, vector<Node*>& arr)
{   
    vector<Node*> flightsData = get_flights_to_airport(icao, arr);
    vector<Node*> departures = get_flights_from_airport(icao, arr);
    flightsData.insert(flightsData.end(), departures.begin(), departures.end());
    sort(flightsData.begin(), flightsData.end(), [](const Node* a, const Node* b) {
        return a->getFirstSeen() < b->getFirstSeen();
        });
    return flightsData;
}

