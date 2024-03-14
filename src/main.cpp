
#include "pch.h"


void a () {
    cv::CascadeClassifier face_cascade = cv::CascadeClassifier(MODULES"/haarcascade_frontalface_default.xml");

    cv::Mat img_source;
    img_source = cv::imread(ASSERTS"/people.jpg");

    cv::Mat img_gray;
    cvtColor(img_source, img_gray, cv::COLOR_BGR2GRAY);

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(img_gray, faces ,1.3, 5, 0, cv::Size(30, 30));

    cv::rectangle(img_source, faces[static_cast<int>(1)], cv::Scalar(0, 255, 0));

    cv::imwrite(DIST"/face.png", img_source);
//    cv::waitKey(0);

//    cv::Mat img = cv::imread(ASSERTS"/pic2.jpg");
}

void b (const std::string& path, std::size_t idx) {


    cv::Mat img = cv::imread(path);

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

    if (idx == 1) {
        cv::imwrite(DIST"/pic1_gray.png", img_gray);
        cv::imwrite(DIST"/pic1_bilateralFilter.png", img_bilateralFilter);
        cv::imwrite(DIST"/pic1_threshold.png", img_threshold);
        cv::imwrite(DIST"/pic1_Typology.png", img_close);
    } else if (idx== 2) {
        cv::imwrite(DIST"/pic2_gray.png", img_gray);
        cv::imwrite(DIST"/pic2_bilateralFilter.png", img_bilateralFilter);
        cv::imwrite(DIST"/pic2_threshold.png", img_threshold);
        cv::imwrite(DIST"/pic2_Typology.png", img_close);
    } else if (idx == 3) {
        cv::imwrite(DIST"/pic3_gray.png", img_gray);
        cv::imwrite(DIST"/pic3_bilateralFilter.png", img_bilateralFilter);
        cv::imwrite(DIST"/pic3_threshold.png", img_threshold);
        cv::imwrite(DIST"/pic3_Typology.png", img_close);
    }
}

int main() {

    a();
    b(ASSERTS"/pic1.jpg", 1);
    b(ASSERTS"/pic2.jpg", 2);
    b(ASSERTS"/pic3.jpg", 3);

//    cv::waitKey(0);
    return 0;
}
