//
// Created by jose on 15/5/22.
//

#ifndef PROYECTO2DATOSII_IMAGE_HPP
#define PROYECTO2DATOSII_IMAGE_HPP
#include "bmp.h"
#include "string"


class image{
public:
    void generate(LONG _width, LONG _height);
    void clear();
    void white();
    bool inBounds(int x,int y);
    void SetPixel(int x, int y,BYTE red,BYTE green, BYTE blue);
    //bool SetPixel(int x, int y, double red,double green, double blue);
    bool read(const char* file);
    bool write(const char* file);
    void reflectX();
    void reflectY();
    void reflectXY();
    void rotate_rigth();
    void rotate_left();
    void dark();
    void grey();
    void negative();
    void mix();
    RGBTRIPLE getPixel(int x,int y);
    void linea(float x1,float y1, float x2, float y2);
    int getWidth();
    int getHeight();
    void setGrosor(int _grosor);
    void BFSpaint(int si, int sj);
    void rectangle(float x1,float y1, float x2, float y2);
    void triangulo(float x1,float y1, float x2, float y2);
    void AumentarGrosor();
    void DisminuirGrosor();
    void rombo(float x1,float y1, float x2, float y2);
    void setColor(RGBTRIPLE _color);
    void SelectRectangle(float x1,float y1, float x2, float y2);
    void ChageMode();
    void setmode(std::string _mode);

private:
    LONG width;
    LONG heigth;
    RGBTRIPLE** data;
    int grosor=1;
    RGBTRIPLE color={(BYTE) 0,(BYTE) 0,(BYTE) 0 };
    bool compararColor(RGBTRIPLE colorInical, RGBTRIPLE colorcasilla);
    std::string mode="pintar";

};

#endif //PROYECTO2DATOSII_IMAGE_HPP
