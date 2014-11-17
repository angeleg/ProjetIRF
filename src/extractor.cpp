#include "extractor.h"

using namespace std;
using namespace cv;

static string INPUT_DIR = "/Users/baptiste/Documents/INSA/irf/test_db/";
static string OUTPUT_DIR = "/Users/baptiste/Documents/INSA/irf/output/";

void Extractor::extract() {
    
    // Load the sheet
    Mat inputSheet = imread(INPUT_DIR + "s01_0001.png");
    if (inputSheet.empty()){
        cout << "Unable to find image" << endl;
        return;
    }
    
    // Convert to grayscale
    Mat gray;
    cvtColor(inputSheet, gray, CV_BGR2GRAY);
    
    // Convert to binary image using Canny
    Mat bw;
    Canny(gray, bw, 0, 50, 5);
    
    // Find contours
    vector<vector<Point> > contours;
    findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    
    // The array for storing the approximation curve
    vector<Point> approx;
    int cpt = 0;
    
    for (int i = 0; i < contours.size(); i++) {
        // Approximate contour with accuracy proportional to the contour perimeter
        approxPolyDP(Mat(contours[i]),
                     approx,
                     arcLength(Mat(contours[i]), true) * 0.02,
                     true
                     );
        
        // Skip small or non-convex objects
        if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
            continue;
        
        // Export rectangles
        if(approx.size() == 4 && approx[0].x + 250 < inputSheet.cols && approx[2].y + 250 < inputSheet.rows){
            cout << approx[0].x << " " << approx[0].y << " " << approx[2].x << " " << approx[2].y << endl;
            cpt++;
            Rect region_of_interest = Rect(approx[0].x, approx[0].y, 250, 250);
            Mat img_roi = inputSheet(region_of_interest);
            string output = OUTPUT_DIR + "img" + to_string(i) + ".png";
            imwrite(output, img_roi);
        }

    }
    cout << "Found " << cpt << " rectangles" << endl;
    
}
