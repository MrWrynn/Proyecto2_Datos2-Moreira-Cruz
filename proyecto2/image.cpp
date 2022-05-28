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
#include "queue"

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

void image::setGrosor(int _grosor){
    grosor=_grosor;
}

void image::SetPixel(int x, int y, BYTE red,BYTE green, BYTE blue){
    if(inBounds(x,y) && x>0 && y>0){
        if(grosor==1){
            data[x][y]={red,green,blue};//{color.rgbtBlue,color.rgbtGreen,color.rgbtRed};
        }
        else{
            for (int i = 0; i < grosor; ++i) {
                for (int j = 0; j < grosor ; ++j) {
                    if(inBounds(x+i,y+j)){
                        data[x+i][y+j]={red,green,blue};//{color.rgbtBlue,color.rgbtGreen,color.rgbtRed};
                    }
                }
            }
        }
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
    RGBTRIPLE** newData=new RGBTRIPLE*[heigth];
    for (int i = 0; i < heigth; ++i) {
        newData[i]=new RGBTRIPLE[width];
    }
    for (int i = 0; i < heigth; ++i) {
        for (int j = 0; j < width; ++j) {
            int blue=(int) data[i][j].rgbtBlue;
            int green=(int) data[i][j].rgbtGreen;
            int red=(int) data[i][j].rgbtRed;
            newData[i][j]={(BYTE) (red/3),(BYTE) (green/3),(BYTE) (blue/3)};
        }
    }
    data=newData;
}

void image::grey(){
    RGBTRIPLE** newData=new RGBTRIPLE*[heigth];
    for (int i = 0; i < heigth; ++i) {
        newData[i]=new RGBTRIPLE[width];
    }
    for (int i = 0; i < heigth; ++i) {
        for (int j = 0; j < width; ++j) {
            int blue=(int) data[i][j].rgbtBlue;
            int green=(int) data[i][j].rgbtGreen;
            int red=(int) data[i][j].rgbtRed;
            int greey=(blue+green+red)/3;
            newData[i][j]={(BYTE) greey,(BYTE) greey,(BYTE) greey};

        }
    }
    data=newData;

}

void image::negative(){
    RGBTRIPLE** newData=new RGBTRIPLE*[heigth];
    for (int i = 0; i < heigth; ++i) {
        newData[i]=new RGBTRIPLE[width];
    }
    for (int i = 0; i < heigth; ++i) {
        for (int j = 0; j < width; ++j) {
            int blue=(int) data[i][j].rgbtBlue;
            int green=(int) data[i][j].rgbtGreen;
            int red=(int) data[i][j].rgbtRed;
            newData[i][j]={(BYTE) (red-255),(BYTE) (green-255), (BYTE) (blue-255)};
        }
    }
    data=newData;
}

void image::mix(){
    RGBTRIPLE** newData=new RGBTRIPLE*[heigth];
    for (int i = 0; i < heigth; ++i) {
        newData[i]=new RGBTRIPLE[width];
    }
    for (int i = 0; i < heigth; ++i) {
        for (int j = 0; j < width; ++j) {
            int blue=(int) data[i][j].rgbtBlue;
            int green=(int) data[i][j].rgbtGreen;
            int red=(int) data[i][j].rgbtRed;
            newData[i][j]={(BYTE) blue,(BYTE) red ,(BYTE) green};
        }
    }
    data=newData;
}

RGBTRIPLE image::getPixel(int x, int y){
    return data[x][y];
}

void image::linea(float x1, float y1, float x2, float y2) {
    if(x1==x2){
        for(int j=y1;j<=y2;j++){
            int i=x1;
            SetPixel(i,j,color.rgbtRed, color.rgbtGreen, color.rgbtBlue);
        }

        for(int j=y2;j<=y1;j++){
            int i=x1;
            SetPixel(i,j,color.rgbtRed, color.rgbtGreen, color.rgbtBlue);
        }
    }
    else{
        float m=(y1-y2)/(x1-x2);
        float b=y1-x1*m;

        for (int i = x1; i <= x2 ; ++i) {
            float j=i*m+b;
            int jentero=(int) j;
            if(j-jentero!=0){
                SetPixel(i,jentero+1,color.rgbtRed, color.rgbtGreen, color.rgbtBlue);
            }
            SetPixel(i,jentero,color.rgbtRed, color.rgbtGreen, color.rgbtBlue);
        }

        for (int i = x2; i <= x1 ; ++i) {
            float j=i*m+b;
            int jentero=(int) j;
            if(j-jentero!=0){
                SetPixel(i,jentero+1,color.rgbtRed, color.rgbtGreen, color.rgbtBlue);
            }
            SetPixel(i,jentero,color.rgbtRed, color.rgbtGreen, color.rgbtBlue);
        }

        for (int j = y1; j < y2 ; ++j) {
            int i=j/m - b/m;
            SetPixel(i,j,color.rgbtRed, color.rgbtGreen, color.rgbtBlue);
        }

        for (int j = y2; j < y1 ; ++j) {
            int i=j/m - b/m;
            SetPixel(i,j,color.rgbtRed, color.rgbtGreen, color.rgbtBlue);
        }
    }
}

int image::getHeight(){
    return heigth;
}

int image::getWidth(){
    return width;
}

void image::BFSpaint(int si, int sj) {
    int row[] = {  -1,  0, 0,  1  };
    int col[] = {  0,  -1, 1,  0 };
    bool vis[width][heigth];
    int temp=grosor;
    RGBTRIPLE colorInicial=data[si][sj];
    grosor=1;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < heigth; ++j) {
            vis[i][j]= false;
        }
    }
    queue<pair<int, int> > q;
    q.push(make_pair(si, sj));
    vis[si][sj] = true;

    if(mode=="pintar"){
        SetPixel(si,sj,color.rgbtRed,color.rgbtGreen,color.rgbtBlue);
    }else{
        SetPixel(si,sj,data[si][sj].rgbtRed/6,data[si][sj].rgbtGreen/6,data[si][sj].rgbtBlue/6);
    }

    while (!q.empty()) {
        int i = q.front().first;
        int j = q.front().second;
        q.pop();

        // Go through all 8 adjacent
        for (int k = 0; k < 4; k++) {
            if (i+row[k]>=0 && j+col[k]>=0 && i+row[k]<width && j+col[k]<heigth && !vis[i+row[k]][j+col[k]]) {
                vis[i + row[k]][j + col[k]] = true;
                if(compararColor(colorInicial,data[i + row[k]][j + col[k]])){
                    if(mode=="pintar"){

                        SetPixel(i + row[k],j + col[k],color.rgbtRed,color.rgbtGreen,color.rgbtBlue);
                    }
                    else {
                        SetPixel(i + row[k],j + col[k],data[i + row[k]][j + col[k]].rgbtRed/2,data[i + row[k]][j + col[k]].rgbtGreen/2,data[i + row[k]][j + col[k]].rgbtBlue/2);
                    }
                    q.push(make_pair(i + row[k], j + col[k]));
                }
            }
        }
    }
    grosor=temp;

}

