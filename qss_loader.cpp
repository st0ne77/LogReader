#include "qss_loader.h"

#include <QFile>
#include <QWidget>


bool QssLoader::Load(QWidget *widget, const QString &qss_file) {
    if (!widget)
        return false;

    QFile qss(qss_file);
    if (!qss.open(QFile::ReadOnly)) {
        return false;
    }

    QString origin_content = QString::fromUtf8(qss.readAll());
    qss.close();
    widget->setStyleSheet(origin_content);
    return true;
}
