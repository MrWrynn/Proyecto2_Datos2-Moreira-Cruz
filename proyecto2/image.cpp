//
// Created by jose on 8/5/22.
//

#ifndef PROYECTO2DATOSII_IMAGE_CPP
#define PROYECTO2DATOSII_IMAGE_CPP

#include "bmp.h"
#include "stdio.h"
#include "iostream"
#include "stdlib.h"
#include "image.hpp"

using namespace std;


void image::generate(LONG _width, LONG _height){
    width=_width;
    heigth=_height;
    data=new RGBTRIPLE*[heigth];
    for(int i=0; i<heigth; i++){
        data[i]=new RGBTRIPLE[width];
    }

}

void image::clear(){
    for (int i = 0; i < heigth; i++) {
        data[i]= nullptr;
    }
    data= nullptr;
    width=0;
    heigth=0;
}

void image::white(){
    for (int i = 0; i < heigth; ++i) {
        for (int j = 0; j < width; ++j) {
            data[i][j]={(BYTE) 255,(BYTE) 255, (BYTE) 255};
        }
    }
};

bool image::inBounds(int x,int y){
    return x<width && y<heigth;
}

void image::SetPixel(int x, int y, BYTE red,BYTE green, BYTE blue){
    if(inBounds(x,y) && x>0 && y>0){
        data[x][y]={blue,green,red};
    }
}

/*bool image::SetPixel(int x, int y, double red,double green, double blue){
    return SetPixel(x,y,red*255+0.5,blue*255+0.5,green*255+0.5);
}*/

bool image::read(const char* file){
    FILE * intpr;
    intpr=fopen(file,"r");
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER),1,intpr);

    BITMAPINFOHEADER bi;
    fread(&bi,sizeof(BITMAPINFOHEADER),1,intpr);
    width=bi.biWidth;
    heigth=bi.biHeight;

    int padding=(width*sizeof(RGBTRIPLE))%4;

    int rowSize= width* sizeof(RGBTRIPLE)+padding;

    BYTE* row=new BYTE[rowSize];
    data=new RGBTRIPLE*[heigth];
    for (int i = 0; i < heigth; i++) {
        data[i]=new RGBTRIPLE[width];
        fread(row, sizeof(BYTE), rowSize,intpr);
        for (int j = 0; j < width; j++) {
            data[i][j]={
                    row[j*3],
                    row[j* 3 + 1],
                    row[j*3+2]};

        }

    }

    fclose(intpr);
    return true;
}

bool image::write(const char* file){
    FILE* outptr;
    outptr= fopen(file,"w");
    int padding = (width*sizeof(RGBTRIPLE))%4;
    DWORD imgSize =heigth*(width* sizeof(RGBTRIPLE)+padding);

    BITMAPFILEHEADER bf;
    bf.bfType=0x4D42;
    bf.bfSize=sizeof(BITMAPFILEHEADER)+ sizeof(BITMAPINFOHEADER)+imgSize;
    bf.bfReserved1=0;
    bf.bfReserved2=0;
    bf.bfOffBits= sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
    fwrite(&bf, sizeof(BITMAPFILEHEADER),1,outptr);

    BITMAPINFOHEADER bi;
    bi.biSize= sizeof(BITMAPINFOHEADER);
    bi.biWidth=width;
    bi.biHeight=heigth;
    bi.biPlanes=1;
    bi.biBitCount=24;
    bi.biCompression=0;
    bi.biSizeImage=0;
    bi.biXPelsPerMeter=0;
    bi.biYPelsPerMeter=0;
    bi.biClrUsed=0;
    bi.biClrImportant=0;
    fwrite(&bi, sizeof(BITMAPINFOHEADER),1,outptr);

    //data
    for (int i = 0; i < heigth; i++) {

        fwrite(data[i], sizeof(RGBTRIPLE),width,outptr);

        if(padding>0){
            for (int j = 0; j < padding; j++) {
                fputc(0x00,outptr);
            }
        }

    }
    fclose(outptr);
    return true;

}

