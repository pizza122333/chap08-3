#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat src = imread("lenna.bmp");
    if (src.empty()) {
        cerr << "사진을 찾을 수 없어요!" << endl;
        return -1;
    }

    float W = src.cols;
    float H = src.rows;

    // 원래 사진의 꼭짓점 3개
    Point2f srcPts[3] = { Point2f(0, 0), Point2f(W, 0), Point2f(0, H) };

    // 줄어들고 정중앙으로 이동할 꼭짓점 3개
    Point2f dstPts[3] = {
        Point2f(W / 4.0f, H / 4.0f),
        Point2f(3.0f * W / 4.0f, H / 4.0f),
        Point2f(W / 4.0f, 3.0f * H / 4.0f)
    };

    // 지도 만들고 변환하기
    Mat M = getAffineTransform(srcPts, dstPts);
    Mat dst;
    warpAffine(src, dst, M, src.size());

    // 화면에 보여주기
    imshow("src", src);
    imshow("dst2", dst);

    // ?? [에러 해결단!] 컴퓨터가 멈추지 않고 아무 키나 누를 때까지 무한히 기다리게 합니다.
    waitKey(0);

    return 0;
}