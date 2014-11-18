#ifndef __irf_project__extractor__
#define __irf_project__extractor__


#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <regex>
#include <fstream>

using namespace std;
using namespace cv;

class Extractor{
private:
    Mat isolatedPictoArea;
    
public:
    vector<Point>  findSquares(string filename);
    vector<vector<int>> generateGrid(vector<Point> found_squares, int precision);
    void extractFromFile(string filename);
};

#endif