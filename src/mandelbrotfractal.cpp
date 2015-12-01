#include "simpio.h"
#include "console.h"
#include "gwindow.h"
using namespace std;


/**
 * Get Maximum iterations number for determining whether the point belongs to the Mandelbrot set.
 *
 * @return - Max iteration number.
 */
int getMaxIterationNumber() {
    int result;
    while (true) {
        result = getInteger("Input the max iteration number (> 10):");
        if (result > 10)
            break;
        cout << "Illegal value. Try again... " << endl;
    }
    return result;
}


/**
 * Return the pixel color depending on whether the pixel belongs to the Mandelbrot set.
 *
 * @param x - Descartes coordinate x of the pixel.
 * @param y - Descartes coordinate y of the pixel.
 * @param maxIterationNumber - Maximum iterations number for determining
 *                             whether the point belongs to the Mandelbrot set.
 * @return - If pixel belong to the Mandelbrot set its color sets to black or other color in other case.
 */
int getPixelColor(double x, double y, int maxIterationNumber) {
    double zReal = 0;
    double zImaginary = 0;
    int iterationNumber = 0;
    while (true) {
        if (iterationNumber == maxIterationNumber)
            return 0;
        if ((zReal * zReal + zImaginary * zImaginary) > 4)
            break;
        double zTemp = zReal * zReal - zImaginary * zImaginary;
        zImaginary = 2 * zReal * zImaginary + y;
        zReal = zTemp + x;
        iterationNumber++;
    }
    int result = (iterationNumber << 16) + (iterationNumber << 8) + iterationNumber;
    return result;
}


/**
 * Draw the Mandelbrot fractal.
 *
 * @param maxIterationNumber - Maximum iterations number for determining
 *                             whether the point belongs to the Mandelbrot set.
 */
void drawMandelbrotFractal(int maxIterationNumber) {
    const int SCALE = 200;
    GWindow window(3.5 * SCALE, 3.5 * SCALE);
    for (double y = -1.25; y <= 1.25; y += 0.01)
        for (double x = -2; x <= 0.5; x += 0.01) {
            int pixelColor = getPixelColor(x, y, maxIterationNumber);
            window.setColor(pixelColor);
            window.drawRect((2.5 + x) * SCALE, (1.75 - y) * SCALE, 1, 1);
        }
}


int main() {
    int maxIterationNumber = getMaxIterationNumber();
    drawMandelbrotFractal(maxIterationNumber);
    return 0;
}
