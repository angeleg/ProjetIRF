#Projet IRF

## HYPOTHESES

    1. The drawn pictograms matrix has to be contained int the region starting at the point (500,700) and having a width of 1900 px and a height of 2500 px
    2. The printed pictograms matrix has to be contained int the region starting at the point (200,700) and having a width of 260 px and a height of 2500 px


##METHOD USED

###Drawn Pictograms extraction

    1. Isolate the drawn pictograms section
    2. Try to automaticaly detect the squared shapes in the image
    3. If not enough squares have been found, ignore the current image
    4. Compute average position of each row/column
    5. Extract from the calculated position obtained in previous step

###Printed pictograms recognition

    1. Isolate the printed pictograms section
    2. For each line found in step 4 of pictograms extraction, isolate the printed pictogram
    3. Compare the printed pictogram from previous step with template ones, and return the best match found

##PERFORMANCE RESULTS

###Success Rate

    - 650 files succesfully parsed (included trap files that are ignored)
    - 156 files generating errors
    - **Success rate on parsing files : 80,65%**

    - 21476 pictograms extracted in total
    - 3110 pictograms extracted without matching any label
    - **Success rate on matching label : 85,52%**

###What can be done
    
    1. Dynamically detect the drawn and printed pictograms areas instead of setting a static zone
    2. Handle the case when the sheet is crooked
    

###Files generating errors 

00117.png, 00316.png, 00504.png, 00511.png, 00700.png, 00706.png, 00708.png, 00710.png, 00713.png, 00715.png, 00818.png,
00904.png, 00906.png, 00914.png, 01002.png, 01017.png, 01112.png, 01211.png, 01213.png, 01300.png, 01301.png, 01302.png,
01303.png, 01306.png, 01310.png, 01311.png, 01316.png, 01317.png, 01410.png, 01415.png, 01416.png, 01418.png, 01421.png,
01500.png, 01501.png, 01503.png, 01506.png, 01510.png, 01606.png, 01621.png, 01702.png, 01707.png, 01709.png, 01712.png,
01716.png, 01803.png, 01805.png, 01808.png, 01809.png, 01814.png, 01819.png, 01821.png, 01902.png, 01920.png, 02003.png,
02005.png, 02109.png, 02110.png, 02112.png, 02115.png, 02201.png, 02208.png, 02219.png, 02302.png, 02303.png, 02309.png,
02316.png, 02320.png, 02321.png, 02400.png, 02407.png, 02410.png, 02411.png, 02420.png, 02421.png, 02503.png, 02507.png,
02511.png, 02515.png, 02601.png, 02602.png, 02603.png, 02606.png, 02608.png, 02609.png, 02616.png, 02621.png, 02702.png,
02704.png, 02709.png, 02713.png, 02717.png, 02802.png, 02807.png, 02812.png, 02815.png, 02818.png, 02821.png, 02902.png,
02904.png, 02907.png, 02909.png, 02913.png, 02914.png, 02916.png, 02917.png, 03013.png, 03015.png, 03100.png, 03101.png,
03102.png, 03103.png, 03104.png, 03105.png, 03106.png, 03107.png, 03108.png, 03109.png, 03110.png, 03111.png, 03112.png,
03115.png, 03118.png, 03202.png, 03206.png, 03209.png, 03212.png, 03215.png, 03221.png, 03301.png, 03302.png, 03303.png,
03304.png, 03305.png, 03306.png, 03307.png, 03308.png, 03309.png, 03310.png, 03311.png, 03312.png, 03313.png, 03316.png,
03317.png, 03318.png, 03320.png, 03321.png, 03402.png, 03404.png, 03406.png, 03415.png, 03417.png, 03418.png, 03419.png
03420.png, 03421.png


