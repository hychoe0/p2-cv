// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.

TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADDITIONAL TESTS

// Basic Test for returning row and column
TEST(test_matrix_row_and_col) {
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 5;

  // Initializing Matrix
  Matrix_init(mat, width, height);

  // General
  const int* ptr = Matrix_at(mat, 2, 1);
  assert(Matrix_row(mat, ptr) == 2);
  assert(Matrix_column(mat, ptr) == 1);

  // General
  const int* ptr2 = Matrix_at(mat, 3, 2);
  assert(Matrix_row(mat, ptr2) == 3);
  assert(Matrix_column(mat, ptr2) == 2);

  // Edge
  const int* ptr3 = Matrix_at(mat, 0, 0);
  assert(Matrix_row(mat, ptr3) == 0);
  assert(Matrix_column(mat, ptr3) == 0);

  // Edge
  const int* ptr4 = Matrix_at(mat, 1, 0);
  assert(Matrix_row(mat, ptr4) == 1);
  assert(Matrix_column(mat, ptr4) == 0);

  delete mat; // delete the Matrix
}

// Basic Test for returning width and height after initialization
TEST(test_matrix_init_) {
  Matrix *mat = new Matrix;

  const int width = 4;
  const int height = 6;

  // Initializing Matrix
  Matrix_init(mat, width, height);

  // General
  ASSERT_EQUAL(Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);

  delete mat; // delete the Matrix

  Matrix *mat2 = new Matrix;

  const int width1 = 1;
  const int height1 = 1;

  // Initializing Matrix
  Matrix_init(mat2, width1, height1);

  // Testing Minimum Width and Height
  ASSERT_EQUAL(Matrix_width(mat2), width1);
  ASSERT_EQUAL(Matrix_height(mat2), height1);

  delete mat2; // delete the Matrix

  Matrix *mat3 = new Matrix;

  const int width2 = MAX_MATRIX_WIDTH;
  const int height2 = MAX_MATRIX_HEIGHT;

  //Initializing Matrix
  Matrix_init(mat3, width2, height2);

  // Testing Maximum Width and Height
  ASSERT_EQUAL(Matrix_width(mat3), width2);
  ASSERT_EQUAL(Matrix_height(mat3), height2);

  delete mat3; // delete the Matrix
}

TEST(test_matrix_fill) {
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 5;
  int value = 37;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  // Test every element in the matrix
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
    }
  }

  delete mat; // delete the Matrix
}

TEST(test_matrix_fill_border) {
  Matrix *mat = new Matrix;

  const int width = 6;
  const int height = 5;
  int value = 37;

  Matrix_init(mat, width, height);

  //Initializing elements to 0s
  Matrix_fill(mat, 0);
  Matrix_fill_border(mat, value);

  // Test every element at the border of the matrix
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      if (row == 0 || col == 0 || row == height - 1 || col == width - 1) {
        ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
      }
      else {
        ASSERT_EQUAL(*Matrix_at(mat, row, col), 0);
      }
    }
  }

  delete mat; // delete the Matrix
}

TEST(test_matrix_max) {

  // Test Case #1
  Matrix *mat = new Matrix;

  const int width = 2;
  const int height = 2;

  Matrix_init(mat, width, height);

  //Initializing elements to 0s
  Matrix_fill(mat, 0);

  // Test Case #1-1 (General 2 x 2)
  *Matrix_at(mat, 0, 0) = 2;
  *Matrix_at(mat, 0, 1) = 4;
  *Matrix_at(mat, 1, 0) = 1;
  *Matrix_at(mat, 1, 1) = 3;
  
  ASSERT_EQUAL(Matrix_max(mat), 4);

  //Initializing elements to 0s
  Matrix_fill(mat, 0);

  // Test Case #1-2 (Edge 2 x 2)
  *Matrix_at(mat, 0, 0) = 4;
  *Matrix_at(mat, 0, 1) = 1;
  *Matrix_at(mat, 1, 0) = 1;
  *Matrix_at(mat, 1, 1) = 0;

  ASSERT_EQUAL(Matrix_max(mat), 4);

  //Initializing elements to 0s
  Matrix_fill(mat, 0);

  // Test Case #1-3 (Multiple Edges 2 x 2)
  *Matrix_at(mat, 0, 0) = 4;
  *Matrix_at(mat, 0, 1) = 3;
  *Matrix_at(mat, 1, 0) = 3;
  *Matrix_at(mat, 1, 1) = 4;

  ASSERT_EQUAL(Matrix_max(mat), 4);

  delete mat;

  // Test Case #2
  Matrix *mat1 = new Matrix;

  const int width1 = 5;
  const int height1 = 4;

  Matrix_init(mat1, width1, height1);

  //Initializing elements to 30s
  Matrix_fill(mat1, 30);

  // Test Case #2-1 (General 5 x 4)
  *Matrix_at(mat1, 3, 2) = 31;
  ASSERT_EQUAL(Matrix_max(mat1), 31);

  //Initializing elements to 30s
  Matrix_fill(mat1, 30);

  // Test Case #2-2 (First Edge 5 x 4)
  *Matrix_at(mat1, 0, 0) = 31;
  ASSERT_EQUAL(Matrix_max(mat1), 31);

  //Initializing elements to 30s
  Matrix_fill(mat1, 30);

  // Test Case #2-2 (Last Edge 5 x 4)
  *Matrix_at(mat1, 3, 4) = 31;
  ASSERT_EQUAL(Matrix_max(mat1), 31);

  //Initializing elements to 30s
  Matrix_fill(mat1, 30);

  // Test Case #2-3 (Multiple Edges 5 x 4)
  *Matrix_at(mat1, 2, 4) = 31;
  *Matrix_at(mat1, 0, 4) = 31;
  *Matrix_at(mat1, 2, 0) = 31;
  ASSERT_EQUAL(Matrix_max(mat1), 31);

  delete mat1;
}

