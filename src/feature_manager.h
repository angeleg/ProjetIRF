#ifndef __irf_project__feature_manager__
#define __irf_project__feature_manager__

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

class FeatureManager {
private:
    string db_folder;
    string arff_folder;
    
public:
    FeatureManager(string db_f, string arff_f);
    //~FeatureManager();
    
    Rect computeDrawingBorders(Mat pictogram);
    
};

#endif
