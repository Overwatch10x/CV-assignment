#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>  // Use features2d for SIFT
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Load the first image in grayscale
    Mat inputImage = imread("img1.png", IMREAD_GRAYSCALE);
    if (inputImage.empty()) {
        cout << "Failed to load the first image!" << endl;
        return -1;
    }

    // Step 1: Harris Corner Detection
    Mat harrisResponse, harrisResponseNormalized;
    harrisResponse = Mat::zeros(inputImage.size(), CV_32FC1);

    cornerHarris(inputImage, harrisResponse, 2, 3, 0.04);
    normalize(harrisResponse, harrisResponseNormalized, 0, 255, NORM_MINMAX, CV_32FC1, Mat());

    // Convert to 8-bit for visualization
    Mat harrisCornersDisplay;
    convertScaleAbs(harrisResponseNormalized, harrisCornersDisplay);

    // Draw detected corners on the original image
    for (int y = 0; y < harrisResponseNormalized.rows; y++) {
        for (int x = 0; x < harrisResponseNormalized.cols; x++) {
            if ((int)harrisResponseNormalized.at<float>(y, x) > 200) {
                circle(inputImage, Point(x, y), 5, Scalar(255), 2);
            }
        }
    }

    // Step 2: SIFT Feature Detection
    Ptr<SIFT> siftDetector = SIFT::create();
    vector<KeyPoint> detectedKeypoints;
    Mat keypointDescriptors;

    siftDetector->detectAndCompute(inputImage, noArray(), detectedKeypoints, keypointDescriptors);

    // Draw keypoints on the image
    Mat keypointsImage;
    drawKeypoints(inputImage, detectedKeypoints, keypointsImage, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

    // Step 3: Feature Matching with SSD and Ratio Test
    Mat secondImage = imread("img2.png", IMREAD_GRAYSCALE);
    if (secondImage.empty()) {
        cout << "Failed to load the second image!" << endl;
        return -1;
    }

    vector<KeyPoint> detectedKeypoints2;
    Mat keypointDescriptors2;
    siftDetector->detectAndCompute(secondImage, noArray(), detectedKeypoints2, keypointDescriptors2);

    BFMatcher featureMatcher(NORM_L2);
    vector<vector<DMatch>> matches;
    featureMatcher.knnMatch(keypointDescriptors, keypointDescriptors2, matches, 2);

    // Filter matches using the ratio test
    vector<DMatch> filteredMatches;
    for (size_t i = 0; i < matches.size(); i++) {
        if (matches[i][0].distance < 0.75 * matches[i][1].distance) {
            filteredMatches.push_back(matches[i][0]);
        }
    }

    // Draw the matched keypoints
    Mat matchedImage;
    drawMatches(inputImage, detectedKeypoints, secondImage, detectedKeypoints2, filteredMatches, matchedImage, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // Display results
    imshow("Harris Corners", harrisCornersDisplay);
    imshow("Detected Keypoints", keypointsImage);
    imshow("Matched Keypoints", matchedImage);

    waitKey(0);
    return 0;
}
