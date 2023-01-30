// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Matrix.h"

using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
  
  // To check the REQUIRES clauses
  assert(0 < width && width <= MAX_MATRIX_WIDTH);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);

  mat->width = width;
  mat->height = height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  
  int width = mat->width;
  int height = mat->height;

  os << width << " " << height << endl;

  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      os << mat->data[width * row + col] << " ";
    }
    os << endl;
  }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  
  return mat->width;

}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {

  return mat->height;

}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  
  // Calculating the index of the element
  int index = ptr - mat->data;

  int row = index / Matrix_width(mat);

  return row;

}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  
  // Calculating the index of the element
  int index = ptr - mat->data;

  return index % Matrix_width(mat);

}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  
  // To check the REQUIRES clauses
  assert(0 <= row && row < mat->height);
  assert(0 <= column && column < mat->width);

  // Conversion of nth element of 1D array from 2D array:
  // row * width + column
  int* pointer = &mat->data[row * Matrix_width(mat) + column];

  return pointer;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {

  // To check the REQUIRES clauses
  assert(0 <= row && row < mat->height);
  assert(0 <= column && column < mat->width);

  // Conversion of nth element of 1D array from 2D array:
  // row * width + column
  const int* pointer = &mat->data[row * Matrix_width(mat) + column];
  
  return pointer; 
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {

  for (int i = 0; i < mat->width * mat->height; ++i) {
    mat->data[i] = value;
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  
  // Fill first and last row
  int max_index = mat->width * mat->height - 1;

  for (int i = 0; i < mat->width; ++i) {
    mat->data[i] = value;
    mat->data[max_index - i] = value;
  }

  // Fill first and last column for each row
  int left_border = mat->width;
  int right_border = (mat->width * 2) - 1;

  for (int j = 0; j < mat->height - 2; ++j) {
    mat->data[left_border + (mat->width * j)] = value;
    mat->data[right_border + (mat->width * j)] = value;
  }

}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int greatest = mat->data[0];

  for (int i = 0; i < mat->height * mat->width; ++i) {
    if (greatest < mat->data[i]) {
      greatest = mat->data[i];
    }
  }

  return greatest;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {

  // To check the REQUIRES Clauses
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  // Starting index of column_start
  int index = (row * Matrix_width(mat)) + column_start;
    
    int temp = 0;
    
    // Initializing minimum value to the first element
    int min = mat->data[index];
    
    // Loop until (column_end - 1) value
    for (int i = 1; i < (column_end - column_start); ++i){
        
        // If the value of the element is smaller than min
        if (mat->data[index + i] < min){

          // Set the min value
          min = mat->data[index + i];

          // Store "i" because it is the index of the particular region
          temp = i;
        }
    }
    
    int min_column = column_start + temp;

    return min_column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
                              
  // To check the REQUIRES Clauses
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);
  
  // First index of the given row
  int firstIndex = Matrix_width(mat) * row;
    
  int minValue = mat->data[firstIndex + Matrix_column_of_min_value_in_row(mat, row, column_start, column_end)];
  return minValue;
}
