#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

class signal_handler{
public:
    static pid_t childPid;
public:
    static void handleSignalChild(int signal);

    static void handleSignalParent(int signal);

    static void setChildPid(int childPid);
};


#endif