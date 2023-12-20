#include "watchwidget.h"

watchWidget::~watchWidget()
{}

void watchWidget::receivePixelFromServer(const crow::json::rvalue& jsonPayload)
{
    if (jsonPayload) {
        QString receivedPenColor = QString::fromStdString(jsonPayload["penColor"].s());
        int receivedPenWidth = jsonPayload["penWidth"].i();
        double receivedX = jsonPayload["x"].d();
        double receivedY = jsonPayload["y"].d();

        updateDrawing(receivedX, receivedY, receivedPenColor, receivedPenWidth);
    }
}

void watchWidget::updateDrawing(double x, double y, const QString& penColor, uint32_t penWidth)
{
    QGraphicsLineItem* receivedLine = new QGraphicsLineItem;

    QPen pen(QColor(penColor), penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    receivedLine->setPen(pen);

    QLineF line(currentLine->line().p1(), QPointF(x, y));
    receivedLine->setLine(line);
    scene()->addItem(receivedLine);
    currentLine = receivedLine;
}
