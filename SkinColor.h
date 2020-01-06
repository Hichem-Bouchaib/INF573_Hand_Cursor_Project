#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;
/*
 This function is basic. It returns a mask of our skin color, allowing us to detect user's skin.
 It will help us to figure out our hand contours.
 
 @parameter : frame from the camera;
 @output : mask of our skin color
  
 */

Mat getSkin(Mat input, float L1x, float L2x, float L3x, float M1x, float M2x, float M3x);

