#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <cstdio>
#include <cstdint>

#include <vector>
#include <iostream>

#include <octree.hpp>
#include <kdtree.hpp>
#include <algorithm.hpp>

using namespace cv;

/*
int main()
{
    int size;
    std::cin >> size;
    std::vector<int> data;
    data.reserve(size);

    int val;
    for(int i = 0; i < size; ++i)
    {
        std::cin >> val;
        data.push_back(val);
    }

    int median = findMedian<int, std::vector<int>&>(data, size);
    printf("Median is %d\n", median);

    return 0;
}
*/

int main()
{
    return 0;
}

/*
int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        return 0;
    }

    std::string image_path = samples::findFile(argv[1]);
    Mat img = imread(image_path, IMREAD_COLOR);
    if(img.empty())
    {
        std::cerr << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    Octree octree {};
    Color read {0, 0, 0};

    for(int i = 0; i < img.rows; ++i)
    {
        for(int j = 0; j < img.cols; ++j)
        {
            Vec3b& color {img.at<Vec3b>(i, j)};
            read.b = color[0]; // B
            read.g = color[1]; // G
            read.r = color[2]; // R

            octree.insertColor(read);
        }
    }

    imshow("Display window", img);

    int k = waitKey(0); // Wait for a keystroke in the window
    uint8_t n_depth = *argv[2] - '0'; // New color depth
    if(k == 's')
    {
        octree.reduct(8 - n_depth);

        Color processed {0, 0, 0};
        for(int i = 0; i < img.rows; ++i)
        {
            for(int j = 0; j < img.cols; ++j)
            {
                Vec3b& color {img.at<Vec3b>(i, j)};
                read.b = color[0]; // B
                read.g = color[1]; // G
                read.r = color[2]; // R

                processed = octree.getProcessedColor(read);
                color[0] = processed.b; // B
                color[1] = processed.g; // G
                color[2] = processed.r; // R
            }
        }
        std::vector<Color> palette;
        octree.getPalette(palette);
        Mat palette_img {32, 32 * (int)palette.size(), CV_8UC3, Scalar{0, 0, 0}};
        for(int l = 0; l < 32; ++l)
        {
            for(int i = 0; i < 32 * palette.size(); ++i)
            {
                Vec3b& color {palette_img.at<Vec3b>(l, i)};
                color[0] = palette[i / 32].b; // B
                color[1] = palette[i / 32].g; // G
                color[2] = palette[i / 32].r; // R
            }
        }

        printf("SUCCESS! Palette with: %llu colors\n", palette.size());
        imshow("Result", img);
        imshow("Palette", palette_img);

        k = waitKey(0);
        if(k == 's')
        {
            std::string out {argv[1]};
            std::size_t pos {out.find(".")};
            out = out.substr(0, pos) + "_proc_" + std::to_string(n_depth) + "b.png";
            imwrite(out, img);
        }
    }
    return 0;
}
*/
