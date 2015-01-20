#include "extractor.h"

const int DRAWN_PICS_ROWS = 7;
const int DRAWN_PICS_COLS = 5;

const Rect first_printed_pictogram_zone(200, 246, 250, 250);
const int printed_pictogram_padding_y = 348;

const Rect first_drawn_pictogram_zone(610,248,250,250);
const Point drawn_pictogram_padding(348,348);
const Rect drawn_pictogram_cropping(10,16,16,16);

/**
 * \brief   Extractor constructor
 * \param   input_f     The input folder where we retrieve the usersheets
 * \param   output_f    The output folder where we put the pictograms exctracted
 */
Extractor::Extractor(string input_f, string output_f, string template_f){
    this->input_folder = input_f;
    this->output_folder = output_f;
    this->template_folder = template_f;
    this->success_cpt = 0;
    this->cross_template = imread(template_f + "sheet_cross.png");
    
    if(this->cross_template.empty())
        cout << "Unable to load cross_template image file." << endl;
}

/**
 * \brief   Extracts the pictograms of a given usersheet
 * \param   filename    The name of the file containing the usersheet
 */
void Extractor::extractFromFile(string filename) {
    
    PictogramIdentifier identifier = *new PictogramIdentifier(this->template_folder);
    this->current_file = filename;
    
    // Normalize the input image
    Mat input_sheet = imread(this->input_folder + filename);
    Mat normalized_sheet = this->normalize(input_sheet);
    
    // Prepare input file regex
    regex fileRegex("([0-9][0-9][0-9])([0-9][0-9]).png");
    match_results<string::const_iterator> resultFile;
    
    // Retrieve scripter and page number
    if(!regex_match(filename, resultFile, fileRegex))
        cout << "Invalid filename" << endl;
    
    string label_name;
    string scripter = resultFile[1];
    string page = resultFile[2];
    
    // Ignore the page 22 or 23 of each scripter because it's not a valid input file
    if ( (page.compare("22") == 0) || (page.compare("23") == 0) )
        return;
    
    Rect current_printed_pictogram_zone = first_printed_pictogram_zone;
    Rect current_drawn_pictogram_zone = first_drawn_pictogram_zone;
    
    for(int i=0; i < DRAWN_PICS_ROWS; i++) {
        
        current_printed_pictogram_zone.y = first_printed_pictogram_zone.y + i*printed_pictogram_padding_y;
        current_drawn_pictogram_zone.y = first_drawn_pictogram_zone.y + i*drawn_pictogram_padding.y;
        
        label_name = identifier.identifyPrintedPicto(normalized_sheet(current_printed_pictogram_zone));
        
        // If we can'tidentify the label, skip this row
        if(label_name == "")
            continue;
        
        // Get the drawn pictograms
        for (int j=0; j < DRAWN_PICS_COLS; j++) {
            
            current_drawn_pictogram_zone.x = first_drawn_pictogram_zone.x + j*drawn_pictogram_padding.x;
            
            Rect current_drawn_pictogram_zone_cropped = current_drawn_pictogram_zone;
            
            // Crop
            current_drawn_pictogram_zone_cropped.x += drawn_pictogram_cropping.x;
            current_drawn_pictogram_zone_cropped.y += drawn_pictogram_cropping.y;
            current_drawn_pictogram_zone_cropped.width -= drawn_pictogram_cropping.width;
            current_drawn_pictogram_zone_cropped.height -= drawn_pictogram_cropping.height;
            
            // Write output files
            string outputName = this->output_folder + label_name + "_" + scripter + "_" + page + "_" + to_string(i) + "_" + to_string(j);
            imwrite(outputName + ".png", normalized_sheet(current_drawn_pictogram_zone_cropped));
            utils::writeDescriptionFile(outputName, label_name, scripter, page , i, j);

        }
    }
    this->success_cpt++;
}

/**
 * \brief   Extracts all the pictograms from sheets contained in input folder
 */
void Extractor::extractFromInputFolder() {
    
    DIR* dir = utils::openDir(this->input_folder);
    struct dirent* readFile = NULL;
    
    while ((readFile = readdir(dir)) != NULL) {
        
        if(!regex_match(readFile->d_name, utils::hiddenFileRegex)) {
            cout << "### Handling file : " << readFile->d_name << endl;
            this->extractFromFile(readFile->d_name);
        }
    }
    
    utils::closeDir(dir);
    cout << "Sheets partially or completly extracted : " << this->success_cpt << endl;
}
