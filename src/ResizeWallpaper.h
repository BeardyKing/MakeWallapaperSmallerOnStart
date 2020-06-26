#pragma once
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

class ResizeWallpaper {
public :
	ResizeWallpaper();
	~ResizeWallpaper();
private:
	int  GetWallpaper();
	int  ResizeImage();
	void SetWallpaper();
	void CallBackgroundChangeFlag();
	void DisplayImage();
private:

	std::string m_Path;
	cv::Mat m_ImageIn, m_ImageOut;
};
