#include <dirent.h>
#include <zip.h>
#include <sys/stat.h>
#include <iostream>
#include "zip.h"


using namespace std;


void addFilesToArchive(zip_t* archive, const string& path, const string& baseDirectory) {
    DIR *dir = opendir(path.c_str());
    if (!dir) {
        throw runtime_error("Failed to open directory!");
        return;
    }

    string baseDirRelative = baseDirectory;
    if (!baseDirectory.empty() && baseDirectory[0] == '/') {
        baseDirRelative = baseDirectory.substr(1);
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        string filePath = path + "/" + entry->d_name;

        struct stat st;
        stat(filePath.c_str(), &st);

        if (S_ISDIR(st.st_mode)) {
            if (string(entry->d_name) == "." || string(entry->d_name) == ".." || !isValidInput(entry->d_name)) {
                continue;
            }

            string nextPath = path + "/" + entry->d_name;
            string nextBaseDirectory = baseDirRelative + "/" + entry->d_name;
            addFilesToArchive(archive, nextPath, nextBaseDirectory);
        } else {
            string entryString(entry->d_name);
            size_t dotPosition = entryString.find_last_of('.');
            string result = entryString.substr(dotPosition + 1);
            if (result != "arv" && result != "dpt")
            {
                continue;
            }
            string entryName = baseDirRelative + "/" + entry->d_name;
            zip_source_t *source = zip_source_file(archive, filePath.c_str(), 0, 0);
            if (zip_file_add(archive, entryName.c_str(), source, ZIP_FL_OVERWRITE) < 0) {
                throw runtime_error("Failed to add file to zip!");
                return;
            }
        }
    }
    closedir(dir);
}

bool isValidInput(const char * ICAO) {
    int i = 0;
    while (ICAO[i] != '\0') {
        if (ICAO[i] > 'Z' || ICAO[i] < 'A') {
            return false;
        }
        i++;
    }
    return true;
}