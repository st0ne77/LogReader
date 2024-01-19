#pragma once
#include <QDebug>
#include <QUuid>
#include <QWidget>

class QWidget;
class QString;

class QssLoader {
public:
    static bool Load(QWidget *widget, const QString &qss_file);
};