TEST(test_matrix_column_of_min_value_in_row) {
  Matrix *mat = new Matrix;

  const int width = 6;
  const int height = 5;

  Matrix_init(mat, width, height);

  //Initializing elements to 0s
  Matrix_fill(mat, 0);

  // Test Case #1 (General)
  int row1 = 2;
  int col_start1 = 1;
  int col_end1 = 4;
  *Matrix_at(mat, 2, 1) = 2;
  *Matrix_at(mat, 2, 2) = 4;
  *Matrix_at(mat, 2, 3) = 1;
  *Matrix_at(mat, 2, 4) = 3;
  
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, row1, col_start1, col_end1), 3);

  // Test Case #2 (Edge)
  // Testing Negative Number and the leftmost minimums

  int row2 = 1;
  int col_start2 = 0;
  int col_end2 = 5;
  *Matrix_at(mat, 1, 0) = -1;
  *Matrix_at(mat, 1, 1) = 1;
  *Matrix_at(mat, 1, 2) = -1;
  *Matrix_at(mat, 1, 3) = 1;
  *Matrix_at(mat, 1, 4) = -1;
  
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, row2, col_start2, col_end2), 0);

  // Test Case #3 (Edge)
  // Testing Last Edge in the given row

  int row3 = 0;
  int col_start3 = 0;
  int col_end3 = 6;
  *Matrix_at(mat, 0, 0) = 4;
  *Matrix_at(mat, 0, 1) = 4;
  *Matrix_at(mat, 0, 2) = 5;
  *Matrix_at(mat, 0, 3) = 12;
  *Matrix_at(mat, 0, 4) = 23;
  *Matrix_at(mat, 0, 5) = 3;
  
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, row3, col_start3, col_end3), 5);

  delete mat; // delete the Matrix
}

TEST(test_matrix_min_value_in_row) {
  Matrix *mat = new Matrix;

  const int width = 6;
  const int height = 5;
  const int value = 0;

  Matrix_init(mat, width, height);

  // Initializing the matrix to 0s
  Matrix_fill(mat, value);

  *Matrix_at(mat, 1, 0) = -1;
  *Matrix_at(mat, 1, 1) = 1;
  *Matrix_at(mat, 1, 2) = -1;
  *Matrix_at(mat, 1, 3) = 1;
  *Matrix_at(mat, 1, 4) = -1;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 5), -1);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 6), -1);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 2, 3), -1);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 2, 4), -1);

  delete mat; // delete the Matrix
}

TEST(test_matrix_irr_shapes) {

  // 1 x 5 Matrix
  Matrix *mat = new Matrix;

  const int width = 1;
  const int height = 5;
  int value = 10;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  // Test every element in the matrix
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
    }
  }

  // Testing min and max within the same values (leftmost)
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 1), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 1), value);
  ASSERT_EQUAL(Matrix_max(mat), value);

  delete mat; // delete the Matrix

  // 4 x 1 Matrix
  Matrix *mat2 = new Matrix;

  const int width2 = 4;
  const int height2 = 1;
  int value2 = 11;

  Matrix_init(mat2, width2, height2);
  Matrix_fill(mat2, value2);

  // Test every element in the matrix
  for (int row2 = 0; row2 < height2; ++row2) {
    for (int col2 = 0; col2 < width2; ++col2) {
      ASSERT_EQUAL(*Matrix_at(mat2, row2, col2), value2);
    }
  }

  // Testing min and max within the same values (leftmost)
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 0, 0, 4), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 0, 0, 4), value2);
  ASSERT_EQUAL(Matrix_max(mat2), value2);

  delete mat2; // delete the Matrix

  // 3 x 3 Matrix
  Matrix *mat3 = new Matrix;

  const int width3 = 3;
  const int height3 = 3;
  int value3 = 13;

  Matrix_init(mat3, width3, height3);
  Matrix_fill(mat3, value3);

  // Test every element in the matrix
  for (int row3 = 0; row3 < height3; ++row3) {
    for (int col3 = 0; col3 < width3; ++col3) {
      ASSERT_EQUAL(*Matrix_at(mat3, row3, col3), value3);
    }
  }

  // Testing min and max within the same values (leftmost)
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat3, 0, 0, 3), 0);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat3, 2, 0, 3), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat3, 0, 0, 3), value3);
  ASSERT_EQUAL(Matrix_max(mat3), value3);

  delete mat3; // delete the Matrix
}

