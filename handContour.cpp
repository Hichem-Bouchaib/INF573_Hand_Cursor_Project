#include "handContour.h"
#include "MoveMouse.h"

using namespace cv;
using namespace std;

// described in the .h
Mat handContour(Mat input_image, Mat frame, float center_x, float center_y){
    Mat contours_image = Mat::zeros(input_image.size(), CV_8UC3);

    // check if the input image is not mpety
    if (input_image.empty())
        return contours_image;

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    // find all the contours of the frame
    findContours(input_image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    // check if we have at least one frame
    if (contours.size() <= 0)
        return contours_image;

    // now it is time to find the biggest area
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
        return contours_image;
    
    

    vector<Point> hull_points;
    // draw the convex hull of the biggest area only
    convexHull(Mat(contours[biggest_contour_index]), hull_points, true);

    // we bound the convex hull
    Rect bounding_rectangle = boundingRect(Mat(hull_points));

    // determine the center of the rectangle = approximately the center of our hand
    Point center_bounding_rect(
        (bounding_rectangle.tl().x + bounding_rectangle.br().x) / 2,
        (bounding_rectangle.tl().y + bounding_rectangle.br().y) / 2
    );
    
    
    // we draw the contour, the hull and the point
    drawContours(contours_image, contours, biggest_contour_index, Scalar(0, 255, 0), 2, 8, hierarchy);
    rectangle(contours_image, bounding_rectangle.tl(), bounding_rectangle.br(), Scalar(0, 0, 255), 2, 8, 0);
    circle(contours_image, center_bounding_rect, 5, Scalar(0, 0, 255), 2, 8);
    
    //Process to store the center as coordinates to be accepted by putText
    string x = to_string(center_bounding_rect.x);
    string y = to_string(center_bounding_rect.y);
    String delimiter=";";
    string coordinates = x+delimiter+y;
    
    // update the global variables for center pos
    center_x = center_bounding_rect.x;
    center_y = center_bounding_rect.y;
    
    //write on the frame
    putText(contours_image, coordinates, center_bounding_rect, FONT_HERSHEY_PLAIN, 3, Scalar(255, 255, 255));
    
    //update the position of the mouse
    moveMouse(center_bounding_rect.x, center_bounding_rect.y);
     return contours_image;
    
}


