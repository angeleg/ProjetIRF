#ifndef __irf_project__utils__
#define __irf_project__utils__

#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <dirent.h>


using namespace std;

namespace utils {
    extern regex hiddenFileRegex;
    
    DIR* openDir(string path);
    void closeDir(DIR* dir);
    
    vector<string> getFilenamesFromFolder(string path);
    
    void writeDescriptionFile(string output_name, string label, string scripter, string page , int i, int j);
}

#endif