TEST(test_matrix_extended) {
  // Matrix_max
  Matrix *mat = new Matrix;

  const int width = 4;
  const int height = 5;
  Matrix_init(mat, width, height);

  // Fill 4x5 Matrix by negative number and find max
  // Fill Matrix with negative number
  Matrix_fill(mat, -5);

  ASSERT_EQUAL(Matrix_max(mat), -5);

  // Change a single element to 0 in each row and find max
  // General
  *Matrix_at(mat, 0, 2) = 0;
  ASSERT_EQUAL(Matrix_max(mat), 0);
  // Reset
  *Matrix_at(mat, 0, 2) = -5;
  ASSERT_EQUAL(Matrix_max(mat), -5);
  // Edge
  *Matrix_at(mat, 1, 0) = -1;
  ASSERT_EQUAL(Matrix_max(mat), -1);
  // Reset
  *Matrix_at(mat, 1, 0) = -5;
  ASSERT_EQUAL(Matrix_max(mat), -5);
  // Edge (Last)
  *Matrix_at(mat, 4, 3) = 0;
  ASSERT_EQUAL(Matrix_max(mat), 0);

  // Fill Matrix with 0s
  Matrix_fill(mat, 0);

  ASSERT_EQUAL(Matrix_max(mat), 0);

  // General
  *Matrix_at(mat, 0, 1) = -1;
  ASSERT_EQUAL(Matrix_max(mat), 0);
  // Edge
  *Matrix_at(mat, 0, 3) = -3;
  ASSERT_EQUAL(Matrix_max(mat), 0);

  delete mat;

  // Matrix_col_min and Matrix_min in a row
  Matrix *mat2 = new Matrix;

  const int width2 = 5;
  const int height2 = 4;
  const int value2 = 2;
  const int newValue = 1;
  const int newValue2 = -1;

  Matrix_init(mat2, width2, height2);

  // Initializing the matrix to 2s
  Matrix_fill(mat2, value2);
  // Fill Border 5x4 Matrix with newValue (positive)
  Matrix_fill_border(mat2, newValue);

  // First Row (Border)
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 0, 0, 5), newValue); // whole row
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 0, 0, 4), newValue); // edge
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 0, 1, 5), newValue); // edge
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 0, 1, 4), newValue); // general
  
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 0, 0, 5), 0); // whole row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 0, 0, 4), 0); // edge
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 0, 1, 5), 1); // edge
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 0, 1, 4), 1); // general
  
  // Second Row (Edge)
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 1, 0, 5), newValue); // whole row
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 1, 0, 4), newValue); // edge
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 1, 1, 5), newValue); // edge
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 1, 1, 4), value2); // general

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 1, 0, 5), 0); // whole row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 1, 0, 4), 0); // edge
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 1, 1, 5), 4); // edge
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 1, 1, 4), 1); // general

  // Initializing the matrix to 2s
  Matrix_fill(mat2, value2);
  // Fill Border 5x4 Matrix with newValue (negative)
  Matrix_fill_border(mat2, newValue2);

  // Third Row (Edge)
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 2, 0, 5), newValue2); // whole row
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 2, 0, 4), newValue2); // edge
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 2, 1, 5), newValue2); // edge
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 2, 1, 4), value2); // general

  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 2, 2, 3), value2); // one value

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 2, 0, 5), 0); // whole row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 2, 0, 4), 0); // edge
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 2, 1, 5), 4); // edge
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 2, 1, 4), 1); // general

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 2, 2, 3), 2); // one value

  // Last Row (Border)
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 3, 0, 5), newValue2); // whole row
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 3, 0, 4), newValue2); // edge
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 3, 1, 5), newValue2); // edge
  ASSERT_EQUAL(Matrix_min_value_in_row(mat2, 3, 1, 4), newValue2); // general
  
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 3, 0, 5), 0); // whole row
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 3, 0, 4), 0); // edge
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 3, 1, 5), 1); // edge
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat2, 3, 1, 4), 1); // general

  delete mat2; // delete the Matrix2
}

// Fill, fill border, and set element to different value 
// to check 6x3 Matrix print and compare with correct output
TEST(test_matrix_print) {

  Matrix* mat = new Matrix;

  const int width = 6;  
  const int height = 3;
  const int value = 1;
  const int newValue = 4;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);
  Matrix_fill_border(mat, 5);

  // Setting Edge values (First and Last)
  *Matrix_at(mat, 0, 0) = newValue;
  *Matrix_at(mat, 2, 5) = newValue;

  // Setting General value
  *Matrix_at(mat, 1, 2) = newValue;

  ostringstream correct;
  correct << "6 3\n"
          << "4 5 5 5 5 5 \n"
          << "5 1 4 1 1 5 \n"
          << "5 5 5 5 5 4 \n";

  ostringstream actual;
  Matrix_print(mat, actual);

  ASSERT_EQUAL(correct.str(), actual.str());

  delete mat;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
