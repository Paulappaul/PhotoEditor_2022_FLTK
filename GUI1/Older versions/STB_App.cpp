#include "MasterimageHeader.h"

int main(int argc, char** argv){
    Image test("test3.jpg");

    test.grayscale_avg();
    //test.colorMask(.8, .2, .2); floats
    test.write("gray.jpg");
  
    return 0;
}