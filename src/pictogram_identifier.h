#ifndef __irf_project__pictogram_identifier__
#define __irf_project__pictogram_identifier__

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include "utils.h"

using namespace std;
using namespace cv;

class PictogramIdentifier{
private:
    string template_folder;
    vector<string> templates_index;
    
public:
    PictogramIdentifier(string template_folder);
    string identifyPrintedPicto(Mat img);
};

#endif
