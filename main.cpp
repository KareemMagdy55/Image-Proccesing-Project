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

    // Get gray scale image file name
    cout << "Enter the source image file name:";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
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

/* Put your filter function here
 * then put it in (filterChoice) message
 * then put it in (filterChoice) switch case
  */


void filterChoice(){
    int filterChoice = 0 ;
    cout <<  "\n-----------------------------------\n"
            "Please Choose a filter to apply it to your image\n"
            "\nPress 1 for Black & White filter "
            "\nPress 2 for Invert image filter"
            "\nPress 3 to rotate image filter"
            "\nPress 0 to Exit"
            "\n-----------------------------------\n";


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
        case 3 :
            rotateImage();
        default:
            break;
    }

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



