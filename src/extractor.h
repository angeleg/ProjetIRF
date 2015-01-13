#ifndef __irf_project__extractor__
#define __irf_project__extractor__

#include <opencv2/opencv.hpp>
#include <iostream>
#include <regex>
#include <fstream>
#include <dirent.h>
#include "pictogram_identifier.h"

using namespace std;
using namespace cv;

class Extractor{
private:
    string input_folder;
    string output_folder;
    string template_folder;
    string current_file;
    int success_cpt;
    Mat cross_template;
    
public:
    Extractor(string input_f, string output_f, string template_f);
    
    // Extraction
    vector<Point>  findSquares(string filename);
    vector<vector<int>> generateGrid(vector<Point> found_squares, int precision);
    void extractFromFile(string filename);
    void extractFromInputFolder();
    
    // Normalization
    vector<Point> findCrossCoordinates(Mat input_sheet);
    Mat normalize(Mat input_sheet);
};

#endif