#include <iostream>
#include <csignal>
#include <unistd.h>
#include "signal_handler.h"
#include "pipe_handler.h"
#include "zip.h"

using namespace std;

pid_t signal_handler::childPid = 0;

void signal_handler::handleSignalChild(int signal)

{
    if (signal == SIGINT)
    {
        cout << "zipping database upon closure" << endl;
        zip_t *archive = zip_open("archive.zip", ZIP_CREATE | ZIP_TRUNCATE, NULL);
        filesystem::path currentPath = filesystem::current_path().parent_path();
        cout << "current path: " << currentPath << endl;
        if (!archive) {
            throw runtime_error("Failed to open a zip file. Demolishing proccess!");
        }
        addFilesToArchive(archive, currentPath.string(), "");
        zip_close(archive);
        exit(0);
    }
    exit(signal);
}

void signal_handler::handleSignalParent(int signal) {
    cout << "Parent process received interrupt signal: " << signal << endl;

    if(signal == SIGINT && childPid != 0) {
        kill(childPid, signal);

        int status;
        waitpid(childPid, &status, 0);

        if (WIFEXITED(status)) {
            std::cout << "Child process ended normally.\n";
            exit(0);
        } else {
            std::cout << "Child process ended abnormally.\n";
        }
    }
    exit(signal);
}

void signal_handler::setChildPid(int childPid) {
    signal_handler::childPid = childPid;
}


