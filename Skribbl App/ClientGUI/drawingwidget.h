#pragma once

#include <QWidget>
#include "ui_drawingwidget.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QPen>
#include <cpr/cpr.h>
#include <crow.h>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include<chrono>

class drawingWidget : public QGraphicsView
{
	struct DrawingPoint {
		QString color;
		int penWidth;
		double x;
		double y;
		// Add more fields as needed
	};
	Q_OBJECT

public:
	//save every pixel coord for sending it to the server to other players graphicsview
	drawingWidget(QWidget* parent = nullptr)
		: QGraphicsView(parent), currentLine(nullptr), penColor(Qt::black), penWidth(5)
	{
		setRenderHint(QPainter::Antialiasing, true);
		setRenderHint(QPainter::SmoothPixmapTransform, true);
		setRenderHint(QPainter::TextAntialiasing, true);

		setScene(new QGraphicsScene(this));

		// Set a fixed scene rectangle to limit the visible area
		setSceneRect(QRectF(0, 0, 1000, 1000)); // Replace with your desired fixed width and height

		// Disable scroll bars
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

		// Ensure the view does not scale
		setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
		setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
	}

	void setEnable(const bool& isDrawing);
	void setPenColor(QColor color);
	void setPenWidth(int width);
	//void clearWidget();

	const bool getEnable() const;

	QColor getPenColor();

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

	void startDrawing(const QPointF& pos);
	void continueDrawing(const QPointF& pos);
	void finishDrawing();

public:
	void sendPixelToServer(const QPointF& pos);
	void receivePixelFromServer(double x, double y, const QString& penColor1, uint32_t penWidth,bool newLine1);
    void updateDrawing(double x, double y, const QString& penColor1, uint32_t penWidth, bool newLine1);


private:
	QGraphicsPathItem* currentLine;
	QPainterPath currentLinePath;
	QColor penColor;
	int penWidth;
	bool enable;
	bool newLine;
	bool newLineForDrawing;
	DrawingPoint lastPixel;
	//enable= true -> desenator
	//enable= false -> watcher
};
