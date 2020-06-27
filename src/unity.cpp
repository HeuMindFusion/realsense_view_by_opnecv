#include"unity.h"

void  depthToPointCloud(const cv::Mat& src, cv::Mat_< cv::Vec3f >& points)
{
	float cx = 6.3693273925781250e+02;
	float fx = 9.0788854980468750e+02;
	float cy = 3.6053610229492188e+02;
	float fy = 9.0788854980468750e+02;
	float depth_scale = 1.0000000474974513e-03;
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			uint16_t depth = src.at<uint16_t>(j, i);
		
			float depthToMeter = depth * depth_scale;
			//cv::Vec3f& point = points.at<cv::Vec3f>(j, i);
			if (depthToMeter > 6.0)
				continue;
			points.at<cv::Vec3f>(j, i)[0] = (i - cx) * depthToMeter / fx;
			points.at<cv::Vec3f>(j, i)[1] = (j - cy) * depthToMeter / fy;
			points.at<cv::Vec3f>(j, i)[2] = depthToMeter;
			
		}
	}



}



void exportToPly(const std::string& path, cv::Mat_< cv::Vec3f > points)
{
	int numbers = 0;
	for (int y = 0; y < points.rows; y++) {
		for (int x = 0; x < points.cols; x++) {
			cv::Vec3f point = points.at<cv::Vec3f>(y, x);
			if (isnan(point[0]) || isnan(point[1]) || isnan(point[2]))
				continue;

			numbers++;
		}
	}
	// Write the ply file
	std::ofstream out = writePlyHeader(path, numbers, true);
	for (int y = 0; y < points.rows; y++) {
		for (int x = 0; x < points.cols; x++) {
			cv::Vec3f point = points.at<cv::Vec3f>(y, x);
			if (isnan(point[0]) || isnan(point[1]) || isnan(point[2]))
				continue;
			out << point(0) << " ";
			out << point(1) << " ";
			out << point(2) << " \n";
		}
	}
}

std::ofstream writePlyHeader(const std::string& fname, int count, bool pointOnly)
{
	std::ofstream out(fname);
	out << "ply\n";
	out << "format ascii 1.0\n";
	out << "comment pointcloud saved from Realsense Viewer\n";
	out << "element vertex " << count << "\n";
	out << "property float" << sizeof(float) * 8 << " x\n";
	out << "property float" << sizeof(float) * 8 << " y\n";
	out << "property float" << sizeof(float) * 8 << " z\n";

	if (!pointOnly)
	{
		out << "property float" << sizeof(float) * 8 << " nx\n";
		out << "property float" << sizeof(float) * 8 << " ny\n";
		out << "property float" << sizeof(float) * 8 << " nz\n";

		out << "property uchar red\n";
		out << "property uchar green\n";
		out << "property uchar blue\n";
	}
	out << "end_header\n";

	return out;
}
