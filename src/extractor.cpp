#include "extractor.h"

static int ROWS_NB = 7;
static int COLS_NB = 5;

static int PICTOGRAM_SIDE = 260;

/**
 * \brief   Extractor constructor
 * \param   input_f The input folder where we retrieve the usersheets
 * \param   output_f The output folder where we put the pictograms exctracted
 */
Extractor::Extractor(string input_f, string output_f, string template_f){
    this->input_folder = input_f;
    this->output_folder = output_f;
    this->template_folder = template_f;
    this->number_of_squares_found = 0;
    this->success_cpt = 0;
}

/**
 * \brief   Try to find the pictograms positions
 * \param   filename    The name of the file containing the usersheet
 * \return  A vector of points, representing the top-left corners of the squares found
 */
vector<Point> Extractor::findSquares(string filename) {
    
    this->current_file = filename;
    
    // The result containing the matrix of points representing the top left corners of found squares
    vector<Point> res;
    
    // Load the sheet
    Mat input_sheet = imread(this->input_folder + filename);
    if (input_sheet.empty()){
        cout << "Unable to find image" << endl;
        return res;
    }
    
    // Isolating drawed pictogram area
    Rect pictograms_region = Rect(500, 700, 1900, 2500);
    Mat pictograms_mat = input_sheet(pictograms_region);
    
    this->drawn_picto_area = pictograms_mat;
    
    // Isolating printed pictogram area
    Rect printed_pictograms_region = Rect(200, 700, PICTOGRAM_SIDE, 2500);
    Mat printed_pictograms_mat = input_sheet(printed_pictograms_region);
    
    this->printed_picto_area = printed_pictograms_mat;
    
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
            res.insert(res.begin(), approx[0]);
            cpt++;
        }
        
    }
    cout << "Found " << cpt << " squares" << endl;
    this -> number_of_squares_found = cpt;
    return res;
}


/**
 * \brief   Computes a "virtual grid" that encapsulates the average coordinates of each row and each column
 * \param   found_squares   The top-left corner point of the squares found by the findSquares method
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


/**
 * \brief   Extracts the pictograms of a given usersheet
 * \param   filename    The name of the file containing the usersheet
 */
void Extractor::extractFromFile(string filename) {
    PictogramIdentifier identifier = *new PictogramIdentifier(this->template_folder);
    
    // Find squares
    vector<cv::Point> squarePoints = this->findSquares(filename);
    
    // Test if enough squares have been detected
    if(this->number_of_squares_found < 28){
        cout << "Unable to process file " << this->current_file << ", because only " << " squares have been detected." << endl;
        return;
    }
    else{
        string labelName;
        regex fileRegex("([0-9][0-9][0-9])([0-9][0-9]).png");
        regex templateFileRegex("([a-zA-Z]+).png");
        
        match_results<string::const_iterator> resultFile;
        match_results<string::const_iterator> resultTemplateFile;
        
        // Retrieve scripter and page number
        if(!regex_match(filename, resultFile, fileRegex))
            cout << "Invalid filename" << endl;
        
        string scripter = resultFile[1];
        string page = resultFile[2];
        
        // Retrieve each pictogram coordinate
        vector<vector<int>> grid = this->generateGrid(squarePoints, 10);
        
        // Extract pictograms
        int cpt = 0;
        
        // For each row
        for(int i=0; i < grid[0].size(); i++) {
            
            // Identify line printed pictogram
            Rect printed_roi = Rect(0, grid[0][i], PICTOGRAM_SIDE, PICTOGRAM_SIDE);
            Mat current_picto_mat = this->printed_picto_area(printed_roi);
            
            labelName = identifier.identifyPrintedPicto(current_picto_mat);
            
            // Retrieve scripter and page number
            if(!regex_match(labelName, resultTemplateFile, templateFileRegex))
                cout << "Invalid template name" << endl;
            
            string parsedLabelName = resultTemplateFile[1];
            
            // For each column
            for(int j=0; j < grid[1].size(); j++) {
                
                string outputName = this->output_folder + parsedLabelName + "_" + scripter + "_" + page + "_" + to_string(i) + "_" + to_string(j);
                
                // Get pictogram region
                Rect region_of_interest = Rect(grid[1][j] + 10, grid[0][i] + 10, PICTOGRAM_SIDE - 20, PICTOGRAM_SIDE - 20);
                Mat img_roi = this->drawn_picto_area(region_of_interest);
                
                // Write pictogram image to disk
                string output = outputName  + ".png";
                imwrite(output, img_roi);
                
                // Write description file to disk
                ofstream descriptionFile;
                descriptionFile.open(outputName + ".txt");
                descriptionFile << "# Team members: Berthier, Géraud, Le Goff\n";
                descriptionFile << "label " << parsedLabelName << "\n";
                descriptionFile << "form " << scripter << page << "\n";
                descriptionFile << "scripter " << scripter << "\n";
                descriptionFile << "page " << page << "\n";
                descriptionFile << "row " << i << "\n";
                descriptionFile << "column " << j << "\n";
                descriptionFile.close();
                
                cpt++;
            }
        }
        
        this->success_cpt++;
    }
}

void Extractor::extractFromInputFolder(){
    DIR* rep = NULL;
    struct dirent* fichierLu = NULL;
    rep = opendir(this->input_folder.c_str());
    
    if (rep == NULL)
        cout << "Unable to open template directory" << endl;
    
    int cpt =0;

    while ((fichierLu = readdir(rep)) != NULL){
        if(cpt > 1){
            cout << "Handling file : " << fichierLu->d_name << endl;
            this->extractFromFile(fichierLu->d_name);
            this->success_cpt++;
        }
        cpt++;
    }
    
    if (closedir(rep) == -1)
        cout << "There was a problem closing the template directory" << endl;
    cout << "Sheet correctly extracted : " << this->success_cpt << "" << endl;
}
