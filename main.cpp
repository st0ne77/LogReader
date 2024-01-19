#include "window.h"

#include <QApplication>

int main(int argc, char** argv){
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);
    LogWindow window;
    window.show();
    return app.exec();
}
