#include <iostream>
#include "extractor.h"
#include "pictogram_identifier.h"

using namespace std;

string input_f = "/Users/baptiste/Documents/INSA/irf/test_db/";
string output_f = "/Users/baptiste/Documents/INSA/irf/output/";

int main (int argc, const char * argv[]) {
    
    Extractor e = *new Extractor(input_f, output_f);
    e.extractFromFile("s01_0002.png");
    
    /*Mat tmpl_picto = imread("/Users/baptiste/Documents/INSA/irf/template_pictograms/police.png");
    Mat sheet = imread("/Users/baptiste/Documents/INSA/irf/test_db/s01_0002.png");

    
    PictogramIdentifier pe = *new PictogramIdentifier();
    pe.identifyPrintedPicto(sheet, tmpl_picto);*/
    
}