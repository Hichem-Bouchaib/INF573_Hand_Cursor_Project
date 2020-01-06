#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include "ColorDetection.h"
#include "MoveMouse.h"

using namespace std;
using namespace cv;

Mat colorDetection(Mat input_image, float center_x, float center_y){
   // Mat contours_image = Mat::zeros(input_image.size(), CV_8UC3);
    imshow("input", input_image);
    // check if the source image is good
    if (input_image.empty())
        return input_image;

    // we work only on the 1 channel result, since this function is called inside a loop we are not sure that this is always the case
    if (input_image.channels() != 1)
        return input_image;

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(input_image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    // we need at least one contour to work
    if (contours.size() <= 0)
        return input_image;

    // find the biggest contour (let's suppose it's our hand)
    int biggest_contour_index = -1;
    double biggest_area = 0.0;

    for (int i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i], false);
        if (area > biggest_area) {
            biggest_area = area;
            biggest_contour_index = i;
        }
    }

    if (biggest_contour_index < 0)
        return input_image;
    
    // we draw what found on the returned image
     drawContours(input_image, contours, biggest_contour_index, Scalar(0, 255, 0), 2, 8, hierarchy);
    
    cout<<countNonZero(input_image)<<endl;
    if (countNonZero(input_image)>800){
        clickMouse(center_x, center_y);
        putText(input_image, "clicked", Point(20,20), FONT_HERSHEY_PLAIN, 3, Scalar(255, 255, 255));
        cout<<"Click detected"<<endl;
    }
    
     return input_image;
    
}

