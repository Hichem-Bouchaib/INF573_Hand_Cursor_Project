#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/*
 @input : input_frame, center of the hand
 @output : frame with blue as white pixels, other in black (threshold)
 
 */

Mat colorDetection(Mat input_image, float center_x, float center_y);


