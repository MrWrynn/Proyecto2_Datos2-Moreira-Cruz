#include <QtWidgets>
#include <QTextStream>
#include <QInputDialog>
#include "mainwindow.h"
#include "image.hpp"
#include "widget.h"
#include <iostream>
#include <string>
#include <string_view>
#include <QMessageBox>
using namespace std;



// Make a subclass of the QWidget class, so that you can override some of its
// virtual methods
class PaintWidget : public QWidget {
    // Create a QPixmap object that you will use to store the bitmap
    // that the user will draw [on].
    //MainWindow window;
    MainWindow ventana;
    QPixmap m_pixmap;
    image bitmap;
    QPoint m_lastPos;
    RGBTRIPLE color=ventana.color;
    RGBTRIPLE lastColor={(BYTE) 0,(BYTE) 0,(BYTE) 0};
    RGBTRIPLE white={(BYTE) 255,(BYTE) 255,(BYTE) 255};
    QString esFigura;
    QString esFiltro;
    QString mensaje;
    string nombre;
    string nombreV2;
    QString col=ventana.col;
    string tipo;
    string modo;
    int width;
    int height;
    bool firstPos = true;
    bool secondPos = false;
    bool figura=false;
    bool filtro=false;
    bool texto=false;
    int x1;
    int y1;
    int x2;
    int y2;


    // Override the paintEvent(QPaintEvent *) [...]
    void paintEvent(QPaintEvent *) override {
        QPainter painter{this};
        painter.drawPixmap(0, 0, m_pixmap);
    }

    void resizeEvent(QResizeEvent *) override {
        // [...] size the QPixmap to be at least as big as the maximum size of the window
        // We'll also never let it shrink so as not to lose the already drawn image.
        auto newRect = m_pixmap.rect().united(rect());
        if (newRect == m_pixmap.rect()) return;
        QPixmap newPixmap{newRect.size()};
        QPainter painter{&newPixmap};
        painter.fillRect(newPixmap.rect(), Qt::white);
        painter.drawPixmap(0, 0, m_pixmap);
        m_pixmap = newPixmap;

    }

    // Override the mousePressEvent(QMouseEvent *) [...]
    void mousePressEvent(QMouseEvent * ev) override {
        esFigura=ventana.esFigura;
        figura=ventana.figura;
        m_lastPos = ev->pos();
        updateWidget();
        guardar();
        drawNoPos();
        if (ev->button()==Qt::LeftButton&&!figura){
            draw(ev->pos());
        }
        else{
            if(ev->button()==Qt::LeftButton&&firstPos){
                x1=ev->pos().x();
                y1=ev->pos().y();
                firstPos=false;
                secondPos=true;
            } else if(ev->button()==Qt::LeftButton&&secondPos){
                x2=ev->pos().x();
                y2=ev->pos().y();
                firstPos=true;
                secondPos=false;
                figura=false;
                if(esFigura=="triangulo"){
                    bitmap.triangulo(x1,y1,x2,y2);
                    updateDrawing();
                }
                else if(esFigura=="rombo"){
                    bitmap.rombo(x1,y1,x2,y2);
                    updateDrawing();
                }
                else if(esFigura=="rectangulo"){
                    bitmap.rectangle(x1,y1,x2,y2);
                    updateDrawing();
                }
                else if(esFigura=="linea"){
                    bitmap.linea(x1,y1,x2,y2);
                    updateDrawing();
                }
                else if(esFigura=="seleccion"){
                    bitmap.SelectRectangle(x1,y1,x2,y2);
                    updateDrawing();
                }
                else if(esFigura=="pintar"){
                    modo=ventana.modo;
                    if(modo=="pintar"){
                        bitmap.setmode("pintar");
                    }
                    else{
                        bitmap.setmode("seleccionar");
                    }
                    bitmap.BFSpaint(x1,y1);
                    updateDrawing();
                }
                else if(esFigura=="picker"){
                    RGBTRIPLE pixel=bitmap.getPixel(x1,y1);
                    int rojo=pixel.rgbtRed;
                    int verde=pixel.rgbtGreen;
                    int azul=pixel.rgbtBlue;
                    string rojoSTR=to_string(rojo);
                    string verdeSTR=to_string(verde);
                    string azulSTR=to_string(azul);
                    QString rojoQ= QString::fromStdString(rojoSTR);
                    QString verdeQ= QString::fromStdString(verdeSTR);
                    QString azulQ= QString::fromStdString(azulSTR);
                    QMessageBox::warning(this,"Color","Rojo: "+rojoQ+" Verde: "+verdeQ+" Azul: "+azulQ);
                    updateDrawing();
                }

            }


        }        
    }

