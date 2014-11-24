#ifndef __irf_project__pictogram_identifier__
#define __irf_project__pictogram_identifier__

#include <opencv2/opencv.hpp>
#include <iostream>
#include <regex>
#include <fstream>

using namespace std;
using namespace cv;

class PictogramIdentifier{
private:
    
public:
    bool identifyPrintedPicto(Mat img, Mat templ);
};

#endif
