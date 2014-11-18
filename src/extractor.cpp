#include "extractor.h"

static string INPUT_DIR = "/Users/baptiste/Documents/INSA/irf/test_db/";
static string OUTPUT_DIR = "/Users/baptiste/Documents/INSA/irf/output/";

static int ROWS_NB = 7;
static int COLS_NB = 5;

/**
 * \brief   Try to find the pictograms positions
 * \return  A vector of points, representing the top-left corners of the squares found
 */
vector<Point> Extractor::findSquares() {
    
    // The result containing the matrix of points representing the top left corners of found squares
    vector<Point> res;
    
    // Load the sheet
    Mat input_sheet = imread(INPUT_DIR + "s01_0001.png");
    if (input_sheet.empty()){
        cout << "Unable to find image" << endl;
        return res;
    }
    
    // Isolating pictogram area
    Rect pictograms_region = Rect(613, 763, 1595, 2350);
    Mat pictograms_mat = input_sheet(pictograms_region);
    
    // Convert to grayscale
    Mat gray;
    cvtColor(pictograms_mat, gray, CV_BGR2GRAY);
    
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
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);
        
        // Skip small or non-convex objects
        if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
            continue;
        
        // Export rectangles
        if(approx.size() == 4) {
            //cout << "x1: " <<approx[0].x << ", y1; " << approx[0].y << ", x2: " << approx[2].x << ", y2: " << approx[2].y << endl;
            
            /*Rect region_of_interest = Rect(approx[0].x, approx[0].y, 250, 250);
             Mat img_roi = pictograms_mat(region_of_interest);
             string output = OUTPUT_DIR + "img" + to_string(i) + ".png";
             imwrite(output, img_roi);*/
            
            res.insert(res.begin(), approx[0]);
            
            cpt++;
        }
        
    }
    cout << "Found " << cpt << " rectangles" << endl;
    return res;
}

/**
 * \brief   Computes a "virtual grid" that encapsulates the average coordinates of each row and each column
 * \param   found_squares   The top-left corner point of the squares found by the findSquares() method
 * \param   precision       The threshold determining if a coordinate is from a same row/column
 * \return  A vector containg two vectors, one containing rows position (first one) and the other containing column ones (second one)
 */
vector<vector<int>> Extractor::generateGrid(vector<Point> found_squares, int precision){
    vector<vector<int>> res;
    
    res.push_back(*new vector<int>()); // position verticale des lignes
    res.push_back(*new vector<int>()); // position horizontale des colonnes
    
    int lastIndex = 0;
    
    // Iterate for each row
    for (int i=0; i < ROWS_NB; i++) {
        int sum = 0;
        int cpt = 0;
        
        Point root = found_squares[lastIndex];
        
        // Group same row values and make average for each line
        for(int j=lastIndex; j < found_squares.size(); j++){
            Point current = found_squares[j+1];
            
            if( (current.y <= root.y + precision) && (current.y >= root.y - precision) ) {
                sum += current.y;
                cpt++;
            }
            else {
                lastIndex = j+1;
                break;
            }
        }
        int average = (int)sum/cpt;
        res[0].push_back(average);
    }
    
    // Iterate for each column
    for(int i=0; i < COLS_NB; i++){
        int sum = 0;
        int cpt = 0;
        
        Point root = found_squares[i];
        
        // Group same column values and make average for each line
        for(int j=0; j < found_squares.size(); j++) {
            Point current = found_squares[j];
            
            if( (current.x <= root.x + precision) && (current.x >= root.x - precision) ) {
                sum += current.x;
                cpt++;
            }
        }
        int average = (int)sum/cpt;
        res[1].push_back(average);
    }
    
    return res;
}
