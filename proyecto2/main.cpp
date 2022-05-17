#include <QtWidgets>
#include <QTextStream>
#include "image.hpp"

// Make a subclass of the QWidget class, so that you can override some of its
// virtual methods

class PaintWidget : public QWidget {
    // Create a QPixmap object that you will use to store the bitmap
    // that the user will draw [on].

    QPixmap m_pixmap;
    image bitmap;
    QPoint m_lastPos;
    QColor color = Qt::black;
    QPen pen;

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
        m_lastPos = ev->pos();

        draw(ev->pos());
    }
    void keyPressEvent(QKeyEvent * ev) override {
        if(ev->key()==Qt::Key_S){
            bitmap.rotate_rigth();
            bitmap.write("/home/jose/proyecto2/copia.bmp");
            bitmap.rotate_left();
        }

        else if(ev->key()==Qt::Key_R){
            bitmap.rotate_rigth();
            cargarimagen();
        }
        else if(ev->key()==Qt::Key_C){
            bitmap.white();
            cargarimagen();
            bitmap.read("/home/jose/proyecto2/snail.bmp");
            bitmap.rotate_left();
            cargarimagen();

        }

    }
    // Override the mouseMoveEvent(QMouseEvent *) [...]
    void mouseMoveEvent(QMouseEvent * ev) override {
        draw(ev->pos());

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

    void draw(const QPoint & pos) {
        //QPainter painter{&m_pixmap};

        //painter.setRenderHint(QPainter::Antialiasing);
        //pen.setWidth(0);
        //pen.setStyle(Qt::SolidLine);
        //painter.setPen(pen);
        //painter.drawLine(m_lastPos, pos);
        RGBTRIPLE rojo={(BYTE) 255,(BYTE) 0,(BYTE) 0 };
        bitmap.linea(m_lastPos.x(),m_lastPos.y(),pos.x(),pos.y(),rojo);
        bitmap.SetPixel(m_lastPos.x(),m_lastPos.y(),(BYTE) 0, (BYTE) 0, (BYTE) 0);
        bitmap.SetPixel(pos.x(),pos.y(),(BYTE) 0, (BYTE) 0, (BYTE) 0);
        cargarimagen();
        QString text;
        text=QString("%1X%2").arg(m_lastPos.x()).arg(m_lastPos.y());
        text=QString("%1X%2").arg(pos.x()).arg(pos.y());

        m_lastPos = pos;
        update();
    }
public:
    using QWidget::QWidget;
    void init(){
        bitmap.generate(600,600);
        bitmap.white();


    }

};

int main(int argc, char ** argv) {
    // Create an object of your subclass and call show()
    QApplication app{argc, argv};
    PaintWidget ui;
    ui.init();
    ui.setFixedSize(600,600);
    ui.show();
    return app.exec();
}
