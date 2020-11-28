#include <cstdio>
#include <cstdint>

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <kdtree.hpp>

#define B1 127.5
#define B2 16256.25
#define B3 2072671.875

void processImage(vector<vector<double>>& points, std::ofstream& ofs, const std::string& path, double imclass)
{
    std::ifstream inputFile;
    inputFile.open(path);

    if(!inputFile.is_open())
        return;

    double n, mean;
    double w, c, v;
    w = c = v = 0.0;

    inputFile >> n;
    inputFile >> mean;
    double val;
    for(double i = 0.0; i < 256.0; i += 1.0)
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

    if(ofs.is_open())
        ofs << w << ' ' << c << ' ' << v << ' ' << imclass << std::endl;

    inputFile.close();
}

int main(int argc, char** argv)
{
    if(argc < 4)
    {
        return 0;
    }
    std::string sk {argv[3]};
    std::string siters {argv[1]};
    int k {std::stoi(sk)};
    int iters {std::stoi(siters)};

    std::ofstream outputFile;
    outputFile.open("./plot/data.pt");
    vector<vector<double>> points;
    for(int i = 0; i < 8; ++i)
        for(int j = 0; j < iters; ++j)
            processImage(points, outputFile, "./dataset/" + std::to_string(i) + "/" + std::to_string(j), (double)i);
    outputFile.close();

    KDTree kdtree(points, 2);
    WPointQueue closest_points;

    outputFile.open("./plot/pred.pt");
    vector<vector<double>> predictions;
    processImage(predictions, outputFile, argv[2], -1.0);
    outputFile.close();

    std::cout << "Predict for: " << std::endl;
    std::cout << "\t? | ["
              << predictions[0][0] << ','
              << predictions[0][1] << ','
              << predictions[0][2] << ']' << std::endl;
    kdtree.knn(predictions[0], closest_points, k);

    std::map<double, pair<std::string, int>> classmap;
    classmap[0.0].first = "Interval 0: 19:00->04:00";
    classmap[1.0].first = "Interval 1: 04:00->05:30";
    classmap[2.0].first = "Interval 2: 05:30->07:00";
    classmap[3.0].first = "Interval 3: 07:00->10:00";
    classmap[4.0].first = "Interval 4: 10:00->14:00";
    classmap[5.0].first = "Interval 5: 14:00->17:00";
    classmap[6.0].first = "Interval 6: 17:00->18:00";
    classmap[7.0].first = "Interval 7: 18:00->19:00";

    printf("\nK-Nearest Neighbours (k=%d):\n", k);
    int limit = closest_points.size();
    for(int i = 0; i < limit; ++i)
    {
        ++classmap[closest_points.top().first[3]].second;
        std::cout << '\t' << closest_points.top().first[3] << " | " << '['
                  << closest_points.top().first[0] << ','
                  << closest_points.top().first[1] << ','
                  << closest_points.top().first[2] << ']' << std::endl;
        closest_points.pop_top();
    }
    std::cout << std::endl;

    double greater_idx = 0.0;
    for(const auto& it : classmap)
        if(it.second.second > classmap[greater_idx].second)
            greater_idx = it.first;

    std::cout << "Prediction: " << std::endl;
    std::cout << "\t" << greater_idx << " | ["
              << predictions[0][0] << ','
              << predictions[0][1] << ','
              << predictions[0][2] << ']' << std::endl;
    std::cout << "\t" << classmap[greater_idx].first << std::endl;

    return 0;
}
