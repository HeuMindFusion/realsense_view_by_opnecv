#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <opencv2/opencv.hpp>   // Include OpenCV API
#include "../src/unity.h"
#include <direct.h>

int main(int argc, char* argv[]) 
{
	int count = 0;

	std::string num;

	rs2::pipeline pipe;     //Contruct a pipeline which abstracts the device

	rs2::config cfg;    //Create a configuration for configuring the pipeline with a non default profile

	int w = 1280;

	int h = 720;

	cfg.enable_stream(RS2_STREAM_COLOR, w, h, RS2_FORMAT_BGR8, 15);

	cfg.enable_stream(RS2_STREAM_DEPTH, w, h, RS2_FORMAT_Z16, 15);

	cfg.enable_stream(RS2_STREAM_INFRARED, 1, w, h, RS2_FORMAT_Y8, 15);

	cfg.enable_stream(RS2_STREAM_INFRARED, 2, w, h, RS2_FORMAT_Y8, 15);
	//depthSensor.set_option(RS2_OPTION_EMITTER_ENABLED,true);
	rs2::pipeline_profile selection = pipe.start(cfg);

	rs2::colorizer color_map;
	rs2::frameset frames;

	frames = pipe.wait_for_frames();
    std::string  name = ROOT_DIR "/data_scene_120/";
	_mkdir(name.c_str());
	//Get each frame
	int index = 0;
	
	while (index <=60)
	{
#if 0	
		index += 1;
        std::cout << index << std::endl;
		frames = pipe.wait_for_frames();

		auto IR_frame_left = frames.get_infrared_frame(1);
		auto IR_frame_right = frames.get_infrared_frame(2);
		auto depth_frame = frames.get_depth_frame();
		cv::Mat left(cv::Size(w, h), CV_8UC1, (void*)IR_frame_left.get_data());
		cv::Mat right(cv::Size(w, h), CV_8UC1, (void*)IR_frame_right.get_data());
		cv::Mat depth(cv::Size(w, h), CV_16UC1, (void*)depth_frame.get_data(), cv::Mat::AUTO_STEP);
		std::string leftName = name + "left" + std::to_string(index) + ".png";
		std::string  rightName = name + "right" + std::to_string(index) + ".png";
		std::string  depthName = name + "depth" + std::to_string(index) + ".png";
        cv::imwrite(leftName, left);
        cv::imwrite(rightName, right);
        cv::imwrite(depthName, depth);
        cv::imshow("left", left);
        cv::waitKey(30);
#else    
       
        frames = pipe.wait_for_frames();

        auto IR_frame_left = frames.get_infrared_frame(1);
        auto IR_frame_right = frames.get_infrared_frame(2);
        auto depth_frame = frames.get_depth_frame();
        cv::Mat left(cv::Size(w, h), CV_8UC1, (void*)IR_frame_left.get_data());
        cv::Mat right(cv::Size(w, h), CV_8UC1, (void*)IR_frame_right.get_data());
        cv::Mat depth(cv::Size(w, h), CV_16UC1, (void*)depth_frame.get_data(), cv::Mat::AUTO_STEP);
        
        cv::imshow("left", left);
        
        if (cv::waitKey(30) == 32)
        {
            index += 1;
            std::cout << index << std::endl;
            std::string leftName = name + "left" + std::to_string(index) + ".png";
            std::string  rightName = name + "right" + std::to_string(index) + ".png";
            std::string  depthName = name + "depth" + std::to_string(index) + ".png";
            cv::imwrite(leftName, left);
            cv::imwrite(rightName, right);
            cv::imwrite(depthName, depth);

        }
#endif
       
	}

	
}
