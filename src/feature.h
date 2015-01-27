#ifndef __irf_project__feature_manager__
#define __irf_project__feature_manager__

#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include "utils.h"

using namespace cv;
using namespace std;

class FeatureManager {
private:
    string db_folder;
    string arff_folder;
    
public:
    FeatureManager(string db_f, string arff_f);
    //~FeatureManager();
    
    // Manager
    void writeArff(string file_path);
    Mat normalize(Mat img, Rect cropping);
    
    // Metrics
    Rect computeDrawingBorders(Mat grayscaled_pictogram);
    
    // Staticstics
    double getBlackPercentage(Mat img);
    Point getGravityCenter(Mat img);
    
    // Zoning
    vector<Point> getZonesGravityCenters(Mat img);
    void printZonesGravityCenterAttributes(ofstream &f);
    
    
};

#endif
