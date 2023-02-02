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

  //Initializing elements to 0s
  Matrix_fill(mat1, 30);

  // Test Case #2-1 (General 5 x 4)
  *Matrix_at(mat1, 3, 2) = 31;
  ASSERT_EQUAL(Matrix_max(mat1), 31);

  //Initializing elements to 0s
  Matrix_fill(mat1, 30);

  // Test Case #2-2 (First Edge 5 x 4)
  *Matrix_at(mat1, 0, 0) = 31;
  ASSERT_EQUAL(Matrix_max(mat1), 31);

  //Initializing elements to 0s
  Matrix_fill(mat1, 30);

  // Test Case #2-2 (Last Edge 5 x 4)
  *Matrix_at(mat1, 3, 4) = 31;
  ASSERT_EQUAL(Matrix_max(mat1), 31);

  //Initializing elements to 0s
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



// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
