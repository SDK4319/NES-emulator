#include "VScreen.h"

void VScreen::create(unsigned int width, unsigned int height, cv::Scalar color)
{
	cv::Mat temp(height, width, CV_8UC3);
	uchar* data = (uchar*)temp.data;
	for (int i = 0; i < width * height; i++) {
		data[i * 3 + 0] = color[0];
		data[i * 3 + 1] = color[1];
		data[i * 3 + 2] = color[2];
	}
	vscreen = temp.clone();
}

void VScreen::setPixel(unsigned int x, unsigned int y, cv::Scalar color)
{
	int height = vscreen.rows;
	int width = vscreen.cols;
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;
	auto& ref = vscreen.at<cv::Vec3b>(y, x);
	ref[0] = color[0];
	ref[1] = color[1];
	ref[2] = color[2];
}

cv::Mat VScreen::getFrame(unsigned int width, unsigned int height)
{
	cv::Mat dst;
	cv::resize(vscreen, dst, cv::Size(width, height),0, 0, cv::INTER_NEAREST);
	return dst.clone();
}

void VScreen::disp()
{
	cv::imshow("maine", vscreen);
}
