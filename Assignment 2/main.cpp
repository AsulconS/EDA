#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <cstdio>
#include <cstring>
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
        octree.reduction(*argv[2] - '0');

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
                printf("PROCESSED! i = %d, j = %d | [%u, %u, %u]\n", i, j, processed.r, processed.g, processed.b);
                color[0] = processed.b; // B
                color[1] = processed.g; // G
                color[2] = processed.r; // R
            }
        }

        char endBuffer[64];
        strcpy(endBuffer, argv[1]);
        printf("SUCCESS!\n");
        imshow("Result", img);

        k = waitKey(0);
        if(k == 's')
        {
            imwrite(strcat(endBuffer, "_proc.png"), img);
        }
    }
    return 0;
}
