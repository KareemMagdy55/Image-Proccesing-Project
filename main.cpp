#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include "bmplib.h"

unsigned char image[SIZE][SIZE];

void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name:";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}


void BW_filter(){
    int counter = 0 ;
    int grayAvg;


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            counter += image[i][j] ;
        }
    }

    grayAvg = counter / (SIZE * SIZE) ;


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
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            image[i][j] = 255 - image[i][j] ;
        }
    }

}

/* Put your filter function here
 * then put it in (filterChoice) message
 * then put it in (filterChoice) switch case
  */


void filterChoice(){
    int filterChoice = 0 ;
    cout << "Please Choose a filter to apply it to your image"
            "\nPress 1 for Black & White filter "
            "\nPress 2 for Invert image filter"
            "\nPress 0 to Exit ";

    cin >> filterChoice;
    switch (filterChoice) {
        case 0 :
            exit(0);
            break;
        case 1:
            BW_filter();
            break;
        case 2 :
            invertFilter();
            break;
        default:
            break;
    }

}


void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}



int main() {
    loadImage();
    filterChoice();
    saveImage();
}
