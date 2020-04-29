#include <iostream>
#include <random>
#include <vector>
#include <chrono>


// #include <delaunator.hpp>
#include "delaunator.h"
#include "vector2.h"
#include "triangle.h"
#include "delaunay.h"

int main(int argc, char* argv[]) {

    //Get argv
    int numberPoints = 100;
	if (argc>1)
	{
		numberPoints = atoi(argv[1]);
	}


    //Generate random points
    std::default_random_engine eng(std::random_device{}());
    std::uniform_real_distribution<double> dist_w(0, 800);
    std::uniform_real_distribution<double> dist_h(0, 600);
    
    std::cout << "Generating " << numberPoints << " random points" << std::endl;


    //Transform to data needed
    //data for the first algorithm 1 (delaunator-cpp)
    std::vector<double> pts1;
    for (int i = 0; i < numberPoints; i++)
    {
        pts1.push_back(dist_w(eng));
        pts1.push_back(dist_h(eng));
    }
    std::cout << "pts1 size: " << pts1.size() << std::endl;

    //data for the second algorithm_2 (delaunay-triangulation)
    std::vector<Vector2> pts2;
    for (int i = 0; i < numberPoints; i++)
    {
        pts2.push_back(Vector2{dist_w(eng), dist_h(eng)});
    }
    std::cout << "pts2 size: " << pts2.size() << std::endl;


    //Calculate and accumulate time seperately
    const auto t_1 = std::chrono::high_resolution_clock::now();
    delaunator::Delaunator d1(pts1);
    const auto t_2 = std::chrono::high_resolution_clock::now();
    Delaunay d2;
    std::vector<Triangle> triangles = d2.triangulate(pts2);
    const auto t_3 = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double> diff1 = t_2 - t_1;
    const std::chrono::duration<double> diff2 = t_3 - t_2;

    std::cout << "#1 algorithm spends " << diff1.count() * 1000 << " ms" << std::endl;
    std::cout << "#2 algorithm spends " << diff2.count() * 1000 << " ms" << std::endl;
}
