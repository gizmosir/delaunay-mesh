#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <math.h>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "delaunator.h"

std::vector<size_t> GetEdgesOfTriangle(size_t t)
{
    return {t * 3, t * 3 + 1, t * 3 + 2};
}

std::vector<size_t> GetAdjacentTriangle(delaunator::Delaunator d, size_t t)
{
    std::vector<size_t> adjacentTri;
    std::vector<size_t> edges = GetEdgesOfTriangle(t);
    for (auto e : edges)
    {
        size_t opposite = d.halfedges[e];
        if (opposite < d.halfedges.size()) {adjacentTri.push_back(opposite/3);}
    }
    return adjacentTri;
}

int MeshesFromNumber(const int numberPoints)
{

    if (numberPoints < 3)
    {
        std::cerr << numberPoints << " points is not enough for triangulation!" << std::endl;
        return -1;
    }

    //Generate random point
    std::default_random_engine eng(std::random_device{}());
    std::uniform_real_distribution<double> dist_w(0, 800);
    std::uniform_real_distribution<double> dist_h(0, 600);
    std::cout << "Generating " << numberPoints << " random points" << std::endl;

    std::vector<double> ptsList;
    for (int i = 0; i < numberPoints; i++)
    {
        ptsList.push_back(dist_w(eng));
        ptsList.push_back(dist_h(eng));
    }

    
    //Triangulation
    delaunator::Delaunator d(ptsList);
    std::cout << "d triangle size: " << d.triangles.size()/3 << std::endl;


    //Get adjacent triangles of each triangle
    // for (size_t i = 0; i < d.triangles.size()/3; i++)
    // {
    //     std::vector<size_t> adtris = GetAdjacentTriangle(d, i);
    // }


    //Draw triangle
    cv::Mat img = cv::Mat::zeros(600, 800, CV_8UC3);
    cv::Scalar color = cv::Scalar(60, 220, 60);
    for (size_t i = 0; i < d.triangles.size()/3; i++)
    {
        //draw triangle
        cv::Point2d pt1, pt2, pt3;
        pt1.x = d.coords[2 * d.triangles[i*3]];
        pt1.y = d.coords[2 * d.triangles[i*3] + 1];
        pt2.x = d.coords[2 * d.triangles[i*3 + 1]];
        pt2.y = d.coords[2 * d.triangles[i*3 + 1] + 1];
        pt3.x = d.coords[2 * d.triangles[i*3 + 2]];
        pt3.y = d.coords[2 * d.triangles[i*3 + 2] + 1];
        cv::line(img, pt1, pt2, color);
        cv::line(img, pt2, pt3, color);
        cv::line(img, pt3, pt1, color);

        //draw text
        cv::Point2d center;
        center.x = (pt1.x + pt2.x + pt3.x)/3;
        center.y = (pt1.y + pt2.y + pt3.y)/3;
        cv::putText(img, std::to_string(i), center, cv::FONT_HERSHEY_COMPLEX, 1, 
                    cv::Scalar(0, 255, 255), 2, 8, 0);
        
        cv::imshow("img", img);
        cv::waitKey(500);
    }

    // cv::imshow("img", img);
    cv::waitKey(0);

    return 0;
}

//detect image and triangulation
int MeshesFromImage(const std::string strImgFile)
{
    //Load image
    cv::Mat img = cv::imread(strImgFile, cv::IMREAD_COLOR);
    if (img.empty())
    {
        std::cerr << "Failed to load image at: "
                 << strImgFile << std::endl;
        return -1;
    }


    //Detect ORB keypoints
    std::vector<cv::KeyPoint> kps;
    cv::Ptr<cv::FeatureDetector> orb = cv::ORB::create(1000);
    orb->detect(img, kps);
    std::cout << "kps size: " << kps.size() << std::endl;


    //Triangulation
    std::vector<double> ptsList;
    for (auto kp : kps)
    {
        ptsList.push_back(kp.pt.x);
        ptsList.push_back(kp.pt.y);
    }
    delaunator::Delaunator d(ptsList);


    // ------ Draw and show image ------
    cv::Scalar color = cv::Scalar(60, 220, 60);
    for (size_t i = 0; i < d.triangles.size(); i+=3)
    {
        cv::Point2d pt1 = kps[d.triangles[i]].pt;
        cv::Point2d pt2 = kps[d.triangles[i+1]].pt;
        cv::Point2d pt3 = kps[d.triangles[i+2]].pt;
        cv::line(img, pt1, pt2, color);
        cv::line(img, pt2, pt3, color);
        cv::line(img, pt3, pt1, color);
    }

    cv::imshow("img", img);
    cv::waitKey(0);

    return 0;
}


int main(int argc, char* argv[])
{
    // Get argv
    int numberPoints = 40;
    std::string strImgFile = "../test.png";
    int mode = 0;
    if (argc > 1) 
    {
        std::string arg = argv[1];
        for (auto c : arg)
        {
            if (!isdigit(c))
            {
                mode = 1;
                break;
            }
        }

        if (!mode)
        {
            numberPoints = stoi(arg);
            std::cout << "Run demo with Point number: " << numberPoints << std::endl;
        }
        else
        {
            strImgFile = arg;
            std::cout << "Run demo with Image: " << strImgFile << std::endl;
        }        
    }

    // Call 
    if (!mode) {MeshesFromNumber(numberPoints);}
    else {MeshesFromImage(strImgFile);}
    
}