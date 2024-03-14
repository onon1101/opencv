
#include "pch.h"

int main() {

    cv::Mat img = cv::imread(ASSERTS"/pic2.jpg");

    // 灰階
    cv::Mat img_gray, img_bilateralFilter, img_threshold, img_open, img_close;
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

    // 雙邊濾波
    cv::bilateralFilter(img_gray, img_bilateralFilter, 9, 20, 20);

    // 二值化
    cv::threshold(img_bilateralFilter, img_threshold, 125, 255, cv::THRESH_BINARY);

    // 膨脹 與 腐蝕
    cv::Mat kernel_open = cv::getStructuringElement(0, cv::Size(5, 5));
    cv::Mat kernel_close = cv::getStructuringElement(0, cv::Size(2, 2));
    cv::morphologyEx(img_threshold, img_open, cv::MORPH_OPEN, kernel_open);
    cv::morphologyEx(img_open, img_close, cv::MORPH_CLOSE, kernel_close, cv::Point(-1, -1), 2);

    cv::imshow("window-test", img_close);

    cv::waitKey(0);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
