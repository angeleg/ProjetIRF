#Projet IRF

##TEAM
* Berthier Guillaume (SRC)
* Géraud Angèle (INFO)
* Le Goff Baptiste (INFO)

##HYPOTHESES

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

* 665 files succesfully treated (completly or partially, included trap files that are ignored)
* __Success rate on parsing files : 83%__

---

* 19921 pictograms extracted in total
* __Success rate on extracting pictograms with label identified : 71%__

###What can be done
    
1. Dynamically detect the drawn and printed pictograms areas instead of setting a static zone
2. Handle the case when the sheet is crooked


