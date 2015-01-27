#include "extractor.h"
#include "feature.h"

string root = "/Users/baptiste/Documents/INSA/irf/data";
string input_learning_db = "NicIcon";
string learning_db_extracted = "NicIcon_extracted";
string template_pictograms = "template_pictograms";
string arff_out = "arff_out";

int main (int argc, const char * argv[]) {
    
    Extractor extractor = *new Extractor(root + input_learning_db + "/",
                                         root + learning_db_extracted + "/",
                                         root + template_pictograms + "/");
    
    FeatureManager fm = FeatureManager(root + learning_db_extracted + "/",
                                       root + arff_out + "/");
    
    //extractor.extractFromInputFolder();
    fm.writeArff("out.arff");
    
    exit(0);
}

// Last succes_cpt : 771 / 806(including pages 22)
// 26 950 images of pictograms extracted (100%)