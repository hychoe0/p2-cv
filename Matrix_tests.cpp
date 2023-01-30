// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.

// TEST(test_fill_basic) {
//   Matrix *mat = new Matrix; // create a Matrix in dynamic memory

//   const int width = 3;
//   const int height = 5;
//   const int value = 42;
//   Matrix_init(mat, 3, 5);
//   Matrix_fill(mat, value);

//   for(int r = 0; r < height; ++r){
//     for(int c = 0; c < width; ++c){
//       ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
//     }
//   }

//   delete mat; // delete the Matrix
// }

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.

TEST(test_matrix_row_and_col) {
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 5;
  const int* ptr = &mat->data[7];

  Matrix_init(mat, width, height);

  assert(Matrix_row(mat, ptr) == 2);
  assert(Matrix_column(mat, ptr) == 1);

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

// TEST(test_matrix_fill) {
//   Matrix *mat = new Matrix;

//   const int width = 3;
//   const int height = 5;
//   int value = 37;

//   Matrix_init(mat, width, height);
//   Matrix_fill(mat, value);

//   // // Printing each elements
//   // for (int i = 0; i < mat->height * mat->width; ++i) {
//   //   cout << i << ": " << mat->data[i] << endl;  
//   // }

//   delete mat; // delete the Matrix
// }

TEST(test_matrix_fill_border) {
  Matrix *mat = new Matrix;

  const int width = 5;
  const int height = 5;
  int value = 37;

  Matrix_init(mat, width, height);
  Matrix_fill_border(mat, value);

  // Printing each elements
  for (int i = 0; i < mat->height * mat->width; ++i) {
    cout << i << ": " << mat->data[i] << endl;  
  }

  delete mat; // delete the Matrix
}




// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
