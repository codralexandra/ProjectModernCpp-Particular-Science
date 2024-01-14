#include "drawingwidget.h"
#include <qbytearray.h>
#include<qdatastream.h>
#include<thread>
#include <QBrush> 
#include <QColor>
#include <QGraphicsEllipseItem>

//drawingWidget::drawingWidget(QWidget* parent)
//{
//    connect(this, &drawingWidget::updateDrawingInstant, this, &drawingWidget::onUpdateDrawingInstant);
//}



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
        if (currentLine)
        {
            currentLinePath.lineTo(pos);
            currentLine->setPath(currentLinePath);

            std::thread waitingThread([this, pos] {
                sendPixelToServer(pos);
                });
            waitingThread.detach();
        }
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        newLine = !newLine;
    }
}
void drawingWidget::clearWidget()
{
    if (scene()) {
        scene()->clear();
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
        //  jsonPayload["color"] = penColor.name().toUtf8();
        jsonPayload["newLine"] = newLine;
        std::string jsonString = jsonPayload.dump();

        auto response = cpr::Put(
            cpr::Url{ "http://localhost:18080/game/pixel" },
            cpr::Body{ jsonString},
            cpr::Header{ { "Content-Type", "application/json" } }
        );
    }
}


void drawingWidget::receivePixelFromServer(double x, double y, const QString& penColor1, uint32_t penWidthbool, bool newLine1)
{
    if (this->enable == false)

    {
        updateDrawing(x, y, penColor1, penWidth, newLine1);
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
void drawingWidget::updateDrawing(double x, double y, const QString& penColor1, uint32_t penWidth, bool newLine1)
{

    //copiat logica ca la fereastra desenatorului
    if (this->enable == false)
    {
        //double ellipseWidth = 3.0;  // Example width
        //double ellipseHeight = 3.0; // Example height

        //// Create a QGraphicsEllipseItem with specified dimensions
        //QGraphicsEllipseItem* pixelItem = new QGraphicsEllipseItem(x - ellipseWidth / 2, y - ellipseHeight / 2, ellipseWidth, ellipseHeight);

        //// Create a pen for the outline
        //QPen pen(QColor(penColor1), penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        //pixelItem->setPen(pen);

        //// Create a brush for the fill color
        //QColor color(penColor1);
        //QBrush brush(color);
        //pixelItem->setBrush(brush);

        //// Add the ellipse item to the scene
        //scene()->addItem(pixelItem);
        if (newLine1 == newLineForDrawing && !lastPixel.color.isEmpty())
        {
            QColor color(penColor1);
            QPen pen(color, penWidth);
            QBrush brush(color);
            QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF(QPointF(lastPixel.x, lastPixel.y), QPointF(x, y)));
            lineItem->setPen(pen);
            scene()->addItem(lineItem);
            lastPixel.color = penColor1;
            lastPixel.penWidth = penWidth;
            lastPixel.x = x;
            lastPixel.y = y;
        }
        else
        {
            newLineForDrawing = newLine1;
            lastPixel.color = penColor1;
            lastPixel.penWidth = penWidth;
            lastPixel.x = x;
            lastPixel.y = y;
        }
        /*QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem(x, y, 3, 3);
        QColor color(penColor1);
        QPen pen(color, penWidth);
        QBrush brush(color);
        ellipseItem->setPen(pen);
        ellipseItem->setBrush(brush);
        scene()->addItem(ellipseItem);*/
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
