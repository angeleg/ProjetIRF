#include "pictogram_identifier.h"

/**
 * \brief   PictogramIdentifier constructor
 * \param   template_f     The folder containing the template pictograms
 */
PictogramIdentifier::PictogramIdentifier(string template_f){
    this->template_folder = template_f;
    this->templates_index = utils::getFilenamesFromFolder(template_f, "sheet_cross.png");
}

/**
 * \brief   Identify the given printed pictogram
 * \param   img     A matrix containing a single printed pictogram
 * \return  The name of the recognized pictogram
 */
string PictogramIdentifier::identifyPrintedPicto(Mat img){
    Mat result;
    
    int best_value = 0;
    int best_template_match = 0;

    Mat templ;
    for(int i=0; i < this->templates_index.size(); i++){
        // Load current template
        templ = imread(this->template_folder + this->templates_index[i]);
         
        // Create the result matrix
        int result_cols =  img.cols - templ.cols + 1;
        int result_rows = img.rows - templ.rows + 1;
        result.create(result_cols, result_rows, CV_32FC1);
        
        // Do the Matching and Normalize
        matchTemplate(img, templ, result, CV_TM_CCOEFF);
        
        double minVal, maxVal;
        Point minLoc, maxLoc;
        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
        
        // Update best match
        if(i == 0) {
            best_value = maxVal;
            best_template_match = i;
        }
        else if(maxVal > best_value) {
            best_value = maxVal;
            best_template_match = i;
        }   
    }
    
    string template_found = this->templates_index[best_template_match];
    
    regex templateFileRegex("([a-zA-Z]+).png");
    match_results<string::const_iterator> resultTemplateFile;
    
    regex_match(template_found, resultTemplateFile, templateFileRegex);
    string parsed_template_found = resultTemplateFile[1];
    
    
    return parsed_template_found;
}