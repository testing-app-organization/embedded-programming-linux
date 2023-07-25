#include <fstream>
#include <filesystem>
#include "myLibrary.h"
#include <iostream>

using namespace std;
namespace fs = filesystem;

void loadFromFile(vector<Node*>& database, const string& file_path){
    ifstream file(file_path);
    if (file) {
        string firstLine;
        bool fEof = false;

        getline(file, firstLine);
        while (!fEof)
        {
            Node* pNode = new Node;
            file >> *pNode;
            database.push_back(pNode);
            if (file.eof())
            {
                fEof = true;
                continue;
            }
        }
        file.close();
    }
}

vector<Node*> loadDatabase() {
    vector<Node*> database;
    const string parent_dir = fs::current_path().parent_path().string();
    for (const auto& entry : fs::directory_iterator(parent_dir)) {
        if (entry.is_directory()) {
            const string icao_name = entry.path().filename().string();
            if (icao_name[0] == '.') { // Skip directories that start with "."
                continue;
            }

            const string dpt_file_path = entry.path() / (icao_name + ".dpt");
            const string arv_file_path = entry.path() / (icao_name + ".arv");

            loadFromFile(database, dpt_file_path);
            loadFromFile(database, arv_file_path);
        }
    }
    return database;
}

bool thereExistsAZipFile(const string& zipName)
{
    const string parent_dir = fs::current_path().string();
    for (const auto& entry : fs::directory_iterator(parent_dir)) {
        if (entry.is_directory())
        {
            continue;
        }
        const string fileName = entry.path().filename().string();
        if (fileName == zipName)
        {
            return true;
        }
    }
    return false;
}

void fetchAirportsData(const vector<string>& icao_names)
{   
    string fileName = "/flightScanner.sh";
    string command;
    const string parent_dir = fs::current_path().parent_path().string();
    command += "bash ";
    command += parent_dir;
    command += fileName;
    int size = icao_names.size();
    for (int i = 0; i < size; i++)
    {
        command += " ";
        command += icao_names[i];
    }

    cout << "Running script command: " << command << endl;

    system(command.c_str());
}

vector<Node*> get_flights_to_airport(string icao , vector<Node*>& arr)
{
    int size = arr.size();
    vector<Node*> arrivals;
    for (int i = 0; i < size; i++)
        if (arr[i]->getEstArrivalAirport() == icao)
            arrivals.push_back(arr[i]);
    
    return arrivals;
}

vector<Node*> get_flights_from_airport(string icao , vector<Node*>& arr)
{
    int size = arr.size();
    vector<Node*> departures;

    for (int i = 0; i < size; i++)
        if (arr[i]->getEstDepartureAirport() == icao)
            departures.push_back(arr[i]);

    return departures;
}

vector<Node*> get_flights_by_aircraft(string aircraft , vector<Node*>& arr)
{
    int size = arr.size();
    vector<Node*> flights;

    for (int i = 0; i < size; i++)
        if (arr[i]->getIcao24() == aircraft)
            flights.push_back(arr[i]);

    return flights;
}

void freeArr(vector<Node *>& arr)
{
    for (Node* node : arr) {
        delete node;
    }
    arr.clear();
}

string convertEpochToReadable(const time_t epoch_time) {
  char buffer[80];
  strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", std::localtime(&epoch_time));
  return string(buffer);
}