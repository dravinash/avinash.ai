// OpenCV Sample Application: facedetect.c

// Include header files
#include "cv.h"
#include "highgui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

// Create memory for calculations
static CvMemStorage* storage = 0;

// Create a new Haar classifier
static CvHaarClassifierCascade* cascade = 0;

// Function prototype for detecting and drawing an object from an image
void detect_and_draw( IplImage* image );

// Create a string that contains the cascade name
const char* cascade_name ="haarcascade_frontalface_alt_tree.xml";
/*    "haarcascade_profileface.xml";*/

// Main function, defines the entry point for the program.
int main( int argc, char** argv )
{
    IplImage* img;
    CvCapture* capture=cvCreateCameraCapture(0);
 
     cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
    
        
    // Allocate the memory storage
    storage = cvCreateMemStorage(0);
    
    // Create a new named window with title: result
    cvNamedWindow( "Face Detection Module", 1 );

        if( capture )
    {
        // Capture from the camera.
      while(1)
        {
            img=cvQueryFrame(capture);
            // Call the function to detect and draw the face
            detect_and_draw( img );
            // Wait for a while before proceeding to the next frame
            if( cvWaitKey( 10 ) >= 0 )
                break;
           
        }

        // Release the images, and capture memory
        cvReleaseImage( &img );
        cvReleaseCapture( &capture );
    
    }
    
    // Destroy the window previously created with filename: "result"
    cvDestroyWindow("Face Detection Module");

    // return 0 to indicate successfull execution of the program
    return 0;
}

// Function to detect and draw any faces that is present in an image
void detect_and_draw( IplImage* img )
{
    int scale = 1;

    // Create a new image based on the input image
    IplImage* temp = cvCreateImage( cvSize(img->width/scale,img->height/scale), 8, 3 );

    // Create two points to represent the face locations
    CvPoint pt1, pt2;
    int i;

    // Clear the memory storage which was used before
    cvClearMemStorage( storage );

    // Find whether the cascade is loaded, to find the faces. If yes, then:
    if( cascade )
    {

       CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(40, 40) );

        // Loop the number of faces found.
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
           // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;

            // Draw the rectangle in the input image
            cvRectangle( img, pt1, pt2, CV_RGB(0,255,0), 1, 8, 0 );
           
           
        }
    }

    // Show the image in the window named "result"
    cvShowImage( "Face Detection Module", img );
   

    // Release the temp image created.
    cvReleaseImage( &temp );
}
