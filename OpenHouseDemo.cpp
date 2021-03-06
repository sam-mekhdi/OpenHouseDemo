/*
	Open House Demo 2018
	Based On: ELEC 474 - Lab 2
	Created By: Ian Maquignaz (with Lab 2 Solution from Avery Cole)

	Notes:
	- This code has many smells...
*/

// Standard C++ 
#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

// OpenCV Imports
#include <opencv2/core/core.hpp> // OpenCV Core Functionality
#include <opencv2/highgui/highgui.hpp> // High-Level Graphical User Interface 
#include <opencv2/imgproc.hpp> // Image Processing

// [Optional] Use OpenCV namespace
// NOTE! If note included, all OpenCV functions will need to be prepended with "cv::"
// EX: "Mat image;" -> "cv:Mat image;"
using namespace cv;

#define SAVE_MODE true
#define DISPLAY_WIDTH 1600
#define DISPLAY_HEIGHT 900


/*class object {
public:
	double area[3];
	double length[3];

	bool isEqualTo(const object&);
	string getName() { return name; };
	void setName(string s) { name = s; };

	void length_min(double n) { length[0] = n; };
	void length_avg(double n) { length[1] = n; };
	void length_max(double n) { length[2] = n; };

	double length_min() { return length[0]; };
	double length_avg() { return length[1]; };
	double length_max() { return length[2]; };

	void area_min(double n) { area[0] = n; };
	void area_avg(double n) { area[1] = n; };
	void area_max(double n) { area[2] = n; };

	double area_min() { return area[0]; };
	double area_avg() { return area[1]; };
	double area_max() { return area[2]; };


private:
	string name;
};*/

class object : public area{
public:
	//bool isEqualTo(const object&);
	//bool isEqualTo(const object&, string);
	void setName(string s) { name = s; };
	string getName() { return name; };
	friend class area;
private:
	string name;
	/*double length_min, length_avg, length_max;
	double area_min, area_avg, area_max;*/
};

class area : public object {
public:
	double min, avg, max;
	void area(double min, double avg, double max) { min = min, avg = avg, max = max; };

};

class length : public object {
public:
	double min, avg, max;
	
};
//bool object::isEqualTo(const object& obj) {
//	bool result = true;
//	int i, j = 0;
//	while (result && j < 3)
//	{
//		if (length[i] != obj.length[i])
//		{
//			result = false;
//		}
//		if (area[i] != obj.area[i])
//		{
//			result = false;
//		}
//		i++;
//		j++;
//
//	}
//	return result;
//}

//bool object::isEqualTo(const object& obj, string s) {
//	bool result = false;
//	if  (s.compare("length")) {
//		if (length_min == obj.length_min && length_avg == obj.length_avg && length_max == obj.length_max) {
//			result = true;
//		}
//	}
//	else if ((s.compare"area")) {
//		if (area_min == obj.area_min && area_avg == obj.area_avg && area_max == obj.area_max) {
//			result = true;
//		}
//	}
//	else result = false;
//	return result;
//}

void readCamera(VideoCapture cameraStream, Mat image, int frameDelay) {
	cameraStream.read(image);
	cv::waitKey(frameDelay);
}

Mat preprocessImage(Mat image, Size blurSize, Mat image_temp, Mat converted_image ) {
	blur(image, image, blurSize);
	resize(image.clone(), image_temp, Size(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2));
	cvtColor(image, converted_image, CV_BGR2GRAY);
	converted_image.convertTo(converted_image, CV_64F);
	return converted_image;
}

Mat imgDiv(Mat image, int frames) {
	image = image / frames;
	return image;
}


