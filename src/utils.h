#ifndef __irf_project__utils__
#define __irf_project__utils__

#include <vector>
#include <iostream>
#include <regex>
#include <dirent.h>


using namespace std;

namespace utils {
    extern regex hiddenFileRegex;
    
    DIR* openDir(string path);
    void closeDir(DIR* dir);
    vector<string> getFilenamesFromFolder(string path);
}

#endif
