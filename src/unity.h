#pragma once

#ifndef UNITY_H
#define UNITY_H
#include <opencv2/opencv.hpp>   // Include OpenCV API
#include <iostream>
#include <fstream>

void  depthToPointCloud(const cv::Mat& src, cv::Mat_< cv::Vec3f >& points);
void exportToPly(const std::string& path, cv::Mat_< cv::Vec3f > points);
std::ofstream writePlyHeader(const std::string& fname, int count, bool pointOnly);

#endif