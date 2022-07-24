#include <iostream>
#include <opencv2/opencv.hpp>
#include <fftw3.h>

using namespace std;
using namespace cv;

int idx = 0;
Mat contornos;
Mat canny;
vector<vector<Point>> puntos;
vector<Vec4i> jerarquia;

void trackbarEvent(int v, void *data)
{
    contornos = Mat::zeros(canny.size(), CV_8UC3);
    findContours(canny, puntos, jerarquia, RETR_TREE, CHAIN_APPROX_NONE);
    drawContours(contornos, puntos, idx, Scalar(10, 207, 10), 1, 8, jerarquia);
    imshow("Contornos", contornos);
}

double distancia(Point origen, Point borde)
{
    return sqrt((origen.x - borde.x) * (origen.x - borde.x) + (origen.y - borde.y) * (origen.y - borde.y));
}

int main(int, char **)
{
    Mat imagen = imread("FiguraIrregluar1.png");
    resize(imagen, imagen, Size(), 1, 1);

    Mat imagenGauss;
    GaussianBlur(imagen, imagenGauss, Size(5, 5), 0.13, 0.13);
    double threshInf = 100.0;
    double ratio = 3.0;

    Canny(imagenGauss, canny, threshInf, threshInf * ratio);
    contornos = Mat::zeros(canny.size(), CV_8UC3);
    findContours(canny, puntos, jerarquia, RETR_TREE, CHAIN_APPROX_NONE);
    cout << "Contornos: " << puntos.size() << endl;
    cout << "Niveles: " << jerarquia.size() << endl;

    int maximo = 0;
    idx = 0;
    for (int i = 0; i < puntos.size(); i++)
    {
        if (maximo < puntos[i].size())
        {
            idx = i;
            maximo = puntos[i].size();
        }
    }

    cout << "Máximo: " << maximo << " Idx: " << idx << endl;

    drawContours(contornos, puntos, idx, Scalar(10, 207, 10), 1, 8, jerarquia);

    /*
     */

    imagen = imread("FiguraIrregluar1.png", IMREAD_GRAYSCALE);

    imagenGauss;
    GaussianBlur(imagen, imagenGauss, Size(5, 5), 0.13, 0.13);
    threshInf = 100.0;
    ratio = 3.0;

    Canny(imagenGauss, canny, threshInf, threshInf * ratio);
    // threshold(imagenGauss, canny, 100, 255, THRESH_BINARY);
    contornos = Mat::zeros(canny.size(), CV_8UC3);

    findContours(canny, puntos, jerarquia, RETR_TREE, CHAIN_APPROX_NONE);
    cout << "Contornos: " << puntos.size() << endl;
    cout << "Niveles: " << jerarquia.size() << endl;

    maximo = 0;
    idx = 0;
    for (int i = 0; i < puntos.size(); i++)
    {
        if (maximo < puntos[i].size())
        {
            idx = i;
            maximo = puntos[i].size();
        }
    }

    cout << "Máximo: " << maximo << " Idx: " << idx << endl;

    drawContours(contornos, puntos, idx, Scalar(10, 207, 10), 1, 8, jerarquia);
    cout << "Puntos 2: " << puntos[0].size() << endl;

    Moments momentos = moments(canny, true);
    double cx = momentos.m10 / momentos.m00;
    double cy = momentos.m01 / momentos.m00;
    Point centroide = Point(cx, cy);
    circle(contornos, centroide, 3, Scalar(10, 10, 200), 2);

    vector<double> distancias;

    double disMax = -1;
    double tmp = 0.0;

    for (int i = 0; i < puntos[2].size(); i++)
    {
        tmp = distancia(centroide, puntos[2][i]);
        if (disMax < tmp)
        {
            disMax = tmp;
        }
        distancias.push_back(tmp);
    }

    int ancho = 1024;
    int alto = 768;
    Mat lienzo = Mat(Size(800, 600), CV_8UC3, Scalar(255, 255, 255));
    double escala = 600 / disMax;

    for (int i = 0; i < distancias.size(); i++)
    {
        circle(lienzo, Point(i, lienzo.rows - distancias[i] * escala), 1, Scalar(10, 10, 233), 1);
    }

    namedWindow("Imagen", WINDOW_AUTOSIZE);
    namedWindow("Gauss", WINDOW_AUTOSIZE);
    namedWindow("Canny", WINDOW_AUTOSIZE);
    namedWindow("Contornos", WINDOW_AUTOSIZE);
    namedWindow("Firma", WINDOW_AUTOSIZE);

    imshow("Imagen", imagen);
    imshow("Gauss", imagenGauss);
    imshow("Canny", canny);
    imshow("Contornos", contornos);
    imshow("Firma", lienzo);

    /*
        TRANSFORMADA DE FOURIER UTILIZANDO FFTW3
    */

   //Asignar espacios de memoria para la entrada y la salida
    double complejo [distance.size()];
    //fftw_complex in[sizeof(distancias)];
    waitKey(0);

    destroyAllWindows();
    return (0);
}