int main()
{
	object object1;
	object1.setName("object1");
	object1.area(2, 3, 4);
	cout << "object: " << object1.getName() << "/10" << endl;
//	// Create an image 
//	Mat image, image_temp, converted_image, processed_image, background, standardError, diff, errorThreshold, edges, contour, laplace, laplace_out;
//	Size blurSize = Size(5, 5);
//	int count = 0, countFrames = 100, countObjectSamples = 10, errorMultiplier = 20, thresh_area = 20, thresh_arc = 20, minMatchScore = 2, object_match = -1, object_area_match = -1, object_length_match = -1, max_contours = 7000;
//	int canny_min = 100, canny_max = 200, canny_kernel = 5;
//	bool SeekObject = false, backgroundCaptured = false;
//	double area_match, length_match, object_match_max = -1;
//
//#if SAVE_MODE
//	vector <Mat> imagesToSave;
//	VideoWriter outputVideo_raw, outputVideo_contour;
//	string videoName = "Captures\\ELEC_474_Lab_2_Videos_";
//	string pictureName = "Captures";
//	int videoCount = 0;
//#endif
//
//
//	// Contours
//	vector<Vec4i> hierarchy;
//	vector<vector<Point>> contourPoints;
//	vector<Point> largest_contour;
//
//	// Objects
//	object newObject;
//	vector<object> knownObjects;
//	vector<double> objectMatchScore;
//
//	// Start Camera
//	int frameDelay = 30;
//	int cameraSelection = 0;
//	VideoCapture cameraStream(cameraSelection);
//
//	if (!cameraStream.isOpened())
//	{
//		cameraStream.release();
//		std::cout << "Error! Camera Stream Not Opened..." << std::endl;
//		Sleep(10000);
//		exit(-1);
//	}
//
//	// Read first frame
//	cameraStream.read(image);
//	count = 0;
//	while (image.empty() && count < 10)
//	{
//		cout << "Failed to Capture Frame. Try " << count << "/10" << endl;
//		Sleep(100);
//		cameraStream.read(image);
//		count++;
//	}
//	if (image.empty())
//	{
//		std::cout << "Error! Could not capture image..." << std::endl;
//		Sleep(10000);
//		exit(-1);
//	}
//
//	// Create a display window
//	namedWindow("Display Window", CV_WINDOW_AUTOSIZE);
//	moveWindow("Display Window", 0, 0);
//	resizeWindow("Display Window", DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
//	resize(image.clone(), image_temp, Size(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2));
//	imshow("Display Window", image_temp);
//
//	// Start Operation
//	int key = ' ';
//	while (key != 'q')
//	{
//		// Check Keys
//		switch (key)
//		{
//			// Print Help
//		case 'h':
//			std::cout << "\n-- Printing Help -- \n" <<
//				" 1)  h - Prints Help \n" <<
//				" 2)  c - Capture New Object \n" <<
//				" 3)  d - Deletes All Objects \n" <<
//				" 4)  b - Captures Background \n" <<
//				" 5)  n - Blur Size ++ \n" <<
//				" 6)  m - Blur Size -- \n" <<
//				" 7)  i - Canny Kernel Size ++ \n" <<
//				" 8)  o - Canny Kernel Size -- \n" <<
//				" 9)  t - Error Multiplier ++ \n" <<
//				" 10) y - Error Multiplier -- \n" <<
//				" 11) p - Print Known Objects \n" <<
//				" 12) g - Toggle Searching For Objects On or Off \n" <<
//				" 13) q - End Program \n" <<
//				"-- End Help --\n" << endl;
//			break;
//		case 'c':
//			std::cout << "--> Capturing New Object" << endl;
//			namedWindow("Contour Window", CV_WINDOW_AUTOSIZE);
//			moveWindow("Contour Window", DISPLAY_WIDTH / 2, 0);
//			resizeWindow("Contour Window", DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
//
//			namedWindow("Selected Contour Window", CV_WINDOW_AUTOSIZE);
//			moveWindow("Selected Contour Window", 0, DISPLAY_HEIGHT / 2);
//			resizeWindow("Selected Contour Window", DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
//
//			newObject = object();
//		
//			newObject.area_min = DBL_MAX;
//			
//			newObject.length_min = DBL_MAX;
//			
//
//#if SAVE_MODE
//			imagesToSave.clear();
//#endif
//
//			count = 0;
//			std::cout << "Twenty images will be captures to sample object \nPress 'A' to Accept or 'D' to Destroy a sample image" << endl;
//			while (count < countObjectSamples)
//			{
//				// Accout for camera delay
//				cv::waitKey(1);
//
//				// Read and display image
//				cameraStream.read(image);
//				resize(image.clone(), image_temp, Size(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2));
//				imshow("Display Window", image_temp);
//
//				// Process Image
//				blur(image, image, blurSize);
//				cvtColor(image, converted_image, CV_BGR2GRAY);
//				converted_image.convertTo(converted_image, CV_64F);
//				absdiff(converted_image, background, diff);
//				subtract(diff, standardError, diff);
//				diff.convertTo(processed_image, CV_8UC1);
//				cv::threshold(processed_image, processed_image, 0, 255, THRESH_BINARY);
//
//				// Find Contour
//				contour = Mat::zeros(converted_image.size(), CV_8UC1);
//				cv::Canny(processed_image, edges, canny_min, canny_max, canny_kernel);//Thresh1, Thresh2, Aperture
//				cv::findContours(edges, contourPoints, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//				//findContours(edges, contourPoints, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//				if (contourPoints.size() >= 1 && contourPoints.size() < max_contours)
//				{
//					drawContours(contour, contourPoints, -1, Vec3d(255, 255, 255), CV_FILLED, 8);
//
//
//					resize(edges.clone(), image_temp, Size(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2));
//					imshow("Contour Window", image_temp);
//
//					double maxarea = 0, maxarclength = 0;
//					for (int j = 0; j < static_cast<int>(contourPoints.size()); j++)
//					{
//
//						double length = arcLength(contourPoints[j], 1);
//						double area = contourArea(contourPoints[j]);
//						if (area > maxarea)
//						{
//							maxarea = area;
//							maxarclength = length;
//							largest_contour = contourPoints[j];
//						}
//					}
//					if (maxarea > thresh_area && maxarclength > thresh_arc)
//					{
//						contourPoints.clear();
//						contourPoints.push_back(largest_contour);
//						contour = Mat::zeros(converted_image.size(), CV_8UC1);
//						drawContours(contour, contourPoints, -1, Vec3d(255, 0, 0), CV_FILLED, 16);
//						resize(contour.clone(), image_temp, Size(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2));
//						imshow("Selected Contour Window", image_temp);
//
//						newObject.area_avg += (double)maxarea;
//						newObject.length_avg += (double)maxarclength;
//						if (newObject.area_min > (double)maxarea)
//						{
//							newObject.area_min = (double)maxarea;
//						}
//						if (newObject.area_max < (double)maxarea)
//						{
//							newObject.area_max = (double)maxarea;
//						}
//						if (newObject.length_min > (double)maxarclength)
//						{
//							newObject.length_min = (double)maxarclength;
//						}
//						if (newObject.length_max < (double)maxarclength)
//						{
//							newObject.length_max = (double)maxarclength;
//						}
//						std::cout << "'A'ccept or 'D'estroy Sample?" << endl;
//						char key = cv::waitKey();
//						if (key == 'a') {
//							std::cout << "Captured Frame [" << count << " / " << countObjectSamples << "]" << endl;
//							count++;
//
//#if SAVE_MODE
//							imagesToSave.push_back(contour.clone());
//#endif
//						}
//					}
//					else {
//						std::cout << "[FAILED] Captured Frame was invalid [" << count << " / " << countFrames << "]" << endl;
//					}
//				}
//				else {
//					std::cout << "[FAILED] Contour Overload! Discarded Frame..." << contourPoints.size() << " [" << count << " / " << countFrames << "]" << endl;
//				}
//
//			}
//
//			cin.clear();
//			std::cout << "New Object Captured! \nPlease give this object a name (Enter 'd' to discard new object):" << endl;
//			cin >> newObject.name;
//
//			if (newObject.name != "d")
//			{
//				// Add Tolerance
//				newObject.area_min = newObject.area_min;
//				newObject.area_max = newObject.area_max;
//				newObject.length_min = newObject.length_min;
//				newObject.length_max = newObject.length_max;
//				newObject.length_avg = newObject.length_avg / (double)countObjectSamples;
//				newObject.area_avg = newObject.area_avg / (double)countObjectSamples;
//
//				// Print New Object
//				std::cout << "New Object Added!\n";
//				std::cout << "object Name = " << newObject.name << endl;
//				std::cout << "object Length Min = " << newObject.length_min << endl;
//				std::cout << "object Length Max = " << newObject.length_max << endl;
//				std::cout << "object Length Avg = " << newObject.length_avg << endl;
//				std::cout << "object Arc Min = " << newObject.area_min << endl;
//				std::cout << "object Arc Max = " << newObject.area_max << endl;
//				std::cout << "object Arc Avg = " << newObject.area_avg << endl;
//				knownObjects.push_back(newObject);
//
//				// Store New Object
//#if SAVE_MODE
//				for (int i = 0; i < imagesToSave.size(); i++)
//				{
//					imwrite(pictureName + "\\" + newObject.name + "\\" + newObject.name + "_" + to_string(i) + ".jpg", imagesToSave[i]);
//				}
//#endif
//			}
//			else
//			{
//				std::cout << "New Object Discarded..." << endl;
//			}
//
//			destroyWindow("Contour Window");
//			destroyWindow("Selected Contour Window");
//
//			std::cout << "--  Capturing New Object -- Done!" << endl;
//			break;
//		case 'd':
//			std::cout << "--> Deleting All Known Objects" << endl;
//			knownObjects.clear();
//			std::cout << "--  Deleting All Known Objects -- Done!" << endl;
//			break;
//		case 'b':
//			std::cout << "--> Capturing Background" << endl;
//			background = cv::Mat::zeros(image.size(), CV_64F);
//			standardError = background.clone();
//			count = 0;
//
//			while (count < countFrames)
//			{
//				readCamera(cameraStream, image, frameDelay);
//				converted_image = preprocessImage(image, blurSize, image_temp, converted_image);
//				imshow("Display Window", image_temp);
//				accumulate(converted_image, background);
//				std::cout << "[Task 1/2] Captured Frame [" << count << "/" << countFrames << "]" << endl;
//				count++;
//			}
//
//			imgDiv(background, countFrames);
//			count = 0;
//			diff = converted_image.clone();
//
//			while (count < countFrames)
//			{
//				readCamera(cameraStream, image, frameDelay);
//				converted_image = preprocessImage(image, blurSize, image_temp, converted_image);
//				imshow("Display Window", image_temp);
//				subtract(converted_image, background, diff);
//				accumulateSquare(diff, standardError);
//				std::cout << "[Task 2/2] Captured Standard Error Frame [" << count << "/" << countFrames << "]" << endl;
//				count++;
//			}
//
//			imgDiv(standardError, countFrames);
//			sqrt(standardError, standardError);
//			standardError = standardError * errorMultiplier;
//			backgroundCaptured = true;
//			std::cout << "--  Capturing Background -- Done!" << endl;
//			break;
//		case 'n':
//			std::cout << "--> Increasing Blur Size" << endl;
//			std::cout << "\t Blur Size " << blurSize;
//			blurSize.height++;
//			blurSize.width++;
//			std::cout << " --> " << blurSize << endl;
//			std::cout << "--  Increasing Blur Size -- Done!" << endl;
//			break;
//		case 'm':
//			std::cout << "--> Decreasing Blur Size" << endl;
//
//			if (blurSize.height > 1)
//			{
//				std::cout << "\t Blur Size " << blurSize;
//				blurSize.height--;
//				blurSize.width--;
//				std::cout << " --> " << blurSize << endl;
//			}
//			else
//			{
//				std::cout << "Error! Blur Size cannot be less than [1,1]! BlurSize=" << blurSize << endl;
//			}
//
//			std::cout << "--  Decreasing Blur Size -- Done!" << endl;
//			break;
//		case 'i':
//			std::cout << "--> Increasing Canny Kernel Size" << endl;
//			if (canny_kernel < 7)
//			{
//				std::cout << "\t Canny Kernel Size " << canny_kernel;
//				canny_kernel = canny_kernel + 2;
//				std::cout << " --> " << canny_kernel << endl;
//			}
//			else
//			{
//				std::cout << "Error! Canny Kernel Size cannot be more than 7! Canny Kernel Size =" << canny_kernel << endl;
//			}
//			std::cout << "--  Increasing Canny Kernel Size -- Done!" << endl;
//			break;
//		case 'o':
//			std::cout << "--> Decreasing Canny Kernel Size" << endl;
//
//			if (canny_kernel > 3)
//			{
//				std::cout << "\t Canny Kernel Size " << canny_kernel;
//				canny_kernel = canny_kernel - 2;
//				std::cout << " --> " << canny_kernel << endl;
//			}
//			else
//			{
//				std::cout << "Error! Canny Kernel Size cannot be less than 3! Canny Kernel Size =" << canny_kernel << endl;
//			}
//
//			std::cout << "--  Decreasing Canny Kernel Size -- Done!" << endl;
//			break;
//		case 't':
//			std::cout << "--> Increasing Error Multiplier" << endl;
//
//			std::cout << "\t Error Multiplier " << errorMultiplier;
//			errorMultiplier++;
//			std::cout << " --> " << errorMultiplier << endl;
//
//			std::cout << "--  Increasing Error Multiplier -- Done!" << endl;
//			break;
//		case 'y':
//			std::cout << "--> Decreasing Error Multiplier" << endl;
//
//			std::cout << "\t Error Multiplier " << errorMultiplier;
//			errorMultiplier--;
//			std::cout << " --> " << errorMultiplier << endl;
//
//			std::cout << "--  Decreasing Error Multiplier -- Done!" << endl;
//			break;
//		case 'g':
//			std::cout << "--> Toggling Object Search [" << SeekObject << "] --> [" << !SeekObject << "]" << endl;
//			if (backgroundCaptured)
//			{
//				SeekObject = !SeekObject;
//			}
//			else
//			{
//				std::cout << "Please capture background first..." << endl;
//			}
//
//			if (SeekObject)
//			{
//				// Clear History
//				objectMatchScore = vector<double>(knownObjects.size(), 0);
//
//				namedWindow("Display Window", WINDOW_NORMAL);
//				moveWindow("Display Window", 0, 0);
//				resizeWindow("Display Window", DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
//
//				namedWindow("Contour Window", WINDOW_NORMAL);
//				moveWindow("Contour Window", 0, DISPLAY_HEIGHT / 2);
//				resizeWindow("Contour Window", DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
//
//				namedWindow("Object Window", WINDOW_NORMAL);
//				moveWindow("Object Window", DISPLAY_WIDTH / 2, 0);
//				resizeWindow("Object Window", DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
//
//				//namedWindow("laplace", WINDOW_NORMAL);
//				//moveWindow("laplace", DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
//				//resizeWindow("laplace", DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
//#if SAVE_MODE
//				outputVideo_raw.open(videoName + "CameraCapture_" + to_string(videoCount) + ".avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, background.size(), true);
//				outputVideo_contour.open(videoName + "Processed_" + to_string(videoCount) + ".avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, background.size(), true);
//
//				if (!outputVideo_raw.isOpened())
//				{
//					cout << "Could not open the output video for write: " << videoName + "CameraCapture_" + to_string(videoCount) + ".avi" << endl;
//					Sleep(10000);
//					return -1;
//				}
//				if (!outputVideo_contour.isOpened())
//				{
//					cout << "Could not open the output video for write: " << videoName + "Processed_" + to_string(videoCount) + ".avi" << endl;
//					Sleep(10000);
//					return -1;
//				}
//
//				videoCount++;
//#endif
//			}
//			else
//			{
//				// Clear History
//				objectMatchScore.clear();
//				destroyWindow("Display Window");
//				namedWindow("Display Window", CV_WINDOW_AUTOSIZE);
//				destroyWindow("Contour Window");
//				destroyWindow("Object Window");
//				//destroyWindow("laplace");
//
//#if SAVE_MODE
//				outputVideo_raw.release();
//				outputVideo_contour.release();
//#endif
//
//			}
//			cout << "--  Toggling Object Search -- Done!" << endl;
//			break;
//		case 'p':
//			cout << "--> Printing Known Objects" << endl;
//			for (int i = 0; i < knownObjects.size(); i++)
//			{
//				cout << knownObjects[i].name << endl;
//			}
//			cout << "--  Printing Known Objects -- Done!" << endl;
//			break;
//		}
//
//		// Read an image
//		cameraStream.read(image);
//
//
//		// Seek Object
//		if (SeekObject)
//		{
//#if SAVE_MODE
//			outputVideo_raw.write(image);
//#endif
//
//			// Process Image
//			blur(image, image, blurSize);
//
//			// Display the image
//			image_temp = image.clone();
//			resize(image_temp, image_temp, Size(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2));
//			imshow("Display Window", image_temp);
//
//			cvtColor(image, converted_image, CV_BGR2GRAY);
//
//			/*
//			Laplacian(converted_image,laplace, CV_16S, 3, 1, 0, BORDER_DEFAULT);
//			convertScaleAbs(laplace, laplace);
//			laplace.convertTo(laplace, CV_64F);
//			log(laplace, laplace);
//			normalize(laplace, laplace, FLT_MIN, FLT_MAX, NORM_MINMAX);
//			imshow("laplace", laplace);
//			*/
//
//			converted_image.convertTo(converted_image, CV_64F);
//			absdiff(converted_image, background, diff);
//			subtract(diff, standardError, diff);
//			diff.convertTo(processed_image, CV_8UC1);
//			threshold(processed_image, processed_image, 0, 255, THRESH_BINARY);
//
//			// Find Contour
//			Canny(processed_image, edges, canny_min, canny_max, canny_kernel);//Thresh1, Thresh2, Aperture
//			findContours(edges, contourPoints, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//			//int idx = 0;
//			//for (; idx >= 0; idx = hierarchy[idx][0])
//			//{
//			//	Scalar color(rand() & 255, rand() & 255, rand() & 255);
//			//	drawContours(contour, contourPoints, idx, color, CV_FILLED, 8, hierarchy);
//			//}
//
//			if (contourPoints.size() >= 1 && contourPoints.size() < max_contours)
//			{
//				contour = Mat::zeros(image.size(), CV_8UC1);
//				drawContours(contour, contourPoints, -1, Vec3d(255, 0, 0), CV_FILLED, 16);
//
//				resize(contour.clone(), image_temp, Size(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2));
//				imshow("Contour Window", image_temp);
//
//				double maxarea = 0, maxarclength = 0;
//				for (int j = 0; j < static_cast<int>(contourPoints.size()); j++)
//				{
//
//					double length = arcLength(contourPoints[j], 1);
//					double area = contourArea(contourPoints[j]);
//					if (area > maxarea)
//					{
//						maxarea = area;
//						maxarclength = length;
//						largest_contour = contourPoints[j];
//					}
//				}
//				area_match = DBL_MAX;
//				length_match = DBL_MAX;
//				object_match = -1;
//				object_match_max = -1;
//				object_area_match = -1;
//				object_length_match = -1;
//				if (maxarea > thresh_area && maxarclength > thresh_arc)
//				{
//					for (int i = 0; i < static_cast<int>(knownObjects.size()); i++)
//					{
//						objectMatchScore[i] = objectMatchScore[i] * 0.95;
//						if (abs(1 - (maxarea / knownObjects[i].area_avg)) < abs(1 - area_match))
//						{
//							area_match = (double)maxarea / knownObjects[i].area_avg;
//							object_area_match = i;
//						}
//						if (abs(1 - (maxarclength / knownObjects[i].length_avg)) < abs(1 - length_match))
//						{
//							length_match = (double)maxarclength / knownObjects[i].length_avg;
//							object_length_match = i;
//						}
//						/*
//						else
//						{
//							cout << knownObjects[i].name <<"- Match Stats :: O =" << knownObjects[object_match].name << " A=" << abs(1 - area_match) << " :: L=" << abs(1 - length_match);
//							cout << " -> Measured Stats :: A= " << abs(1 - (maxarea / knownObjects[i].area_avg)) << ":: L=" << abs(1 - (maxarclength / knownObjects[i].length_avg)) <<  endl;
//						}*/
//					}
//				}
//				/*else
//				{
//					cout << "Failed thresh test" << endl;
//				}*/
//
//				// Draw best Contour
//				contourPoints.clear();
//				contourPoints.push_back(largest_contour);
//				contour = Mat::zeros(converted_image.size(), CV_8UC1);
//				drawContours(contour, contourPoints, -1, Vec3d(255, 0, 0), CV_FILLED, 16);
//
//				// Clasify
//
//				if (abs(1 - length_match) < 0.50 && abs(1 - area_match) < 0.50)
//				{
//					objectMatchScore[object_area_match]++;
//					objectMatchScore[object_length_match]++;
//					for (int i = 0; i < static_cast<int>(objectMatchScore.size()); i++)
//					{
//						// Recall
//						//objectMatchScore[i] = objectMatchScore[i]*0.60;
//						cout << i << " -> " << objectMatchScore[i] << endl;
//						// Selection
//						if (objectMatchScore[i] > minMatchScore && object_match_max < objectMatchScore[i])
//						{
//							object_match_max = objectMatchScore[i];
//							object_match = i;
//						}
//					}
//
//					if (object_match != -1)
//					{
//						cout << "Object Identified! Object[" << object_match << "]=" << knownObjects[object_match].name << " :: ArcLength Score = " << length_match << ", Area Score = " << area_match << endl;
//						cout << "\t--> (AREA)" << knownObjects[object_match].area_min << " < " << maxarea << " < " << knownObjects[object_match].area_max << "\t&&\t (Length)" << knownObjects[object_match].length_min << " < " << maxarclength << " < " << knownObjects[object_match].length_max << endl;
//
//#if !SAVE_MODE
//						putText(contour, "PREDICTION = " + knownObjects[object_match].name, Point(120, 100), cv::FONT_HERSHEY_PLAIN, 7, Scalar(255, 0, 0), 4);
//#endif					
//					}
//
//				}
//				else
//				{
//					cout << "-" << endl;
//				}
//
//#if SAVE_MODE
//
//				image_temp = contour.clone();
//				image_temp.convertTo(image_temp, CV_8UC3);
//				cv::cvtColor(image_temp, image_temp, cv::COLOR_GRAY2BGR);
//				outputVideo_contour.write(image_temp);
//#endif
//
//				resize(contour.clone(), contour, Size(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2));
//				imshow("Object Window", contour);
//			}
//			else
//			{
//				std::cout << "Contour Overload! Discarded Frame..." << contourPoints.size() << endl;
//			}
//			key = ' ';
//			key = cv::waitKey(1);
//		}
//		else
//		{
//			// Display the image
//			resize(image.clone(), image_temp, Size(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2));
//			putText(image_temp, "Live Capture", Point(100, 100), cv::FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 0));
//			imshow("Display Window", image_temp);
//
//			key = ' ';
//			key = waitKey(frameDelay);
//
//		}
//	}
//
//	// Wait for a keystroke in the window
//	// NOTE! If you don't add this the window will close immediately!
//	std::cout << "Press Any Key To End Program" << endl;
//	cv::waitKey(frameDelay);
//
//	// Terminate the program
//	std::cout << "END PROGRAM" << endl;
//	return 0;
}

