/*
        FCI – Programming 1 – 2022 - Assignment 3

        Program Name: xxxxxx.cpp
        Last Modification Date: xx/xx/xxxx

        Author1 : Abdullah Ibrahim  ID : 20210590
        Author2 : Kareem Magdy      ID : 20211071
        Author3 : Mohammed Reyad    ID : 20211074

        Teaching Assistant: Eng. Afaf Abdelmonem

        Purpose:..........
*/

#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include "bmplib.h"

unsigned char image[SIZE][SIZE];

void loadImage ();
void filterChoice();
void saveImage ();

int main() {
    loadImage();
    filterChoice();
    saveImage();
}


void loadImage () {
    char imageFileName[100];
    bool imgValidation = false;

    while (!imgValidation) {
        // Get gray scale image file name
        cout << "Enter the source image file name:";
        cin >> imageFileName;

        // Add to it .bmp extension and load image
        strcat(imageFileName, ".bmp");


        if (! readGSBMP(imageFileName, image)) {
            imgValidation = true;
        }
        else { //if the Image is not valid, reRun loadImage()
            cout << "\nImage not found, Please try again.\n";
        }
    }
}
void rotateImage(){
    unsigned char newImage[SIZE][SIZE];
    int rotationChoice = 1 ;
    cout << "Press 1 for 90 degree rotation\nPress 2 for 180 degree rotation\nPress 3 for 270 degree rotation";
    cin >> rotationChoice;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            switch(rotationChoice) {
                case 1 :
                    // 90 degree rotation
                    newImage[i][j] = image[SIZE - 1 - j][ i];
                    break;
                case 2 :
                    // 180 degree rotation
                    newImage[i][j] = image[SIZE - 1 - i][SIZE - 1 - j];
                    break ;
                case 3 :
                    // 270 degree rotation
                    newImage[i][j] = image[j][SIZE - 1 - i] ;
                    break;
                default :
                    break;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j < SIZE; ++j) {
            image[i][j] = newImage[i][j] ;
      }
    }
}

void BW_filter(){
    int counter = 0 ;
    int grayAvg;

    // calculate gray color average
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            counter += image[i][j] ;
        }
    }

    grayAvg = counter / (SIZE * SIZE) ;

// every color above average will be White (  255 )
// every color under average will be Black (   0  )
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > grayAvg){
                image[i][j] = 255 ;
            }else{
                image[i][j] = 0 ;
            }
        }
    }

}

void invertFilter(){
    // every gray pixel is turned to opposite level of brightness  (255 – pixel value)

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            image[i][j] = 255 - image[i][j] ;
        }
    }

}

// Filter to flip the image Vertically or Horizontally
void flipImage(){
    string type_of_flip;
    unsigned char clone[SIZE][SIZE]; //2D array that has the same size as the image

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            clone[i][j] = image[i][j]; //copying the image pixels values into "clone" 2D array

        }
    }

    cout << "\nFlip (H) horizontally or (V) vertically ?\n";
    cin >> type_of_flip; // Take the type of the flip from user
    while (true) {
        if (type_of_flip == "h"||type_of_flip == "H") {
            // To flip the image "Horizontally"
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {

                    image[i][j] = clone[i][255 - j]; //Flipping the matrix values horizontally

                }
            }
        break;//breaks the biggest loop after flipping the image horizontally
        }
        else if (type_of_flip == "v"||type_of_flip == "V"){
            // To flip the image "Vertically"
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {

                    image[i][j] = clone[255 - i][j]; //Flipping the matrix values vertically

                }
            }
        break; //breaks the biggest loop after flipping the image vertically
        }
        else{
            cout << "invalid input! please enter H or V..." << endl;
            cin >> type_of_flip;
        }
    }




}

/* Put your filter function here
 * then put it in (filterChoice) message
 * then put it in (filterChoice) switch case
  */


void filterChoice(){
   bool validInput = false ;

   do {
       int filterChoice = 0;
       cout << "\n-----------------------------------\n"
               "Please Choose a filter to apply it to your image\n"
               "\nPress 1 for Black & White filter "
               "\nPress 2 for Invert image filter"
               "\nPress 3 to rotate image filter"
               "\nPress 4 to flip image filter"
               "\nPress 0 to Exit"
               "\n-----------------------------------\n";


       cin >> filterChoice;

       switch (filterChoice) {
           case 0 :
               exit(0);
           case 1:
               BW_filter();
               validInput = true;
               break;
           case 2 :
               invertFilter();
               validInput = true;
               break;
           case 3 :
               rotateImage();
               validInput = true;
               break;
           case 4 :
               flipImage();
               validInput = true;
               break;
           default:
               cout << "\nInvalid input, Please try again\n";
               break;
       }
   }while (! validInput);




}

void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "-----------------------------------\n";
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}