void image::reflectX(){
    for (int i = 0; i < heigth/2; i++) {
        RGBTRIPLE* tmp=data[i];
        data[i]=data[heigth-1-i];
        data[heigth-1-i]=tmp;
    }
}

void image::reflectY(){
    for (int i = 0; i < heigth; ++i) {
        for (int j = 0; j < width/2; ++j) {
            RGBTRIPLE temp=data[i][j];
            data[i][j]=data[i][width-1-j];
            data[i][width-1-j]=temp;

        }

    }
}

void image::reflectXY(){
    RGBTRIPLE** newData=new RGBTRIPLE*[heigth];
    for (int i = 0; i < heigth; ++i) {
        newData[i]=new RGBTRIPLE[width];
    }
    for (int i = 0; i < heigth; ++i) {
        for (int j = 0; j < width; ++j) {
            newData[i][j]=data[j][i];;
        }
    }
    data=newData;
}

void image::rotate_rigth(){
    reflectXY();
    reflectX();
};

void image::rotate_left(){
    reflectXY();
    reflectY();
};

void image::dark(){
    for (int i = 0; i < heigth; ++i) {
        for (int j = 0; j < width; ++j) {
            int blue=(int) data[i][j].rgbtBlue;
            int green=(int) data[i][j].rgbtGreen;
            int red=(int) data[i][j].rgbtRed;
            SetPixel(i,j,(BYTE) (red/3),(BYTE) (green/3), (BYTE) (blue/3));
        }
    }
}

void image::grey(){
    for (int i = 0; i < heigth; ++i) {
        for (int j = 0; j < width; ++j) {
            int blue=(int) data[i][j].rgbtBlue;
            int green=(int) data[i][j].rgbtGreen;
            int red=(int) data[i][j].rgbtRed;
            int greey=(blue+green+red)/3;
            SetPixel(i,j,(BYTE) greey,(BYTE) greey, (BYTE) greey);
        }
    }

}

void image::negative(){
    for (int i = 0; i < heigth; ++i) {
        for (int j = 0; j < width; ++j) {
            int blue=(int) data[i][j].rgbtBlue;
            int green=(int) data[i][j].rgbtGreen;
            int red=(int) data[i][j].rgbtRed;
            SetPixel(i,j,(BYTE) red-255,(BYTE) green-255, (BYTE) blue-255);
        }
    }
}

RGBTRIPLE image::getPixel(int x, int y){
    return data[x][y];
}

void image::linea(float x1, float y1, float x2, float y2) {
    if(x1==x2){
        for(int j=y1;j<y2;j++){
            int i=x1;
            SetPixel(i,j,(BYTE) 255, (BYTE) 0, (BYTE) 0);
        }

        for(int j=y2;j<y1;j++){
            int i=x1;
            SetPixel(i,j,(BYTE) 255, (BYTE) 0, (BYTE) 0);
        }
    }
    else{
        float m=(y1-y2)/(x1-x2);
        float b=y1-x1*m;
        for (int i = x1; i < x2 ; ++i) {
            float j=i*m+b;
            int jentero=(int) j;
            if(j-jentero!=0){
                SetPixel(i,jentero+1,(BYTE) 255, (BYTE) 0, (BYTE) 0);
                    }
            SetPixel(i,jentero,(BYTE) 255, (BYTE) 0, (BYTE) 0);
        }

        for (int i = x2; i < x1 ; ++i) {
            float j=i*m+b;
                    int jentero=(int) j;
                    if(j-jentero!=0){
                        SetPixel(i,jentero+1,(BYTE) 255, (BYTE) 0, (BYTE) 0);
                    }
                    SetPixel(i,jentero,(BYTE) 255, (BYTE) 0, (BYTE) 0);
        }
    }
}

int image::getHeight(){
    return heigth;
}

int image::getWidth(){
    return width;
}





#endif //PROYECTO2DATOSII_IMAGE_CPP
