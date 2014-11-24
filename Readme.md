#Projet IRF

## HYPOTHESES

    1. The drawn pictograms matrix has to be contained int the region starting at the point (500,700) and having a width of 1900 px and a height of 2500 px
    2. The printed pictograms matrix has to be contained int the region starting at the point (200,700) and having a width of 260 px and a height of 2500 px


##METHOD USED

###Drawn Pictograms extraction

    1. Isolate the drawn pictograms section
    2. Try to automaticaly detect the square shapes in the image
    3. Compute average position of each row/column
    4. Extract from the calculated position obtained in previous step

###Printed pictograms recognition
    1. Isolate the printed pictograms section
    2. For each line found in step 3 of pictograms extraction, isolate the printed pictogram
    3. Compare the printed pictogram from step 2 with template ones, and return the best match found

##PERFORMANCE RESULTS

Problem found with files : 



