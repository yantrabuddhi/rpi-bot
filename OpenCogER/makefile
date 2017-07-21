all:
		g++ -I./include -std=c++11  src/main.cpp src/DetectionTrackerBase.cpp src/color2gray.cpp src/faceDetect.cpp src/smileDetect.cpp src/filterBase.cpp src/histEqualize.cpp src/leftEyeDetect.cpp src/rightEyeDetect.cpp src/CamCapture.cpp -o DBT `pkg-config --cflags --libs opencv` -lpthread
