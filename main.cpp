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
#include<cmath>

unsigned char image[SIZE][SIZE];

void loadImage ();
void filterChoice();
void saveImage ();

int main() {
    loadImage();
    while (true) {
        filterChoice();
    }
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
void enlargeImage() {
    unsigned char enlargedImage[SIZE][SIZE];

    int enlargeChoice = 1 ;
    cout << "\nWhich quarter to enlarge 1, 2, 3 or 4?\n";


    cin >> enlargeChoice;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            switch(enlargeChoice) {
                case 1 :
                    // first quarter
                    enlargedImage[i][j] = image[i / 2][j / 2];
                    break;
                case 2 :
                    // second quarter
                    enlargedImage[i][j] = image[i / 2][SIZE / 2 + j / 2];
                    break ;
                case 3 :
                    // third quarter
                    enlargedImage[i][j] = image[SIZE / 2 + i / 2][j / 2];
                    break;
                case 4 :
                    // Fourth quarter
                    enlargedImage[i][j] = image[SIZE / 2 + i / 2][SIZE / 2 + j / 2];
                    break;
                default :
                    break;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = enlargedImage[i][j];
        }
    }


}
bool isShuffleValid(string& word){
    for(char& c : word){
        if (c != '1' && c!= '2' && c!='3' && c!='4') {
            return false;
        }
    }
    return true;

}
void shuffleImage(){
    unsigned char shuffledImage[SIZE][SIZE];

    string userShuffle ;
    cout << "Please enter your shuffle order:";
    cin >> userShuffle;

    while (!isShuffleValid(userShuffle) && userShuffle.length() != 4){
        cout << "\nInvalid shuffle order, please re-enter a valid one :\n";

    }


    for (int k = 0; k < 4; ++k) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                switch(k){
                    case 0 :
                        switch ( userShuffle[k]) {
                            case '1':
                                shuffledImage[i / 2][j / 2] = image[i / 2][j / 2];
                                break;
                            case '2':
                                shuffledImage[i / 2][j / 2] = image[i / 2][SIZE / 2 + j / 2];
                                break;
                            case '3' :
                                shuffledImage[i / 2][j / 2]= image[SIZE / 2 + i / 2][j / 2];
                                break;
                            case '4' :
                                shuffledImage[i / 2][j / 2] = image[SIZE / 2 + i / 2][SIZE / 2 + j / 2];
                                break;
                        }
                        break;

                    case 1 :
                        switch (userShuffle[k]) {
                            case '1':
                                shuffledImage[i / 2][SIZE / 2 + j / 2] = image[i / 2][j / 2];
                                break;
                            case '2':
                                shuffledImage[i / 2][SIZE / 2 + j / 2] = image[i / 2][SIZE / 2 + j / 2];
                                break;
                            case '3' :
                                shuffledImage[i / 2][SIZE / 2 + j / 2]= image[SIZE / 2 + i / 2][j / 2];
                                break;
                            case '4' :
                                shuffledImage[i / 2][SIZE / 2 + j / 2] = image[SIZE / 2 + i / 2][SIZE / 2 + j / 2];
                                break;
                        }
                        break;
                    case 2 :
                        switch ( userShuffle[k]) {
                            case '1':
                                shuffledImage[SIZE / 2 + i / 2][j / 2] = image[i / 2][j / 2];
                                break;
                            case '2':
                                shuffledImage[SIZE / 2 + i / 2][j / 2] = image[i / 2][SIZE / 2 + j / 2];
                                break;
                            case '3' :
                                shuffledImage[SIZE / 2 + i / 2][j / 2]= image[SIZE / 2 + i / 2][j / 2];
                                break;
                            case '4' :
                                shuffledImage[SIZE / 2 + i / 2][j / 2] = image[SIZE / 2 + i / 2][SIZE / 2 + j / 2];
                                break;
                        }
                        break;
                    case 3 :
                        switch ( userShuffle[k]) {
                            case '1':
                                shuffledImage[SIZE / 2 + i / 2][SIZE / 2 + j / 2] = image[i / 2][j / 2];
                                break;
                            case '2':
                                shuffledImage[SIZE / 2 + i / 2][SIZE / 2 + j / 2] = image[i / 2][SIZE / 2 + j / 2];
                                break;
                            case '3' :
                                shuffledImage[SIZE / 2 + i / 2][SIZE / 2 + j / 2]= image[SIZE / 2 + i / 2][j / 2];
                                break;
                            case '4' :
                                shuffledImage[SIZE / 2 + i / 2][SIZE / 2 + j / 2] = image[SIZE / 2 + i / 2][SIZE / 2 + j / 2];
                                break;
                        }
                        break;




                }
            }
        }

    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = shuffledImage[i][j];
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

void detect_edges(){
    BW_filter();
    unsigned char clone[SIZE][SIZE]; //2D array that has the same size as the image

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            clone[i][j] = image[i][j]; //copying the image pixels values into "clone" 2D array
        }
    }

    for (int i = 1; i < 255; i++) {
        for (int j = 1; j < 255; j++) {
            if (clone[i-1][j-1]==0 and clone[i-1][j]==0 and clone[i-1][j+1]==0
            and clone[i][j-1]==0 and clone[i][j+1]==0
            and clone[i+1][j-1]==0 and clone[i+1][j]==0 and clone[i+1][j+1]==0){
                image[i][j] = 255;
            }
        }
    }

}

