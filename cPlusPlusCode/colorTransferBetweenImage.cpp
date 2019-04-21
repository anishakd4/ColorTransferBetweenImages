#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(){

    //Read the source and destination images
    Mat source = imread("../assets/src.jpeg");
    Mat destination = imread("../assets/dest.jpeg");

    //Result Mat instialized
    Mat result = destination.clone();

    //declare Mat variables to store images in LAB color space
    Mat sourceLab, destinationLab, resultLab;

    //Converting to LAB color space
    cvtColor(source, sourceLab, COLOR_BGR2Lab);
    cvtColor(destination, destinationLab, COLOR_BGR2Lab);
    cvtColor(result, resultLab, COLOR_BGR2Lab);

    //Convert to float32
    sourceLab.convertTo(sourceLab, CV_32F);
    destinationLab.convertTo(destinationLab, CV_32F);
    resultLab.convertTo(resultLab, CV_32F);

    //Declare vectors to store splitted channels
    vector<Mat> sourceChannels;
    vector<Mat> destinationChannels;
    vector<Mat> resultChannels;

    //spliting channels
    split(sourceLab, sourceChannels);
    split(destinationLab, destinationChannels);
    split(resultLab, resultChannels);

    //Declare variables to store means and standard deviations
    float mean1, mean2, mean3, mean4,mean5, mean6;
    float stdDev1, stdDev2, stdDev3, stdDev4, stdDev5, stdDev6;
    Scalar meanSource, meanDestination, stdDevSource, stdDevDestination;

    //Finding means and standard deviations for different channels for source image
    meanStdDev(sourceLab, meanSource, stdDevSource, Mat());
    mean1 = meanSource.val[0];
    mean2 = meanSource.val[1];
    mean3 = meanSource.val[2];
    stdDev1 = stdDevSource.val[0];
    stdDev2 = stdDevSource.val[1];
    stdDev3 = stdDevSource.val[2];

    //Finding means and standard deviations for different channels for destination image
    meanStdDev(destinationLab, meanDestination, stdDevDestination, Mat());
    mean4 = meanDestination.val[0];
    mean5 = meanDestination.val[1];
    mean6 = meanDestination.val[2];
    stdDev4 = stdDevDestination.val[0];
    stdDev5 = stdDevDestination.val[1];
    stdDev6 = stdDevDestination.val[2];

    //subtract the mean of destination image. This in a way removes the base color of the destination image.
    resultChannels[0] = destinationChannels[0] - mean4;
    resultChannels[1] = destinationChannels[1] - mean5;
    resultChannels[2] = destinationChannels[2] - mean6;

    //scale the standard deviation of the destination image
    resultChannels[0] = resultChannels[0] * (stdDev1/ stdDev4);
    resultChannels[1] = resultChannels[1] * (stdDev2/ stdDev5);
    resultChannels[2] = resultChannels[2] * (stdDev3/ stdDev6);

    //add the mean of source image to get the color
    resultChannels[0] = resultChannels[0] + mean1;
    resultChannels[1] = resultChannels[1] + mean2;
    resultChannels[2] = resultChannels[2] + mean3;

    //merge the channels
    merge(resultChannels, resultLab);

    //convert back from float32
    resultLab.convertTo(resultLab, CV_8UC3);

    //convert the image back BGR Color space
    cvtColor(resultLab, result, COLOR_Lab2BGR);

    //Create windows to display images
    namedWindow("source", WINDOW_NORMAL);
    namedWindow("destination", WINDOW_NORMAL);
    namedWindow("result", WINDOW_NORMAL);

    //display images
    imshow("source", source);
    imshow("destination", destination);
    imshow("result", result);

    //press esc to exit the program
    waitKey(0);

    //close all the opened windows
    destroyAllWindows();

    return 0;
}