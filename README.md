
# Computer Vision Assignment - README

## Overview
This project implements a computer vision application using **OpenCV** to perform keypoint detection, feature description, and feature matching. The application is developed in **C++** using **Code::Blocks** with **OpenCV 4.10.0** on **Windows**.

## Assignment Objectives
The assignment consists of three primary tasks:

1. **Keypoint Detection**: Identify points of interest in an image using the Harris corner detection method. **[8 Marks]**
2. **Feature Description**: Compute scale-invariant feature transform (SIFT) descriptors at each detected keypoint. **[6 Marks]**
3. **Feature Matching**: Match features using the Sum of Squared Differences (SSD) and the ratio distance method to determine the closest matches.

## Prerequisites
- **OpenCV 4.10.0** (with extra modules, including `features2d`)
- **MinGW** as the compiler
- **Code::Blocks** as the Integrated Development Environment (IDE)
- **CMake** for building OpenCV
- Properly configured environment variables for OpenCV

## Installation & Setup

### Step 1: OpenCV Installation
1. Download the OpenCV source code and extract it to a suitable location.
2. Use **CMake** to configure the OpenCV build:
   - Ensure `BUILD_opencv_xfeatures2d` is checked if necessary.
3. Build OpenCV using **MinGW** and use the `-j4` flag for parallel compilation:
   ```bash
   cmake -G "MinGW Makefiles" -D CMAKE_CXX_FLAGS="-std=c++11" ..  # Inside the build directory
   mingw32-make -j4
   ```

### Step 2: Compiler Settings
1. Open **Code::Blocks** and set the project to use **MinGW**.
2. In **Project > Build options > Linker settings**, link the required OpenCV libraries:
   - `libopencv_core4100.dll.a`
   - `libopencv_imgcodecs4100.dll.a`
   - `libopencv_highgui4100.dll.a`
   - `libopencv_features2d4100.dll.a`

3. Ensure the paths to the OpenCV DLLs are included in the system's **PATH** environment variable or copy the DLLs to the project directory.

### Step 3: Running the Application
- Place the input images (`img1.png` and `img2.png`) in the same directory as the executable.
- Compile and run the program. The application will:
  - Load the images.
  - Perform Harris corner detection.
  - Compute SIFT descriptors.
  - Match features between the two images and display the results.

## Key Steps & Issues Encountered
1. **CMake Configuration**: Configured and generated the OpenCV build with necessary modules.
2. **Multithreaded Build**: Compiled OpenCV using multiple threads for faster build times.
3. **Linking Issues**: Resolved undefined references by ensuring the correct OpenCV libraries were linked.
4. **DLL Management**: Handled missing DLL issues by verifying paths and ensuring availability.
5. **Image Loading Errors**: Ensured input images were accessible by placing them in the correct directory.

## Conclusion
This project demonstrates the application of OpenCV in computer vision tasks such as keypoint detection, feature description, and matching. The objectives were achieved successfully, and the program was able to process images and display results accurately.