void mirror(){

    string type_of_mirror;
    cout<< "\nPlease Choose type of mirror to apply to your image\n"
        << "\nPress 1 for Left Part Mirror "
        << "\nPress 2 for Right Part Mirror"
        << "\nPress 3 for Upper Part Mirror"
        << "\nPress 4 for Lower Part Mirror" << endl;
    cin >> type_of_mirror;

    while (true) {
        if (type_of_mirror == "1") {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < 128; j++) {
                    image[i][255-j] = image[i][j];
                }
            }
            break;
        }
        else if (type_of_mirror == "2"){
            for (int i = 0; i < SIZE; i++) {
                for (int j = 128; j < 256; j++) {
                    image[i][255-j] = image[i][j];
                }
            }
            break;
        }
        else if (type_of_mirror == "3"){
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image[255-i][j] = image[i][j];
                }
            }
            break;
        }
        else if (type_of_mirror == "4"){
            for (int i = 128; i < 256; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image[255-i][j] = image[i][j];
                }
            }
            break;
        }
        else{
            cout << "\n invalid input... please try again" << endl;
            cin >> type_of_mirror;
        }
    }
}


void darken_or_lighten() {
    unsigned char image2[SIZE][SIZE];
    int choice ;
    cout <<"enter 0 to darken or 1 to lighten : ";
    cin >> choice;
    if (choice == 0 ){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image2[i][j] = (image[i][j] / 2 );
            }
        }
    }
    else if (choice==1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image2[i][j] =  (pow(image[i][j],.8)-120) ;
            }
        }
    }
    for (int i =0 ;i<SIZE;i++){
        for (int j=0 ; j< SIZE;j++){
            image[i][j]=image2[i][j];
        }
    }

}
void merge() {
    unsigned char image2[SIZE][SIZE];
    unsigned char image3 [SIZE][SIZE];
    char image2FileName[100];
    cout << "Enter the source image2 file name:";
    cin >> image2FileName;
    strcat (image2FileName, ".bmp");
    readGSBMP(image2FileName, image2);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image3[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
    for (int i =0 ;i<SIZE;i++){
        for (int j=0 ; j< SIZE;j++){
            image[i][j]=image3[i][j];
        }
    }
}

void blurfilter(){
    long long avg=0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = i; k < i+7; k++) {
                for (int l = j; l < j+7; l++) {
                    avg+=(image[k][l]);
                }
            }
            avg=avg/49;
            image[i][j]=avg;
            avg=0;
        }
    }
}

void shrink () {
    unsigned char image2[SIZE][SIZE];
    int choice ;
    cout <<"for 1/2 shrink photo press 1 \n";
    cout <<"for 1/3 shrink photo press 2 \n";
    cout <<"for 1/4 shrink photo press 3 \n";
    cin >> choice;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image2[i][j]=255;
        }
    }
    if (choice == 1){
        for (int i = 0; i < SIZE; i+=2) {
            for (int j = 0; j < SIZE; j+=2) {
                image2[i / 2][j / 2] =  image[i][j];
            }
        }

    }

    else if (choice == 2){
        for (int i = 0; i < SIZE; i+=3) {
            for (int j = 0; j < SIZE; j+=3) {
                image2[i / 3][j / 3] =  image[i][j];
            }
        }

    }
    else if (choice == 3){
        for (int i = 0; i < SIZE; i+=4) {
            for (int j = 0; j < SIZE; j+=4) {
                image2[i / 4][j /4 ] =  image[i][j];
            }
        }

    }
     for (int i =0 ;i<SIZE;i++){
        for (int j=0 ; j< SIZE;j++){
            image[i][j]=image2[i][j];
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
               "\nPress 5 to darken or lighten filter"
               "\nPress 6 to merge filter"
               "\nPress 7 to enlarge the image"
               "\nPress 8 to shuffle the image"
               "\nPress 9 to blur the image"
               "\nPress 10 to shrink the image"
               "\nPress 11 to detect image edges"
               "\nPress 12 to mirror image"
               "\nPress 13 to save the image"
               "\nPress 0 to Exit"
               "\n-----------------------------------\n";


        cin >> filterChoice;

        if (filterChoice >= 0 && filterChoice <= 13) {

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
                case 5 :
                    darken_or_lighten() ;
                    validInput = true;
                    break;
                case 6 :
                    merge();
                    validInput = true;
                    break;
                case 7 :
                    enlargeImage();
                    validInput = true;
                    break;
                case 8 :
                    shuffleImage();
                    validInput = true;
                    break;
                case 9 :
                    blurfilter();
                    validInput = true;
                    break;
                case 10 :
                    shrink();
                    validInput = true;
                    break;
                case 11 :
                    detect_edges();
                    validInput = true;
                    break;
                case 12 :
                    mirror();
                    validInput = true;
                    break;
                case 13 :
                    saveImage();
                    validInput = true;
                    break;
                default:
                    cout << "\nInvalid input, Please try again...\n";
                    break;
            }
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



