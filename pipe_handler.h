#ifndef PIPE_HANDLER_H
#define PIPE_HANDLER_H

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <functional>
#include "myLibrary.h"
#include "full_schedule.h"
#include "arrivals.h"
#include "airplane.h"
#include "signal_handler.h"
#include "node.h"

    // Function to handle pipe creation
    void createPipe(const string& type, int pipe[]);

    void closePipe(int pipe[]);

    void exitProcess(int exitCode, int pipeToNotify);

    // Function to handle pipe reading for integer values
    int readFromPipe(int pipe);

    // Function to handle pipe writing for integer values
    void writeToPipe(int pipe, int value);

    // Function to handle pipe reading for string values
    char* readStringFromPipe(int pipe);

    // Function to handle pipe writing for string values
    void writeStringToPipe(int pipe, const string& value);

    // Function to handle node creation from pipe
    Node* createNodeFromPipe(int pipe);

    // Function to handle node writing to pipe
    void writeNodeToPipe(int pipe, Node* node);

    void readStringVectorFromPipe(int pipe, vector<string>& result);

    void writeStringVectorToPipe(int pipe, vector<string>& input);

    void printNodeVectorFromPipe(const string& inputNames, int pipe, function<void(vector<Node*>&, const string&)> printFunction);

    void printMultiNodeVectorFromPipe(vector<string>& inputNames, int pipe, function<void(vector<Node*>&, const string&)> printFunction);

    void writeNodeVectorToPipe(int pipe, vector<Node*>& input);

    pid_t tryFork();


#endif //PIPE_HANDLER_H
