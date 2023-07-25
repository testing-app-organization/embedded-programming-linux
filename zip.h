#ifndef ZIP_H
#define ZIP_H

#include <iostream>
#include <vector>
#include <filesystem>
#include <cctype>
#include <dirent.h>
#include <zip.h>
#include <sys/stat.h>

using namespace std;

//void zip_directory(const string& inputDirectory,const string& outputFileName);
//bool is_dir(const string& dir);
//void zipFiles(string inputDirectory, string currentDirectory, zip_t * zipper);
bool isValidInput(const char * ICAO);
void addFilesToArchive(zip_t* archive, const string& path, const string& baseDirectory);



#endif //__ZIP_H
