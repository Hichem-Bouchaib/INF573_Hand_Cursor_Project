#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include "MoveMouse.h"
#include "SkinColor.h"
#include "handContour.h"
#include "ColorDetection.h"


using namespace std;
using namespace cv;

void detectAndDisplay( Mat frame );
CascadeClassifier face_cascade;

// Values to detect the skin color
int L1x  = 0;
int L2x  = 48;
int L3x = 80;
int M1x = 20;
int M2x = 255;
int M3x = 244;

float center_x =0;
float center_y =0;

//String faceClassifierFileName = "/Users/Hichem/Desktop/haarcascade_frontalface_alt.xml";
//CascadeClassifier faceCascadeClassifier;
Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2(0,50);

int main()
{
    VideoCapture capture;
    //open capture object at location zero (default location for webcam)
    capture.open(0);
    //set height and width of capture frame
    capture.set(CAP_PROP_FRAME_WIDTH,640);
    capture.set(CAP_PROP_FRAME_HEIGHT,800);
    
    Mat cameraFeed;
    Mat skinMat, frame, fgMaskMOG2;
    if( !face_cascade.load( "haarcascade_frontalface_alt.xml" ) )
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };

    //start an infinite loop where webcam feed is copied to cameraFeed matrix
    //all of our operations will be performed within this loop
    vector<vector<Point>> contours;
     vector<Vec4i> hierarchy;
    Mat output;
    Mat mask1;
    Mat mask2;
    Mat maskfinal;
    Mat croped;
    Mat blueColor;
    
    while(1){
        capture.read(cameraFeed);
        flip(cameraFeed,cameraFeed,1);
        
        detectAndDisplay(cameraFeed); // remove the face
        GaussianBlur(cameraFeed, frame, Size(5,5), 0);
      

        pMOG2->apply(frame, fgMaskMOG2,0);
      //  imshow("fgMasj",fgMaskMOG2);
       // imshow("cameraFeed",cameraFeed);
        cv::Mat colorForeground = cv::Mat::zeros(cameraFeed.size(), cameraFeed.type());
        cameraFeed.copyTo(colorForeground,fgMaskMOG2);
        imshow("hand",colorForeground);
        
        skinMat= getSkin(colorForeground, L1x, L2x, L3x, M1x, M2x, M3x);
        
        
        Mat contourHand = handContour(skinMat, output, center_x, center_y);
        
        imshow("Image",colorForeground);
        //imshow("Image after",skinMat);
        imshow("contour ?",contourHand);
        imshow("Skin",skinMat);
        
        Mat color = cameraFeed;
        cvtColor(cameraFeed, color, COLOR_BGR2HSV);
        inRange(color, Scalar(110,50,50), Scalar(130,255,255), mask1);
        blueColor = colorDetection(mask1, center_x, center_y);
        imshow("Blue Color - Click",blueColor);
        int key = waitKey(1);
        if (key == 27) // esc

            break;

        }
    return 0;
}

//Detect the face, and put a black rectangle on it
void detectAndDisplay( Mat frame )

{
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //Detect the faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        rectangle(
            frame,
            Point(faces[i].x-100, faces[i].y-100),
            Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height+100),
            Scalar(0, 0, 0),
            -1
        );
    }
}


