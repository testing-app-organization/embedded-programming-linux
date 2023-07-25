#include <iostream>
#include "myLibrary.h"
#include "arrivals.h"

void printArrivals(vector<Node*>& arr, string icao_name)
{
    int size = arr.size();
    cout << icao_name << ":" << endl;
    for (int i = 0; i < size; i++)
        cout << "FLight #" << arr[i]->getCallSign() << " Arriving from " << arr[i]->getEstDepartureAirport() 
        << ", tookoff at " << convertEpochToReadable(arr[i]->getFirstSeen()) << " landed at " << convertEpochToReadable(arr[i]->getLastSeen()) << endl;
}

vector<Node*> arrivals(string icao, vector<Node*>& arr)
{   
    vector<Node*> arrivalsInfo = get_flights_to_airport(icao, arr);
    return arrivalsInfo;
}