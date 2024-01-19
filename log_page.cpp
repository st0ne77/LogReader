#include "log_page.h"
#include "ui_log_page.h"

#include <QFileSystemWatcher>
#include <QScrollBar>

LogPage::LogPage(const QString &path, QWidget *parent)
    : QWidget(parent), ui(new Ui::LogPage), path_(path) {
    ui->setupUi(this);
    ui->label_file_name->setText(path_);

    ReadAll();

    QFileSystemWatcher *watcher = new QFileSystemWatcher(this);
    watcher->addPath(path);

    connect(watcher, &QFileSystemWatcher::fileChanged, this, [this](){
        ReadAll();
    });
}

LogPage::~LogPage() {}

void LogPage::ReadAll() {
    QFile file(path_);
    if (!file.open(QIODevice::ReadOnly)) {
        // TODO
        return;
    }
    file.seek(pos_);

    QScrollBar* scrollbar = ui->plainTextEdit->verticalScrollBar();
    int max = scrollbar->maximum();
    bool is_bottom = scrollbar->value() == max;
    int scroll_pos = scrollbar->value();
    if (!is_bottom)
        ui->plainTextEdit->setUpdatesEnabled(false);
    while (!file.atEnd()) {
        QString str = file.readLine();
        if (str.endsWith("\r\n")) {
            str = str.left(str.size() - 2);
        }
        ui->plainTextEdit->appendPlainText(str);
    }
    pos_ = file.pos();

    if (!is_bottom) {
        scrollbar->setValue(scroll_pos);
        ui->plainTextEdit->setUpdatesEnabled(true);
    } else {
        scrollbar->setValue(scrollbar->maximum());
    }
}