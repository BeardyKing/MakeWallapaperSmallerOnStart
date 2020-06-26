#include "ResizeWallpaper.h"


ResizeWallpaper::ResizeWallpaper()
{
	char* pValue;
	size_t len;
	errno_t err = _dupenv_s(&pValue, &len, "APPDATA");
	if (!err)
	{
		m_Path = pValue;
		m_Path += "/Microsoft/Windows/Themes/TranscodedWallpaper";

		if (GetWallpaper()) {
			if (ResizeImage()) {
				SetWallpaper();
				CallBackgroundChangeFlag();

				#if _DEBUG
				DisplayImage();
				#endif
			}
		}
	}
}

ResizeWallpaper::~ResizeWallpaper() {}

int ResizeWallpaper::GetWallpaper() {
	m_ImageIn = cv::imread(m_Path);
	if (m_ImageIn.empty()){
		std::cout << "Could not find desktop wallpaper" << std::endl;
		std::cin.get(); //wait for any key press
		return 0;
	}
	return 1;
}


int ResizeWallpaper::ResizeImage() {

	if (m_ImageIn.size[0] > 2){
		if (m_ImageIn.size[1] > 2) {
			cv::resize(m_ImageIn, m_ImageOut, cv::Size(), 0.5, 0.5);
			return 1;
		}
	}
	std::cout << "can not make image any smaller" << std::endl;
	std::cin.get();
	return 0;
}

void ResizeWallpaper::SetWallpaper() {
	std::string target_Path;
	target_Path = m_Path;
	target_Path += ".png";

	cv::imwrite(target_Path, m_ImageOut);
	
	remove(m_Path.c_str());
	rename(target_Path.c_str(), m_Path.c_str());
}

void ResizeWallpaper::CallBackgroundChangeFlag() {
	// can't find flags for x64 only win32 
	// can't find flags to change to tiled 
}

void ResizeWallpaper::DisplayImage() {
	std::string windowName = "Debug - Scaled Image";
	cv::namedWindow(windowName);
	cv::imshow(windowName, m_ImageOut);

	cv::waitKey(0); // Wait for keystroke in the window

	cv::destroyWindow(windowName);
}

