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
    fm.writeArff("features.arff");
    
    /*Mat img = imread(root_f + "electricity_004_20_4_0.png", CV_LOAD_IMAGE_GRAYSCALE);
    Rect r = fm.computeDrawingBorders(img);
    cout << "x : " << r.x << ", y : " << r.y << ", width : " << r.width << ", height : " << r.height << endl;
    imshow("", img(r));
    waitKey();*/
    
    exit(0);
}

// Last succes_cpt : 771 / 806(including pages 22)
// 26 950 images of pictograms extracted (100%)