#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <stdio.h>
#include <stdio.h>

using namespace cv;
using namespace std;

/*
 
 @input : input frame, outputframe, and coordinates of the hand's center
 @output : frame with contours and convexhull drawn
 
 */
Mat handContour(Mat input_image, Mat frame, float center_x, float center_y);


