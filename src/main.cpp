#include <iostream>
#include "extractor.h"
#include "pictogram_identifier.h"

using namespace std;

string input_f = "/Users/baptiste/Documents/INSA/irf/test_input/";
string output_f = "/Users/baptiste/Documents/INSA/irf/output/";
string root_f = "/Users/baptiste/Documents/INSA/irf/";

int main (int argc, const char * argv[]) {
    
    Extractor extractor = *new Extractor(input_f, output_f, root_f + "template_pictograms/");
    extractor.extractFromFile("00004.png");
    /*
    Mat sheet = imread(output_f + "aaaa6.png");

    PictogramIdentifier pe = *new PictogramIdentifier(root_f + "template_pictograms/");
    pe.identifyPrintedPicto(sheet);*/
    
}