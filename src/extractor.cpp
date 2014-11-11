#include "extractor.h"
#include <iostream>
#include <fstream>

#define OUTPUT_DIR "/Users/baptiste/Desktop"

using namespace std;

void Extractor::extract() {
    string outputDir (OUTPUT_DIR);
    string outputName ("/irf-out.txt");
    
    // Write file on disk
    ofstream file;
    file.open(outputDir + outputName);
    file << "line 1\nline 2";
    file.close();
    
    cout << OUTPUT_DIR << " writed to disk" << endl;
}