void image::rectangle(float x1, float y1, float x2, float y2) {
    RGBTRIPLE rojo ={(BYTE) 0,(BYTE) 0,(BYTE) 255};
    linea(x1,y1,x2,y1);
    linea(x2,y1,x2,y2);
    linea(x2,y2,x1,y2);
    linea(x1,y2,x1,y1);
}

void image::triangulo(float x1, float y1, float x2, float y2) {
    int xMenor;
        if(x1<x2){
            xMenor=x1;
        }else{
            xMenor=x2;
        }
        int punta=abs(x1-x2)/2;
        RGBTRIPLE rojo ={(BYTE) 0,(BYTE) 0,(BYTE) 255};
        linea(x1,y2,x2,y2);
        linea(x1,y2,punta+xMenor,y1);
        linea(x2,y2,punta+xMenor,y1);
}

void image::DisminuirGrosor() {
    if(grosor<=1){
        grosor=1;
    }
    else{
        grosor--;
    }
}

void image::AumentarGrosor() {
    grosor++;
}

void image::rombo(float x1, float y1, float x2, float y2) {
    int puntomediox=abs((x1-x2)/2);
    int puntomedioy=abs((y1-y2)/2);
    linea(x1+puntomediox,y1,x2,puntomedioy+y1);
    linea(x2,puntomedioy+y1,x1+puntomediox,y2);
    linea(x1+puntomediox,y2,x1,y1+puntomedioy);
    linea(x1,y1+puntomedioy,x1+puntomediox,y1);
}

void image::setColor(RGBTRIPLE _color){
    color=_color;
}



bool image::compararColor(RGBTRIPLE colorInical, RGBTRIPLE colorcasilla) {
    return colorInical.rgbtRed==colorcasilla.rgbtRed &&
    colorInical.rgbtGreen==colorcasilla.rgbtGreen &&
    colorInical.rgbtBlue==colorcasilla.rgbtBlue;
}

void image::SelectRectangle(float x1, float y1, float x2, float y2) {
    int xmayor,xmenor,ymenor,ymayor;
    if (x1>x2){
        xmayor=x1;
        xmenor=x2;
    }
    else{
        xmayor=x2;
        xmenor=x1;
    }
    if (y1>y2){
        ymayor=y1;
        ymenor=y2;
    }
    else{
        ymayor=y2;
        ymenor=y1;
    }
    int i=xmenor;
    int j=ymenor;
    while(i<xmayor){
        SetPixel(i,j,data[i][j].rgbtRed/6,data[i][j].rgbtGreen/6,data[i][j].rgbtBlue/6);
        j++;
        if(j>ymayor){
            j=ymenor;
            i++;
        }
    }
}
void image::ChageMode() {
    if(mode=="pintar"){
        mode="seleccionar";
    }
    else {
        mode="pintar";
    }
}
void image::setmode(string _mode){
    mode=_mode;
}




#endif //PROYECTO2DATOSII_IMAGE_CPP
