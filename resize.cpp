// Project UID af1f95f547e44c8ea88730dfb185559d

#include <iostream>
#include <fstream>
#include "processing.h"

using namespace std;

int main(int argc, char* argv[]) {
  
  // Error message when the argument is not 4 or 5
  if (argc < 4 || argc > 5) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  string inFileName = argv[1];
  string outFileName = argv[2];

  // Reading Input File
  ifstream fin;
  fin.open(inFileName);

  // Error message when the file is not opening
  if(!fin.is_open()) {
    cout << "Error opening file: " << inFileName << endl;
    return 1;
  }

  // Create an image and initialize to input file
  Image *img = new Image;
  Image_init(img, fin);

  // Assign the desired width to an int variable
  int newWidth = atoi(argv[3]);
  int newHeight = Image_height(img);
  
  // If there are 5 arguments, assign the desired height to an int variable
  if (argc == 5) {
    newHeight = atoi(argv[4]);
  }

  // Error message when argument violates newWidth and newHeight rules
  if (newWidth <= 0 || newWidth > Image_width(img)
      || newHeight <= 0 || newHeight > Image_height(img)) {

    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;

  }

  fin.close();

  // File Output
  ofstream fout;
  fout.open(outFileName);

  // Error message when the file is not opening
  if(!fout.is_open()) {
    cout << "Error opening file: " << outFileName << endl;
    return 1;
  }

  // Resizing process
  seam_carve(img, newWidth, newHeight);
  Image_print(img,fout);

  fout.close();

  delete img; // delete img
  
  return 0;
}