#include "log_name_dialog.h"
#include "ui_log_name_dialog.h"

#include <QDateTime>
#include <QFileDialog>
#include <QStandardPaths>

LogNameDialog::LogNameDialog(QWidget *parent) : QDialog(parent), ui(new Ui::LogNameDialog) {
    ui->setupUi(this);
}

LogNameDialog::~LogNameDialog() {}

QString LogNameDialog::dir() {
    return ui->lineEdit_dir->text();
}

QString LogNameDialog::name_format() {
    QString fmt = ui->lineEdit_name_format->text();
    if (fmt.isEmpty()) {
        fmt = ui->lineEdit_name_format->placeholderText();
    }
    return fmt;
}

QString LogNameDialog::date_format() {
    QString fmt = ui->lineEdit_date_format->text();
    if (fmt.isEmpty()) {
        fmt = ui->lineEdit_date_format->placeholderText();
    }
    return fmt;
}

QString LogNameDialog::FormatFileName(const QString &dir, const QString & name_fmt, const QString &date_fmt) {
    QString file_name = name_fmt.arg(QDateTime::currentDateTime().toString(date_fmt));
    return dir + "/" + file_name;
}

void LogNameDialog::on_pushButton_select_dir_clicked() {
    QString local = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/..";
    QString dir = QFileDialog::getExistingDirectory(this, tr("选择日志目录"), local);
    if (dir.isEmpty()) {
        return;
    }
    ui->lineEdit_dir->setText(dir);
}

void LogNameDialog::on_pushButton_ok_clicked() {
    QString d = dir();
    if (d.isEmpty()) {
        ui->label_error->setText(tr("日志目录不能为空"));
        return;
    }

    QString nfmt = name_format();
    QString dfmt = date_format();

    file_ = FormatFileName(d, nfmt, dfmt);

    accept();
}