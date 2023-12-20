#include "drawingwidget.h"

void drawingWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        startDrawing(mapToScene(event->pos()));
    }
}

void drawingWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        continueDrawing(mapToScene(event->pos()));
    }
}

void drawingWidget::setPenColor(QColor color)
{
    penColor = color;
}

void drawingWidget::setPenWidth(int width)
{
    penWidth = width;
}

void drawingWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        finishDrawing();
    }
}

QColor drawingWidget::getPenColor()
{
    return penColor;
}

void drawingWidget::startDrawing(const QPointF& pos)
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

void drawingWidget::continueDrawing(const QPointF& pos)
{
    currentLinePath.lineTo(pos);
    currentLine->setPath(currentLinePath);

    sendPixelToServer(pos);
}

void drawingWidget::finishDrawing()
{
    // Optional: Remove the last point if there are only two points
    if (currentLinePath.elementCount() == 2 && currentLinePath.elementAt(0) == currentLinePath.elementAt(1)) {
        scene()->removeItem(currentLine);
    }
    currentLine = nullptr;
}

void drawingWidget::sendPixelToServer(const QPointF& pos)
{
    crow::json::wvalue jsonPayload;
    jsonPayload["penColor"] = penColor.name().toStdString();
    jsonPayload["penWidth"] = penWidth;
    jsonPayload["x"] = pos.x();
    jsonPayload["y"] = pos.y();
    std::string jsonString = jsonPayload.dump();

    auto response = cpr::Put(
        cpr::Url{ "http://localhost:18080/game/sendpixel" },
        cpr::Body{ jsonString },
        cpr::Header{ { "Content-Type", "application/json" } }
    );
}
