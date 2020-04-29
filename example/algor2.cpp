#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "vector2.h"
#include "triangle.h"
#include "delaunay.h"

//FYI, check: https://github.com/Bl4ckb0ne/delaunay-triangulation
int main()
{
	int numberPoints = 10;
	std::default_random_engine eng(std::random_device{}());
	std::uniform_real_distribution<double> dist_w(0, 800);
	std::uniform_real_distribution<double> dist_h(0, 600);

	std::vector<Vector2> points;
	for(int i = 0; i < numberPoints; ++i) {
		points.push_back(Vector2{dist_w(eng), dist_h(eng)});
	}

	Delaunay triangulation;
	const auto start = std::chrono::high_resolution_clock::now();
	const std::vector<Triangle> triangles = triangulation.triangulate(points);
	const auto end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> diff = end - start;

	std::cout << triangles.size() << " triangles generated in " << diff.count() << "s\n";
	const std::vector<Edge> edges = triangulation.getEdges();

	std::cout << " ========= ";

	std::cout << "\nPoints : " << points.size() << std::endl;
	for(const auto &p : points)
		std::cout << p << std::endl;

	std::cout << "\nTriangles : " << triangles.size() << std::endl;
	for(const auto &t : triangles)
		std::cout << t << std::endl;

	std::cout << "\nEdges : " << edges.size() << std::endl;
	for(const auto &e : edges)
		std::cout << e << std::endl;
	

	return 0;
}
