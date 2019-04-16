/**
* Copyright (c) 2011 Aldebaran Robotics. All Rights Reserved
* \file sayhelloworld.cpp
* \brief Make NAO say a short phrase.
*
* A simple example showing how to make NAO say a short phrase using the
* specialized proxy ALTextToSpeechProxy.
*/

#include "build-naotoolchain/sayhelloworld.h"
#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/alvideodeviceproxy.h>
#include <alvision/alvisiondefinitions.h>
#include <alproxies/almotionproxy.h>

extern "C" {
	std::string ip = "192.168.100.6";
	std::string subscriberID = "subscriberID";

	// Proxy to ALVideoDevice
	AL::ALVideoDeviceProxy* cameraProxy;

	__declspec(dllexport) void NaoGoToPosture(std::string posture) {
		try
		{
			AL::ALRobotPostureProxy postureProxy(ip,9559); 
			postureProxy.goToPosture(posture,1.0);
		}
		catch (const AL::ALError& e)
		{
			std::cerr << "Caught exception: " << e.what() << std::endl;
			exit(1);
		}
	}

	__declspec(dllexport) const char* GetIPAddress() {
		return ip.c_str();
	}

	__declspec(dllexport) void SetIPAddress(const char* ipAddress) {
		ip = ipAddress;
	}

	__declspec(dllexport) void NaoSit() {
		NaoGoToPosture("Sit");
	}

	__declspec(dllexport) void NaoStand() {
		NaoGoToPosture("Stand");
	}

	__declspec(dllexport) void NaoLieDown() {
		NaoGoToPosture("LyingBack");
	}

	__declspec(dllexport) void NaoWalkTo(float x, float y, float theta) {
		
		  AL::ALMotionProxy motion(ip,9559);
		  AL::ALRobotPostureProxy robotPosture(ip,9559);

		  robotPosture.goToPosture("StandInit", 0.5f);

		  motion.moveTo(x, y, theta);
		  // Will block until walk Task is finished
	}
	
	__declspec(dllexport) void NaoWave() {
		//TODO
	}

	__declspec(dllexport) void NaoSpeak(const char* phraseToSay) {
		try
		{
			/** Create an ALTextToSpeechProxy so that we can call the say method
			* Arguments for the constructor are:
			*  - IP of the robot
			*  - port on which NAOqi is listening. Default is 9559
			*/
			AL::ALTextToSpeechProxy tts(ip , 9559);
			tts.say(phraseToSay);
		}
		catch (const AL::ALError& e)
		{
			std::cerr << "Caught exception: " << e.what() << std::endl;
			exit(1);
		}
	}

	__declspec(dllexport) void SubscribeVideo() {

		// Proxy to ALVideoDevice.
		cameraProxy = new AL::ALVideoDeviceProxy(ip);
		// Subscribe a Vision Module to ALVideoDevice, starting the
		// frame grabber if it was not started before.
		int fps = 5;
		int cameraID = 0;
		// The subscriberID can be altered if other instances are already running
		subscriberID = cameraProxy->subscribeCamera(subscriberID, cameraID, AL::kQQVGA, AL::kBGRColorSpace, fps);
	}

	__declspec(dllexport) int GetImageData(unsigned char* *data, int* size, int* width, int* height) {
		// Retrieve the current image.
		AL::ALValue results;
		std::cout << "Retrieving Image" << std::endl;

		results = cameraProxy->getImageRemote(subscriberID);

		const unsigned char* imageData =  static_cast<const unsigned char*>(results[6].GetBinary());

		unsigned char* p = new unsigned char[results[6].getSize()];
		std::memcpy(p, imageData, results[6].getSize());

		*data = p;
		
		std::cout << "Image Data size: " << results[6].getSize() << std::endl;
		std::cout << "Image Data width: " << (int) results[0] << std::endl;
		std::cout << "Image Data height: " << (int) results[1] << std::endl;
		std::cout << "Ptr " <<  (void *)p << std::endl;

		*size = results[6].getSize();
		*width  = (int) results[0];
		*height = (int) results[1];

		cameraProxy->releaseImage(subscriberID);

		if (imageData == nullptr) {
			std::cerr << "Could not retrieve current image." << std::endl;
			return 0;
		}
		else {
			std::cout << "Image retrieved." << std::endl;
			return 1;
		}

	}

	__declspec(dllexport) void UnsubscribeVideo() {
		// Unsubscribe the V.M.
		cameraProxy->unsubscribe(subscriberID);
	}

}



