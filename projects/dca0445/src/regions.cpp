#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/* 
 * argv[1] = image 
 * argv[2] = p1.x
 * argv[3] = p1.y
 * argv[4] = p2.x
 * argv[5] = p2.y
 */

int main(int argc, char** argv)
{
    Mat image;  
    Point p1, p2;
    Rect rec;
    
    // Verifica a quantidade de argumentos. 
    if (argc != 6) 
    {
        cout << "A lista de argumentos deve ser: ./regions <image> <point1_x> "
                                    "<point1_y> <point2_x> <point2_y>" << endl;
        return -1;
    }
    
    // Check if the image can be loaded.
    image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    if (!image.data) 
    {
        cout << "The image could not be loaded!" << endl;
        return -2;
    }
    
    // Check if the points coordinates are valid numbers.
    try 
    {
        p1.x = stoi(argv[2]);
        p1.y = stoi(argv[3]);
        p2.x = stoi(argv[4]);
        p2.y = stoi(argv[5]);       
    }
    catch (const std::exception& e) 
    {
        cout << "There is a problem with the points." << endl;
        return -3;
    }
    
    // Check if the points are valid (if they are inside the image).
    if (p1.x > image.rows || p1.y > image.cols)
    {
        cout << "Point 1 is out of bounds.";
        return -4;
    }
    if (p2.x > image.rows || p2.y > image.cols)
    {
        cout << "Point 2 is out of bounds.";
        return -4;
    }

    // Calculate the negative for the specified region.
    rec = Rect(p1, p2);
    for (int i = rec.x; i < rec.height; i++)
    {
        for (int j = rec.y; j < rec.width; j++)
        {
            image.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
        }
    }

    imshow("result", image);  
    waitKey(10000);

    return 0;
}
