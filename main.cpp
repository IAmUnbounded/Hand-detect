#include <QCoreApplication>
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
        VideoCapture cap("/home/sukhad/YDXJ0157.mp4");
         if(!cap.isOpened())  // check if we succeeded
         {
            cout<<"Video feed not available";
            cout<<"\nCheck for camera availability";
            int n;
            cin>>n;
            return(-1);}
        int border_value=0,iterations=2;
         int max_area=0;
         vector<Point>approx;
         vector<Point> hull;
         vector<Point> one;
         Mat kernel;
         kernel=Mat::ones(3,3,CV_8U);
         Mat edges;
        namedWindow("edges",1);
        namedWindow("second",1);
        for(;;)
        {
            vector<Point>Largest_contour;
            max_area=0;
            Mat frame1,frame2,grey,blur,dst,dilated;
            vector<vector<Point> > contours;
            vector<Vec4i> hierarchy;
            cap>>frame1;
            cvtColor(frame1, grey, CV_BGR2GRAY);
            GaussianBlur(grey,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            GaussianBlur(blur,blur,Size(5,5),1,1);
            threshold(blur, dst, 140, 255,THRESH_BINARY_INV+THRESH_OTSU);
            erode(dst, dst, kernel,Point(-1,-1),iterations);
            dilate(dst,dilated,kernel,Point(-1,-1),iterations);
            findContours(dilated,contours,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
            cout<<"\nContour elements no. ->"<<contours.size()<<endl;
            //DRAW ALL THE CONTOURS WHICH ARE PRESENT IN THE FRAME
            //drawContours(frame1,contours,-1,Scalar(255,255,255),2);
            for(unsigned int i=0; i < contours.size(); i++)
            {
                double area=contourArea(contours[i]);
                cout<<"\n"<<i+1<<" : "<<area;
                if(area>max_area)
                {
                    max_area=area;
                    Largest_contour=contours[i];
                }
            }
            vector<vector<Point> > tcontour;
            approxPolyDP(Largest_contour,approx,0.01*arcLength(Largest_contour,true),true);
            cout<<"\naprroximation done";
            convexHull(approx,hull);
            cout<<"\nHull done";
            tcontour.push_back(Largest_contour);
            drawContours(frame1,tcontour,-1,Scalar(255,0,0),2);
            int a=hull.size();
            a=a-2;
            //for(int i=0;i<hull.size();i++)
            //	cout<<endl<<hull[i].x<<":"<<hull[i].y<<"->"<<hull[i]<<endl;
            stringstream stream;
            string text;
            text = "Fingers: ";
            stream<<text<<a;
            text=stream.str();
            putText(frame1,text,Point(10,30),FONT_HERSHEY_COMPLEX_SMALL,1,Scalar(255,34,57));
            //PUTTING A-E AROUND FINGERS
            string point_number;
            //point_number="A";
            //for(int i=0;i<hull.size();i++)
            //{
            //	putText(frame1,point_number,Point(hull[i].x,hull[i].y),FONT_HERSHEY_COMPLEX,1,Scalar(255,255,255));
            //	point_number=point_number[0]+1;
            //}
            if(hull.size()>2)
            {
            for (int i=2;i<hull.size();i++)
            {
                int x=hull[i].x;
                int y=hull[i].y;
                circle(frame1,Point(x,y),5,Scalar(0,255,0),-1);
                circle(frame1,Point(x,y),8,Scalar(255,255,0),2);
                circle(frame1,Point(x,y),11,Scalar(255,0,0),2);
            }
            }
            vector <Point> point_array;
            point_array=hull;
            Point center = Point(0,0);
                for(int j=0;j<hull.size();j++)
                {
                    center.x=center.x + hull[j].x;
                    center.y=center.y + hull[j].y;

                }
                center.x=center.x/hull.size();
                center.y=center.y/hull.size();
                //PLOTTING THE CENTER POINT ON IMAGE
                circle(frame1,center,8,Scalar(255,0,0),2);
                point_number="Center";
                putText(frame1,point_number,center,FONT_HERSHEY_COMPLEX_SMALL,1,Scalar(245,123,67));
                //CALCULATING DISTANCE AND THEN DRAWING A CIRCLE FROM THE POINTS
                float max_x=0;
                if(hull.size()>2)
                {
                    for(int i=2;i<hull.size();i++)
                    {
                        float length;
                        length = sqrt(pow(hull[i].x-center.x,2)+pow(hull[i].y-center.y,2));
                        if(length>max_x)
                        {
                            max_x=length;
                        }
                    }
                }
                cout<<"\n::Radius of Circle:"<<(int)max_x;
                stringstream radius_circle_print;
                radius_circle_print<<"Radius Of Circle: "<<(int)max_x;

                putText(frame1,radius_circle_print.str(),Point(10,70),FONT_HERSHEY_COMPLEX_SMALL,1,Scalar(255,0,0));
                //DRAW CIRCLE AROUND THE HAND
                circle(frame1,center,(max_x-max_x/10),Scalar(167,240,45),4);
            cout<<"\nText done";
            imshow("edges", dilated);
            imshow("second",frame1);
            if(waitKey(30) >= 0) break;
        }
        // the camera will be deinitialized automatically in VideoCapture destructor
   return a.exec();
}
