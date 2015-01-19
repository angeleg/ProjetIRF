#include <iostream>
#include "extractor.h"

using namespace std;

string root_f = "/Users/baptiste/Documents/INSA/irf/";

int main (int argc, const char * argv[]) {
    
    Extractor extractor = *new Extractor(root_f + "sample_db/", root_f + "output/", root_f + "template_pictograms/");
    //extractor.extractFromFile("00001.png");
    extractor.extractFromInputFolder();
}

// Last succes_cpt : 771
// TODO : rewrite Readme.md