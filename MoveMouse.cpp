#include "MoveMouse.h"
#import "CoreGraphics/CoreGraphics.h"

// described in the .h
void moveMouse(float x, float y){
    CGDisplayMoveCursorToPoint (kCGDirectMainDisplay, CGPointMake(x, y));
}

// described in the .h
void clickMouse(float x, float y){
    CGEventRef click1_down = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, CGPointMake(x,y), kCGMouseButtonLeft);
    CGEventRef click1_up = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, CGPointMake(x,y), kCGMouseButtonLeft);
    CGEventPost(kCGHIDEventTap, click1_down);
    CGEventPost(kCGHIDEventTap, click1_up);
}

