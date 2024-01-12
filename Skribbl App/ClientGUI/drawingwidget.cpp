#include "drawingwidget.h"
#include <qbytearray.h>
#include<qdatastream.h>


struct DrawingPoint {
    QString color;
    int penWidth;
    QPointF position;
    // Add more fields as needed
};

void drawingWidget::mousePressEvent(QMouseEvent* event)
{
    if (this->enable == true)
    {
        if (event->button() == Qt::LeftButton) {
            startDrawing(mapToScene(event->pos()));
        }
    }
}

void drawingWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (this->enable == true)
    {
        if (event->buttons() & Qt::LeftButton) {
            continueDrawing(mapToScene(event->pos()));
        }
    }
}

void drawingWidget::setEnable(const bool& isDrawing)
{
    enable = isDrawing;
}

void drawingWidget::setPenColor(QColor color)
{
    penColor = color;
}

void drawingWidget::setPenWidth(int width)
{
    penWidth = width;
}

//void drawingWidget::clearWidget()
//{
//    this->clearWidget();
//}

const bool drawingWidget::getEnable() const
{
    return this->enable;
}

void drawingWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (this->enable == true)
    {
        if (event->button() == Qt::LeftButton) {
            finishDrawing();
        }
    }
}

QColor drawingWidget::getPenColor()
{
    return penColor;
}

void drawingWidget::startDrawing(const QPointF& pos)
{
    if (this->enable == true)
    {
        currentLinePath = QPainterPath();
        currentLinePath.moveTo(pos); // Move to the cursor position
        currentLine = new QGraphicsPathItem;

        // Use the updated penColor here
        QPen pen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

        currentLine->setPen(pen);
        currentLine->setPath(currentLinePath);
        scene()->addItem(currentLine);
    }
}

void drawingWidget::continueDrawing(const QPointF& pos)
{
    if (this->enable == true)
    {
        currentLinePath.lineTo(pos);
        currentLine->setPath(currentLinePath);

        sendPixelToServer(pos);
        //daca se poate returna currentLinePath - sa se transmita pe sv
        //daca nu, se creeaza un vector de puncte/linii
        //ruta pt preluare in paint event - pt cei care ghicesc
        //pt cel care deseneaza - ruta de exportare a desenului
    }
}

void drawingWidget::finishDrawing()
{
    if (this->enable == true)
    {
        // Optional: Remove the last point if there are only two points
        if (currentLinePath.elementCount() == 2 && currentLinePath.elementAt(0) == currentLinePath.elementAt(1)) {
            scene()->removeItem(currentLine);
        }
        currentLine = nullptr;
    }
}

void drawingWidget::sendPixelToServer(const QPointF& pos)
{
    if (this->enable == true)
    {

        /*DrawingPoint drawingPoint;
        drawingPoint.color = penColor.name();
        drawingPoint.penWidth = penWidth;
        drawingPoint.position = pos;*/

        // Serialize to binary data using QByteArray and QDataStream
        /*QByteArray binaryData;
        QDataStream stream(&binaryData, QIODevice::WriteOnly);
        stream << drawingPoint.color << drawingPoint.penWidth << drawingPoint.position;*/


       //cand se incheie o linie, se trimite o cord(-1,1) -> usor de identificat pe ceilalti clienti



        crow::json::wvalue jsonPayload;
        jsonPayload["x"] = static_cast<double>(pos.x());;
        jsonPayload["y"] = static_cast<double>(pos.y());;
        jsonPayload["penWidth"] = penWidth;
        jsonPayload["color"] = penColor.name().toUtf8();
        std::string jsonString = jsonPayload.dump();

        auto response = cpr::Put(
            cpr::Url{ "http://localhost:18080/game/pixel" },
            cpr::Body{ jsonString},
            cpr::Header{ { "Content-Type", "application/json" } }
        );
    }
}


void drawingWidget::receivePixelFromServer(double x, double y, const QString& penColor, uint32_t penWidth)
{
    if (this->enable == false)
   
    {
            updateDrawing(x, y, penColor, penWidth);
        }
}
//void drawingWidget::receivePixelFromServer(const crow::json::rvalue& jsonPayload)
//{
//    if (this->enable == false)
//    {
//        if (jsonPayload) {
//            QString receivedPenColor = QString::fromStdString(jsonPayload["penColor"].s());
//            int receivedPenWidth = jsonPayload["penWidth"].i();
//            double receivedX = jsonPayload["x"].d();
//            double receivedY = jsonPayload["y"].d();
//
//            updateDrawing(receivedX, receivedY, receivedPenColor, receivedPenWidth);
//        }
//    }
//}
//
void drawingWidget::updateDrawing(double x, double y, const QString& penColor, uint32_t penWidth)
{

    //copiat logica ca la fereastra desenatorului
    if (this->enable == false)
    {
        QGraphicsEllipseItem* pixelItem = new QGraphicsEllipseItem(x, y, 1, 1);

        QPen pen(QColor(penColor), penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        pixelItem->setPen(pen);

        scene()->addItem(pixelItem);
    }
}
//
//void drawingWidget::updateDrawing(double x, double y, const QString& penColor, uint32_t penWidth)
//{
//    if (this->enable == false)
//    {
//        QGraphicsLineItem* receivedLine = new QGraphicsLineItem;
//
//        QPen pen(QColor(penColor), penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//        receivedLine->setPen(pen);
//
//        QLineF line(currentLine->line().p1(), QPointF(x, y));
//        receivedLine->setLine(line);
//        scene()->addItem(receivedLine);
//        currentLine = receivedLine;
//    }
//}
