#pragma once
#include <QDialog>
#include <memory>

namespace Ui {
class LogNameDialog;
} // namespace Ui

class LogNameDialog : public QDialog {
    Q_OBJECT
public:
    explicit LogNameDialog(QWidget *parent = nullptr);
    ~LogNameDialog();

    QString dir();
    QString name_format();
    QString date_format();
    static QString FormatFileName(const QString &dir, const QString & name_fmt, const QString &date_fmt);

    QString file() {return file_;}
private slots:
    void on_pushButton_select_dir_clicked();

    void on_pushButton_ok_clicked();
private:
    std::unique_ptr<Ui::LogNameDialog> ui;

    QString file_;
};