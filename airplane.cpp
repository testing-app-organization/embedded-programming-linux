#include <iostream>
#include "myLibrary.h"
#include "airplane.h"

void printAirplaneFlights(vector<Node *> &arr, const string &airplane) {
    if (arr.empty()) {
        cout << "There is no info about aircraft " << airplane << " in db." << endl;
    }
    else
    {
        int size = (int) arr.size();
        cout << airplane << ":" << endl;
        for (int i = 0; i < size; i++)
            cout << arr[i]->getIcao24() << " departed from " << arr[i]->getEstDepartureAirport() <<
                " at " << convertEpochToReadable(arr[i]->getFirstSeen()) << " arrived in "
                << arr[i]->getEstArrivalAirport() <<
                " at " << convertEpochToReadable(arr[i]->getLastSeen()) << endl;
    }
}

void printAirplaneArrivalFlights(vector<Node *> &arr, const string &airport) {
    if (arr.empty()) {
        cout << "There is no info about airport " << airport << " in db." << endl;
    }
    else
    {
        int size = (int) arr.size();
        cout << airport << ":" << endl;
        for (int i = 0; i < size; i++) {
            cout << "FLight #" << arr[i]->getCallSign() << " Arriving from " << arr[i]->getEstDepartureAirport() 
            << ", tookoff at " << convertEpochToReadable(arr[i]->getFirstSeen()) << " landed at " << convertEpochToReadable(arr[i]->getLastSeen()) << endl;
        }
    }
}

vector<Node *> airplaneFlights(const string &icao_name, vector<Node *> &arr) {
    vector<Node *> flightsByAircraft = get_flights_by_aircraft(icao_name, arr);
    return flightsByAircraft;
}