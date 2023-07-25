#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "myLibrary.h"
#include "full_schedule.h"
#include "arrivals.h"
#include "airplane.h"
#include "signal_handler.h"
#include "error_handling.h"
#include <filesystem>
#include "zip.h"
#include "pipe_handler.h"

using namespace std;

int userOptions(vector<string> &names);

int main()
{

    mkfifo("/tmp/flights_pipe", 0666);

    // Open the named pipe for reading and writing
    int pipeFd = open("/tmp/flights_pipe", O_WRONLY);
    if (pipeFd < 0)
    {
        cout << "Failed to open the named pipe." << endl;
        return 1;
    }

    int exitStatus;
    vector<string> inputNames;
    int userChoice;

    // Set handler for SIGINT
    signal(SIGINT, signal_handler::handleSignalParent);

    // Wait for the child process to finish unzipping if zip exists
    // read(pipeFd, &userChoice, sizeof(userChoice));

    while (true)
    {
        // Get user input
        userChoice = userOptions(inputNames);
        // Write user choice to pipe
        write(pipeFd, &userChoice, sizeof(userChoice));
        if (userChoice >= 1 && userChoice <= 3)
        {
            writeStringVectorToPipe(pipeFd, inputNames);
        }

        switch (userChoice)
        {
        case 1:
            cout << "Fetching airports data." << endl;
            break;
        case 2:
        {
            printMultiNodeVectorFromPipe(inputNames, pipeFd, printAirplaneArrivalFlights);
            break;
        }
        case 3:
        {
            printNodeVectorFromPipe(inputNames[0], pipeFd, printFullSchedule);
            break;
        }
        case 4:
        {
            printMultiNodeVectorFromPipe(inputNames, pipeFd, printAirplaneFlights);
            break;
        }
        case 5:
            cout << "Starting zipping process." << endl;
            break;
        case 6:
            cout << "Exiting." << endl;
            exitStatus = readFromPipe(pipeFd); // make sure child process finished
            return exitStatus;
        default:
            return 1;
        }

        // Wait for the child process to finish
        read(pipeFd, &userChoice, sizeof(userChoice));
        cout << endl;

        inputNames.clear();
    }

    // Close the named pipe
    close(pipeFd);

    return 0;
}

int userOptions(vector<string> &names)
{
    int userChoice = 0;
    string input;
    names.clear();
    while (userChoice < 1 || userChoice > 6)
    {
        cout << "1 - Fetch airports data." << endl;
        cout << "2 - print airports incoming flights." << endl;
        cout << "3 - print airports full flights schedule." << endl;
        cout << "4 - print aircraft full flights schedule." << endl;
        cout << "5 - Zip DB files." << endl;
        cout << "6 - Shutdown." << endl;
        cout << "Please make your choice <1,2,3,4,5,6>: " << endl;

        while (input.empty()) // handle cases of user press enter
            getline(cin, input);

        while (!(isNumber(input, userChoice))) // validate input
        {
            cout << "Invalid input. Please enter a valid integer between 1 to 7: ";
            getline(cin, input);
        }
        if (userChoice == 1)
        {
            int size;
            cout << "insert how many icao names would you like to insert: ";

            getline(cin, input);

            while (!(isNumber(input, size))) // validate input
            {
                cout << "Invalid input. Please enter a valid integer: ";
                getline(cin, input);
            }
            cout << "insert icao names (press enter after each one):" << endl;
            for (int i = 0; i < size; i++)
            {
                string name;
                cin >> name;
                names.push_back(name);
            }
        }
        else if (userChoice == 2)
        {
            cout << "insert icao name: ";
            string name;
            cin >> name;
            names.push_back(name);
        }
        else if (userChoice == 3)
        {
            int size;
            cout << "insert how many aircraft names would you like to insert: ";

            getline(cin, input);

            while (!(isNumber(input, size))) // validate input
            {
                cout << "Invalid input. Please enter a valid integer: ";
                getline(cin, input);
            }
            cout << "insert aircraft names (press enter after each one):" << endl;
            for (int i = 0; i < size; i++)
            {
                string name;
                cin >> name;
                names.push_back(name);
            }
        }
        else if (userChoice > 7 || userChoice < 1)
        {
            cout << "Invalid input. Please enter a valid integer between 1 to 7: ";
            getline(cin, input);
        }
    }
    return userChoice;
}
