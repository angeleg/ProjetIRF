#include <iostream>
#include "extractor.h"
#include "feature.h"

using namespace std;

string root_f = "/Users/baptiste/Documents/INSA/irf/";

int main (int argc, const char * argv[]) {
    
    //Extractor extractor = *new Extractor(root_f + "test_data/", root_f + "output_test/", root_f + "template_pictograms/");
    //extractor.extractFromInputFolder();
    
    FeatureManager fm = FeatureManager(root_f + "output_test/", root_f + "arff_out/");
    fm.writeArff("features_test.arff");
    
    exit(0);
}

// Last succes_cpt : 771 / 806(including pages 22)
// 26 950 images of pictograms extracted (100%)