#include "feature_manager.h"

/**
 * \brief   Constructor
 * \param   db_f    Database input folder
 * \param   arff_f  ARFF output folder
 */
FeatureManager::FeatureManager(string db_f, string arff_f) {
    this->db_folder = db_f;
    this->arff_folder = arff_f;
}

int findFirstPixel(Mat grayscale_pictogram, bool parse_from_zero, bool parse_by_row) {
    
    uchar THRESHOLD = 220;
    
    int i;
    int j;
    int bigBound;
    int littleBound;
    
    // Set boundaries
    if(parse_by_row) {
        bigBound = grayscale_pictogram.rows;
        littleBound = grayscale_pictogram.cols;
    }
    else {
        bigBound = grayscale_pictogram.cols;
        littleBound = grayscale_pictogram.rows;
    }
    
    // Init counters
    if(parse_from_zero) {
        i = 0;
        j = 0;
    }
    
    else {
        i = bigBound - 1;
        j = littleBound - 1;
    }
    
    // Parse image
    while( (parse_from_zero && i < bigBound) || (!parse_from_zero && i > 0) ) {
        
        // Detect first non white pixel
        if(parse_by_row && grayscale_pictogram.at<uchar>(i,j) < THRESHOLD)
            break;
        else if(!parse_by_row && grayscale_pictogram.at<uchar>(j,i) < THRESHOLD)
            break;
        
        // Increase counter
        if(parse_from_zero) {
            if( ((j+1) % littleBound) == 0 ) {
                j = 0;
                i++;
            }
            else
                j++;
        }
        // Decrease counter
        else {
            if(j-1 == 0) {
                j = littleBound - 1;
                i--;
            }
            else
                j--;
        }
    }
    
    return i;
}

// TODO : load in grayscale
Rect FeatureManager::computeDrawingBorders(Mat grayscale_pictogram) {
    
    int leftBorder = findFirstPixel(grayscale_pictogram, true, false);
    int topBorder = findFirstPixel(grayscale_pictogram, true, true);
    int rightBorder = findFirstPixel(grayscale_pictogram, false, false);
    int bottomBorder = findFirstPixel(grayscale_pictogram, false, true);
    
    std::cout << leftBorder << ", " << topBorder << ", " << rightBorder << ", " << bottomBorder << std::endl;
    Rect roi = Rect(leftBorder, topBorder, rightBorder - leftBorder, bottomBorder - topBorder);
    
    imshow("", grayscale_pictogram(roi));
    waitKey();
    
    return roi;
}