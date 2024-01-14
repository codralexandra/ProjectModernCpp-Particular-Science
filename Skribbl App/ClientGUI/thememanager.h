#pragma once

#include <QObject>
#include "qapplication.h"

class ThemeManager : public QObject
{
    Q_OBJECT

public:
    static ThemeManager& instance();
    QString getCurrentStyleSheet() const;

signals:
    void themeChanged(const QString& styleSheet);

public slots:
    void setDarkTheme();
    void setLightTheme();
    void setBaseTheme();
private:
    QString currentStyleSheet="background: qlineargradient(spread:pad, x1:0, y1:0, x2:0.75, y2:0.79, stop:0 rgba(255, 190, 230, 255), stop:1 rgba(220, 217, 255, 255), x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 231, 251, 255), stop:1 rgba(210, 230, 255, 255));";
};

