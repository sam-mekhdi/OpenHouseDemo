class area {
public:
	double min, avg, max;
	area(double min1, double avg1, double max1) { min = min1, avg = avg1, max = max1; };
	bool isEqualTo(const object&);

};

class length {
public:
	double min, avg, max;
	length(double min1, double avg1, double max1) { min = min1, avg = avg1, max = max1; };
	bool isEqualTo(const object&);
};

class object : public area, public length {
public:

	void setName(string s) { name = s; };
	string getName() { return name; };

private:
	string name;


};


bool length::isEqualTo(const object& obj) {
	bool result = false;
	if (min == obj.length.min && avg == obj.length.avg && max == obj.length.max) {
		return true;
	}
}
bool area::isEqualTo(const object& obj) {
	bool result;
	if (min == obj.area.min && avg == obj.area.avg && max == obj.area.max) {
		return true;
	}
}

void readCamera(VideoCapture cameraStream, Mat image, int frameDelay) {
	cameraStream.read(image);
	cv::waitKey(frameDelay);
}

Mat preprocessImage(Mat image, Size blurSize, Mat image_temp, Mat converted_image) {
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


void main{
case 'b':
				std::cout << "--> Capturing Background" << endl;
				background = cv::Mat::zeros(image.size(), CV_64F);
				standardError = background.clone();
				count = 0;

				while (count < countFrames)
				{
					readCamera(cameraStream, image, frameDelay);
					converted_image = preprocessImage(image, blurSize, image_temp, converted_image);
					imshow("Display Window", image_temp);
					accumulate(converted_image, background);
					std::cout << "[Task 1/2] Captured Frame [" << count << "/" << countFrames << "]" << endl;
					count++;
				}

				imgDiv(background, countFrames);
				count = 0;
				diff = converted_image.clone();

				while (count < countFrames)
				{
					readCamera(cameraStream, image, frameDelay);
					converted_image = preprocessImage(image, blurSize, image_temp, converted_image);
					imshow("Display Window", image_temp);
					subtract(converted_image, background, diff);
					accumulateSquare(diff, standardError);
					std::cout << "[Task 2/2] Captured Standard Error Frame [" << count << "/" << countFrames << "]" << endl;
					count++;
				}

				imgDiv(standardError, countFrames);
				sqrt(standardError, standardError);
				standardError = standardError * errorMultiplier;
				backgroundCaptured = true;
				std::cout << "--  Capturing Background -- Done!" << endl;
				break; }