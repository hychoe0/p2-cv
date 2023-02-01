// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.

TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// Basic Test for initialization img and returning width and height
TEST(test_image_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const int width = 3;
  const int height = 3;

  Image_init(img, width, height);
  
  ASSERT_EQUAL(Image_width(img), width);
  ASSERT_EQUAL(Image_height(img), height);

  delete img; // delete the Image
}

// Test for reading PPM format and getting the pixel
TEST(test_image_ppm) {
  Image *img = new Image; // create an Image in dynamic memory

  string fileName = "crabster_70x35.correct.ppm";

  ifstream input(fileName);

  Image_init(img, input);
  
  ASSERT_EQUAL(Image_width(img), 70);
  ASSERT_EQUAL(Image_height(img), 35);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), {255, 255, 255}));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 22, 1), {181, 137, 143}));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 34, 69), {255, 255, 255}));

  delete img; // delete the Image
}

TEST(test_image_print) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  //const Pixel white = {255, 255, 255};

  const int width = 3;
  const int height = 4;
  Image_init(img, width, height);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 0, 2, blue);
  // Image_set_pixel(img, 0, 3, white);

  Image_print(img, cout);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 1), green));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 2), blue));
  // ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 3), white));

  delete img; // delete the Image
}

TEST(test_image_fill) {
  Image *img = new Image; // create an Image in dynamic memory

  Pixel red = {255, 0, 0};

  const int width = 3;
  const int height = 3;
  Image_init(img, 3, 3);

  Image_fill(img, red);

  Image_print(img, cout);
  
  // Checking every pixel in the Image
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, row, col), red));
    }
  }

  delete img; // delete the Image
}



// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
