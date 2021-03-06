#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

#include <octree.hpp>

using namespace cv;

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
        std::cout << "Could not read the image: " << image_path << std::endl;
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
    if(k == 's')
    {
        octree.reduct(*argv[2] - '0');

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

        char end_buffer[64];
        strcpy(end_buffer, argv[1]);
        printf("SUCCESS!\n");
        imshow("Result", img);
        imshow("Palette", palette_img);

        k = waitKey(0);
        if(k == 's')
        {
            imwrite(strcat(end_buffer, "_proc.png"), img);
        }
    }
    return 0;
}
