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

TEST(test_matrix_row_and_col) {
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 5;

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

TEST(test_matrix_at) {
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 5;
  int row = 2;
  int column = 1;
  int* ptr = &mat->data[7];

  Matrix_init(mat, width, height);

  // Printing pointers
  cout << Matrix_at(mat, row, column) << endl;
  cout << ptr << endl;

  assert(Matrix_at(mat, row, column) == ptr);

  delete mat; // delete the Matrix
}

TEST(test_matrix_fill) {
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 5;
  int value = 37;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  // Printing each elements
  Matrix_print(mat, cout);

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

  Matrix_print(mat, cout);

  delete mat; // delete the Matrix
}

TEST(test_matrix_coluimn_of_min_value_in_row) {
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
  mat->data[6] = -1;
  mat->data[7] = 1;
  mat->data[8] = -1;
  mat->data[9] = 1;
  mat->data[10] = -1;

  Matrix_print(mat, cout);
  
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, row2, col_start2, col_end2), 0);

  cout << Matrix_column_of_min_value_in_row(mat, row2, col_start2, col_end2) << endl;

  delete mat; // delete the Matrix
}

TEST(test_matrix_min_value_in_row) {
  Matrix *mat = new Matrix;

  const int width = 6;
  const int height = 5;
  const int value = 0;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  mat->data[6] = -1;
  mat->data[7] = 1;
  mat->data[8] = -1;
  mat->data[9] = 1;
  mat->data[10] = -1;

  Matrix_print(mat, cout);
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
