#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 1. 원본 사진을 안전하게 불러옵니다
    Mat src = imread("lenna.bmp");
    if (src.empty()) {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    float W = src.cols; // 가로 크기
    float H = src.rows; // 세로 크기

    // 처음에는 원본 그대로 보여주기 위해 아무것도 안 하는 기본 행렬(항등 행렬)로 시작해요
    Mat M = (Mat_<double>(2, 3) << 1, 0, 0, 0, 1, 0);
    string mode_text = "Original";

    imshow("src", src);

    // 2. 무한루프 시작! 키보드 입력을 실시간으로 감시해요
    while (true) {
        Mat dst;
        // 현재 설정된 마법 지도(M)를 사용해 사진을 변환합니다
        warpAffine(src, dst, M, src.size());

        // 화면에 현재 어떤 대칭 모드인지 글자를 남겨줘요
        putText(dst, mode_text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
            Scalar(255, 0, 0), 1, LINE_AA);

        // 결과 창을 띄웁니다
        imshow("dst", dst);

        // ?? [중요] 30ms 동안 키보드 입력을 대기하여 창이 멈추는(응답 없음) 현상을 방지합니다!
        int key = waitKey(30);

        // 3. 힌트대로 사용자가 누른 키에 따라 변환 행렬과 글자를 다르게 처리합니다
        if (key == 'a' || key == 'A') {
            // [a 키] 좌우 대칭 행렬 적용
            M = (Mat_<double>(2, 3) << -1, 0, W,
                0, 1, 0);
            mode_text = "Horizontal Flip (a)";
        }
        else if (key == 'b' || key == 'B') {
            // [b 키] 상하 대칭 행렬 적용
            M = (Mat_<double>(2, 3) << 1, 0, 0,
                0, -1, H);
            mode_text = "Vertical Flip (b)";
        }
        else if (key == 'c' || key == 'C') {
            // [c 키] 좌우 및 상하 대칭 동시 적용
            M = (Mat_<double>(2, 3) << -1, 0, W,
                0, -1, H);
            mode_text = "Both Flip (c)";
        }
        else if (key == 'o' || key == 'O') {
            // 원본으로 되돌아오는 보너스 키도 만들어 둘게요!
            M = (Mat_<double>(2, 3) << 1, 0, 0, 0, 1, 0);
            mode_text = "Original (o)";
        }
        else if (key == 'q' || key == 'Q' || key == 27) {
            // q 나 ESC를 누르면 프로그램 종료!
            break;
        }
    }

    return 0;
}