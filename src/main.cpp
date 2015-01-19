#include <iostream>
#include "extractor.h"
#include "feature.h"

using namespace std;

string root_f = "/Users/baptiste/Documents/INSA/irf/";

int main (int argc, const char * argv[]) {
    
    //Extractor extractor = *new Extractor(root_f + "NicIcon/", root_f + "output/", root_f + "template_pictograms/");
    //extractor.extractFromInputFolder();
    //extractor.extractFromFile("00001.png");
    
    FeatureManager fm = FeatureManager(root_f + "output/", root_f + "arff_out/");
    //Mat im = imread(root_f + "output/accident_000_00_0_0.png", CV_LOAD_IMAGE_GRAYSCALE);
    //fm.computeDrawingBorders(im);
    fm.writeArff("features.arff");
    
    exit(0);
}

// Last succes_cpt : 771
// TODO : finish to write Readme.md