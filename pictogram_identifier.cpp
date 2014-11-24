#include "pictogram_identifier.h"

bool PictogramIdentifier::identifyPrintedPicto(Mat img, Mat templ){
    Mat img_display;
    img.copyTo( img_display );
    
    Mat result;
    
    /// Create the result matrix
    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
    result.create( result_cols, result_rows, CV_32FC1 );
    
    /// Do the Matching and Normalize
    matchTemplate( img, templ, result, CV_TM_CCOEFF );
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
    
    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    
    matchLoc = maxLoc;
    
    /// Show me what you got
    rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    
    imshow( "image_window", img_display );
    imshow( "result_window", result );
    
    waitKey();
    
    return true;
}