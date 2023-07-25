#ifndef NODE_H
#define NODE_H

#include <fstream>
#include <string>
using namespace std;

class Node
{
private:
    int firstSeen, lastSeen;
    string icao24, estDepartureAirport, estArrivalAirport, callSign;
public:
    int getFirstSeen() const {return firstSeen;}
    int getLastSeen() const {return lastSeen;}
    string& getIcao24() {return icao24;}
    string& getEstDepartureAirport() {return estDepartureAirport;}
    string& getEstArrivalAirport() {return estArrivalAirport;}
    string& getCallSign() {return callSign;}

    void setIcao24(string icao) {this->icao24 = icao;}
    void setFirstSeen(int firstSeen) {this->firstSeen = firstSeen;}
    void setLastSeen(int lastSeen) {this->lastSeen = lastSeen;}
    void setEstDepartureAirport(string departueAirport) {this->estDepartureAirport = departueAirport;}
    void setEstArrivalAirport(string arrivalAirport) {this->estArrivalAirport = arrivalAirport;}
    void setCallSign(string callSign) {this->callSign = callSign;}

    friend istream& operator>>(istream& in, Node& node)
    {
        char d; // delimiter
        getline(in, node.icao24, ',');
        in >> node.firstSeen >> d;
        getline(in, node.estDepartureAirport, ',');
        in >> node.lastSeen >> d;
        getline(in, node.estArrivalAirport, ',');
        getline(in, node.callSign, '\n');
        return in;
    }
};
#endif