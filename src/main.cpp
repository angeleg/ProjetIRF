#include <iostream>
#include "extractor.h"
#include "feature_manager.h"

using namespace std;

string root_f = "/Users/baptiste/Documents/INSA/irf/";

int main (int argc, const char * argv[]) {
    
    //Extractor extractor = *new Extractor(root_f + "sample_db/", root_f + "output/", root_f + "template_pictograms/");
    //extractor.extractFromFile("00001.png");
    //extractor.extractFromInputFolder();
    
    FeatureManager fm = FeatureManager(root_f + "output/", root_f + "arff_out/");
    Mat im = imread(root_f + "output/casualty_000_00_3_0.png", CV_LOAD_IMAGE_GRAYSCALE);
    fm.computeDrawingBorders(im);
    
    exit(0);
}

// Last succes_cpt : 771
// TODO : rewrite Readme.md