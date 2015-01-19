#include "extractor.h"
#include <cmath>

// Theorical data of crosses position and angle between them
const cv::Point nm_tr_cross(2205, 472);
const cv::Point nm_bl_cross(256, 3235);
const double nm_cross_angle = 54.801136731;


/**
 * \brief   Find the coordinates of the two cross on the sheet
 * \param   input_sheet The matrix containing the image
 * \return  A vector of two points
 */
vector<Point> Extractor::findCrossCoordinates(Mat input_sheet) {
    
    vector<Point> result;
    Point top_right_cross;
    Point bottom_left_cross;
    
    Mat foundCross;
    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    
    // Find top right cross position
    Rect tr_corner(input_sheet.cols*3/4, 0, input_sheet.cols/4, input_sheet.rows/4);
    
    matchTemplate(input_sheet(tr_corner), this->cross_template, foundCross, CV_TM_SQDIFF);
    minMaxLoc(foundCross, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    
    top_right_cross = minLoc;
    
    top_right_cross.x += this->cross_template.cols/2 + input_sheet.cols*3/4;
    top_right_cross.y += this->cross_template.rows/2;
    
    // Find bottom left cross position
    Rect bl_corner(0, input_sheet.rows*3/4, input_sheet.cols/4, input_sheet.rows/4);
    
    matchTemplate(input_sheet(bl_corner), this->cross_template, foundCross, CV_TM_SQDIFF);
    minMaxLoc(foundCross, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    
    bottom_left_cross = minLoc;
    bottom_left_cross.x += this->cross_template.cols/2;
    bottom_left_cross.y += this->cross_template.rows/2 + input_sheet.rows*3/4;
    
    result.push_back(top_right_cross);
    result.push_back(bottom_left_cross);
    
    return result;
}

/**
 * \brief   Normalizes the sheet in size and rotation
 * \param   input_sheet The raw sheet to normalize
 * \return  The normalized sheet
 */
Mat Extractor::normalize(Mat input_sheet) {

    Mat normalized_sheet;
    vector<Point> cross_coordinates = this->findCrossCoordinates(input_sheet);
    Point tr_cross = cross_coordinates[0];
    Point bl_cross = cross_coordinates[1];
    
    // Rotate the TR-BL line around BL to match the normalized orientation
    double dx_cross = tr_cross.x - bl_cross.x;
    double dy_cross = bl_cross.y - tr_cross.y;
    double cross_angle = atan(dy_cross/dx_cross) * 180.0 / M_PI;
    
    Mat rot = getRotationMatrix2D(bl_cross, nm_cross_angle-cross_angle, 1.0);
    warpAffine(input_sheet, normalized_sheet, rot, input_sheet.size());
    
    // Align this form's BL cross with the normalized BL
    Point delta_bl_nm = nm_bl_cross - bl_cross;
    
    Mat translate = (Mat_<double>(2,3) << 1, 0, delta_bl_nm.x, 0, 1, delta_bl_nm.y);
    warpAffine(normalized_sheet, normalized_sheet, translate, input_sheet.size());
    
    // Resize the image to position the TR cross correctly
    double nm_dx_cross = nm_tr_cross.x - nm_bl_cross.x;
    double nm_dy_cross = nm_bl_cross.y - nm_tr_cross.y;
    double scale_factor_x = nm_dx_cross/dx_cross;
    double scale_factor_y = nm_dy_cross/dy_cross;
    
    Mat resize = getRotationMatrix2D(bl_cross, 0.0, (scale_factor_x+scale_factor_y)*0.5);
    warpAffine(normalized_sheet, normalized_sheet, resize, input_sheet.size());
    
    // Vertically crop the image to the region between the crosses
    Rect crop_roi(0, nm_tr_cross.y, normalized_sheet.cols, nm_dy_cross);
    
    return normalized_sheet(crop_roi);
}
