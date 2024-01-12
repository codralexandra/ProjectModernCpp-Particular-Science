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
    QString currentStyleSheet;
};

