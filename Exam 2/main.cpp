#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <cstdio>
#include <cstdint>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <kdtree.hpp>

#define B1 127.5l
#define B2 16256.25l
#define B3 2072671.875l

using namespace cv;

void processImage(vector<vector<double>>& points, const std::string& path, double imclass)
{
    std::ifstream inputFile;
    inputFile.open(path);
    if(!inputFile.is_open())
    {
        return;
    }

    double n, mean;
    double w, c, v;
    w = c = v = 0.0l;

    inputFile >> n;
    inputFile >> mean;
    double val;
    for(double i = 0.0l; i < 256.0l; i += 1.0l)
    {
        inputFile >> val;
        w += val * (((i - B1) * (i - B1) * (i - B1)) / B3);
        c += val * (1 - ((i - B1) * (i - B1)) / B2);
        v += (val - mean) * (val - mean);
    }
    w /= n;
    c /= n;
    v /= n;
    points.push_back({w, c, v, imclass});

    inputFile.close();
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        return 0;
    }
    std::string siters {argv[1]};
    int iters {std::stoi(siters)};

    vector<vector<double>> points;
    for(int i = 0; i < 8; ++i)
        for(int j = 0; j <= iters; ++j)
            processImage(points, std::string{"./dataset/"} + std::to_string(i) + "/" + std::to_string(j), (double)i);

    for(const auto& p : points)
        std::cout << p[3] << " | " << '[' << p[0] << ',' << p[1] << ',' << p[2] << ']' << std::endl;

    return 0;

    WPointQueue closest_points;

    KDTree kdtree(points, 2);
    kdtree.knn({30, 81}, closest_points, 4);

    for(int i = 0; i < closest_points.size(); ++i)
    {
        std::cout << '[' << closest_points.top().first[0] << ',' << closest_points.top().first[1] << ']' << std::endl;
        closest_points.pop_top();
    }

    return 0;
}
