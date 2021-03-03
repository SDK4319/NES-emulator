#pragma once
#include<opencv2/opencv.hpp>

class VScreen
{
public:
	void create(unsigned int width, unsigned int height, cv::Scalar color);
	void setPixel(unsigned int x, unsigned int y, cv::Scalar color);
	cv::Mat getFrame(unsigned int width, unsigned int height);
	void disp();
private:
	cv::Mat vscreen;
	cv::Mat mainFrame;
};