    void keyPressEvent(QKeyEvent * ev) override {
        //"\n";
        if(ev->key()==Qt::Key_S){
            bitmap.rotate_rigth();
            bitmap.write("/home/jose/proyecto2/copia.bmp");
            bitmap.rotate_left();
        }
        else if(ev->key()==Qt::Key_R){
            bitmap.rotate_right;
            bitmap.write("/home/jose/proyecto2/copia.bmp");
            
        }
        else if(ev->key()==Qt::Key_L){
            bitmap.rotate_left();
            bitmap.write("/home/jose/proyecto2/copia.bmp");
        }
        else if(ev->key()==Qt::Key_Up){
            bitmap.AumentarGrosor();
        }
        else if(ev->key()==Qt::Key_Down){
            bitmap.DisminuirGrosor();
        }


    }
    // Override the mouseMoveEvent(QMouseEvent *) [...]
    void mouseMoveEvent(QMouseEvent * ev) override {
        if(!figura){
            draw(ev->pos());
        }
    }
    void cargarimagen(){
        QPainter painter{&m_pixmap};        
        for(int i=0;i<bitmap.getWidth();i++){
            for(int j=0;j<bitmap.getHeight();j++){
                RGBTRIPLE pixel=bitmap.getPixel(i,j);
                painter.fillRect(i,j,1,1,QColor((int) pixel.rgbtRed,(int) pixel.rgbtGreen,(int) pixel.rgbtBlue));
            }
        }
    }
    void drawNoPos(){
        filtro=ventana.filtro;
        esFiltro=ventana.esFiltro;
        if(filtro){
            if(esFiltro=="negativo"){
                bitmap.negative();
                ventana.filtro=false;
            }
            else if(esFiltro=="gris"){
                bitmap.grey();
                ventana.filtro=false;
                }
            else if(esFiltro=="oscuro"){
                bitmap.dark();
                ventana.filtro=false;
            }
            else if(esFiltro=="mix"){
                bitmap.mix();
                ventana.filtro=false;
            }
        }
        else{
            filtro=ventana.filtro;
        }
        cargarimagen();
        update();
    }
    void draw(const QPoint & pos) {
        bitmap.linea(m_lastPos.x(),m_lastPos.y(),pos.x(),pos.y());
        cargarimagen();
        QString text;
        m_lastPos = pos;
        update();
    }
    void guardar(){
        texto=ventana.texto;
        tipo=ventana.tipo;
        if(texto){
            if(tipo=="guardar"){
                nombre=ventana.nombre.toStdString();
                bitmap.rotate_rigth();
                string parteA="/home/jose/proyecto2/";
                parteA+=nombre;
                parteA+=".bmp";
                const char *name = parteA.c_str();
                bitmap.write(name);
                bitmap.rotate_left();
                ventana.texto=false;
            }
            else{
                nombre=ventana.nombre.toStdString();
                string parteA="/home/jose/proyecto2/";
                parteA+=nombre;
                parteA+=".bmp";
                const char *name = parteA.c_str();
                bitmap.white();
                cargarimagen();
                bitmap.read(name);
                bitmap.rotate_left();
                cargarimagen();
                ventana.texto=false;
            }

        }
        else{
            ventana.texto=false;
        }

    }
public:
    using QWidget::QWidget;

    int setWidth(){
        width=QInputDialog::getInt(this,"Inicio","Digite el valor del ancho: ");
        return width;
    }
    int setHeight(){
        height=QInputDialog::getInt(this,"Inicio","Digite el valor de la altura: ");
        return height;
    }
    void init(){
        ventana.show();
        bitmap.generate(width,height);
        bitmap.white();
    }
    void updateDrawing(){
        figura=false;
        cargarimagen();
        update();
    }
    void updateWidget(){
        col=ventana.col;
        if(col=="blanco"){
            bitmap.setColor(white);
        }
        else{
            bitmap.setColor(ventana.color);
        }

    }

};

int main(int argc, char ** argv) {
    // Create an object of your subclass and call show()    
    QApplication app{argc, argv};
    PaintWidget ui;
    MainWindow ventana;
    widget inicio;
    ui.setFixedSize(ui.setWidth(),ui.setHeight());
    ui.init();
    ui.show();
    return app.exec();
}
