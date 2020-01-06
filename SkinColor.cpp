
#include <iostream>
#include "SkinColor.h"

using namespace cv;
using namespace std;


// description on the .h file
Mat getSkin(Mat input, float L1x, float L2x, float L3x, float M1x, float M2x, float M3x){
   Mat hsvInput;
   Mat skinMask;
   cvtColor(input, hsvInput, COLOR_BGR2HSV);
    imshow("HSV", hsvInput);
   inRange(
       hsvInput,
       Scalar(L1x, L2x, L3x),
       Scalar(M1x, M2x, M3x),
       skinMask);

    Mat structuringElement = getStructuringElement(MORPH_ELLIPSE, { 3, 3 });
    morphologyEx(skinMask, skinMask, MORPH_ELLIPSE, structuringElement);
    dilate(skinMask, skinMask, Mat(), Point(-1, -1), 3);
    
   return skinMask;
}



