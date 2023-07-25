#include "pipe_handler.h"

// Function to handle pipe creation
void createPipe(const string &type, int pipefd[]) {
    if (pipe(pipefd) == -1) {
        perror((type + "pipe creation failed").c_str());
        exit(EXIT_FAILURE);
    }
}

void closePipe(int pipe[]) {
    close(pipe[0]);
    close(pipe[1]);
}

// Function to handle pipe reading for integer values
int readFromPipe(int pipe) {
    int value;
    read(pipe, &value, sizeof(int));
    return value;
}

// Function to handle pipe writing for integer values
void writeToPipe(int pipe, int value) {
    write(pipe, &value, sizeof(int));
}

// Function to handle pipe reading for string values
char *readStringFromPipe(int pipe) {
    int size = readFromPipe(pipe);
    char *str = new char[size];
    read(pipe, str, size);
    return str;
}

// Function to handle pipe writing for string values
void writeStringToPipe(int pipe, const string &value) {
    int size = (int) value.size() + 1;
    writeToPipe(pipe, size);
    write(pipe, value.c_str(), size);
}

// Function to handle node creation from pipe
Node *createNodeFromPipe(int pipe) {
    Node *node = new Node;
    node->setCallSign(readStringFromPipe(pipe));
    node->setIcao24(readStringFromPipe(pipe));
    node->setEstDepartureAirport(readStringFromPipe(pipe));
    node->setEstArrivalAirport(readStringFromPipe(pipe));
    node->setFirstSeen(readFromPipe(pipe));
    node->setLastSeen(readFromPipe(pipe));

    return node;
}

// Function to handle node writing to pipe
void writeNodeToPipe(int pipe, Node *node) {
    writeStringToPipe(pipe, node->getCallSign());
    writeStringToPipe(pipe, node->getIcao24());
    writeStringToPipe(pipe, node->getEstDepartureAirport());
    writeStringToPipe(pipe, node->getEstArrivalAirport());
    writeToPipe(pipe, node->getFirstSeen());
    writeToPipe(pipe, node->getLastSeen());
}

pid_t tryFork() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error creating child process");
        exit(EXIT_FAILURE);
    }

    return pid;
}

void exitProcess(int exitCode, int pipeToNotify) {
    writeToPipe(pipeToNotify, exitCode);
    exit(exitCode);
}

void readStringVectorFromPipe(int pipe, vector<string> &result) {
    result.clear();
    int size = readFromPipe(pipe);
    for (int i = 0; i < size; i++) {
        result.push_back(readStringFromPipe(pipe));
    }
}

void writeStringVectorToPipe(int pipe, vector<string> &input) {
    int size = input.size();
    writeToPipe(pipe, size);
    for (int i = 0; i < size; i++) {
        writeStringToPipe(pipe, input[i]);
    }
}

void printNodeVectorFromPipe(const string& inputName, int pipe, function<void(vector<Node *> &, const string &)> printFunction) {
    vector<Node *> result;
    int size = readFromPipe(pipe);
    for (int i = 0; i < size; i++) {
        result.push_back(createNodeFromPipe(pipe));
    }
    printFunction(result, inputName);
    freeArr(result);
}

void printMultiNodeVectorFromPipe(vector<string> &inputNames, int pipe,
                                  function<void(vector<Node *> &, const string &)> printFunction) {
    for (int i = 0; i < inputNames.size(); i++) {
        printNodeVectorFromPipe(inputNames[i], pipe, printFunction);
    }
}

void writeNodeVectorToPipe(int pipe, vector<Node *> &input) {
    int size = input.size();
    writeToPipe(pipe, size);
    for (int i = 0; i < size; i++) {
        writeNodeToPipe(pipe, input[i]);
    }
}
