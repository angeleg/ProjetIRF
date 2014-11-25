#include <iostream>
#include "extractor.h"
#include "pictogram_identifier.h"
#include "utils.h"

using namespace std;

string root_f = "/Users/baptiste/Documents/INSA/irf/";

int main (int argc, const char * argv[]) {
    
    Extractor extractor = *new Extractor(root_f + "test_input/", root_f + "output/", root_f + "template_pictograms/");
    //extractor.extractFromFile("00117.png");

    extractor.extractFromInputFolder();
}