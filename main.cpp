#include <iostream>
#include <opencv2/opencv.hpp>
#include <fftw3.h>

using namespace std;
using namespace cv;

int idx = 0;
Mat contornos;
Mat canny;
vector<vector<Point> > puntos;
vector<Vec4i> jerarquia;

void trackbarEvent(int v, void *data){
    contornos =  Mat::zeros(canny.size(), CV_8UC3);
    findContours(canny, puntos, jerarquia, RETR_TREE, CHAIN_APPROX_NONE);
    drawContours(contornos, puntos, idx, Scalar(10,207,10), 1, 8, jerarquia);
    imshow("Contornos", contornos);
}

int main(int, char**) {
    Mat imagen = imread("FiguraIrregluar1.png");
    resize(imagen, imagen, Size(), 1, 1);

    Mat imagenGauss;
    GaussianBlur(imagen, imagenGauss, Size(5,5), 0.13, 0.13);
    double threshInf = 100.0;
    double ratio = 3.0;

    Canny(imagenGauss, canny, threshInf, threshInf*ratio);
    contornos =  Mat::zeros(canny.size(), CV_8UC3); 
    findContours(canny, puntos, jerarquia, RETR_TREE, CHAIN_APPROX_NONE);
    cout << "Contornos: " << puntos.size() << endl;
    cout << "Niveles: " << jerarquia.size() << endl;

    int maximo = 0;
    idx = 0;
    for (int i=0;i<puntos.size();i++){
        if (maximo<puntos[i].size()){
            idx = i;
            maximo = puntos[i].size();
        }
    }

    cout << "Máximo: " << maximo << " Idx: " << idx << endl;

    drawContours(contornos, puntos, idx, Scalar(10,207,10), 1, 8, jerarquia);


    namedWindow("Imagen", WINDOW_AUTOSIZE);
    namedWindow("Gauss", WINDOW_AUTOSIZE);
    namedWindow("Canny", WINDOW_AUTOSIZE);
    namedWindow("Contornos", WINDOW_AUTOSIZE);

    createTrackbar("Contorno (Idx)", "Imagen", &idx, puntos.size()-1, trackbarEvent, NULL);

    imshow("Imagen", imagen);
    imshow("Gauss", imagenGauss);
    imshow("Canny", canny);
    imshow("Contornos", contornos);

    waitKey(0);

    destroyAllWindows();
    return(0);
}
