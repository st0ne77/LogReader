#pragma once
#include <QMainWindow>
#include <memory>
#include <QSettings>

namespace Ui {
class LogWindow;
} // namespace Ui

class QStandardItemModel;

class LogWindow : public QMainWindow {
    Q_OBJECT
public:
    LogWindow();
    ~LogWindow() override;

private slots:
    void on_pushButton_add_file_clicked();

    void on_pushButton_roll_log_clicked();

    void on_pushButton_close_clicked();
private:
    void AddFile(const QString &file, const QString &fmt = "");

    std::unique_ptr<Ui::LogWindow> ui;

    QStandardItemModel *model_ = nullptr;

    QSettings file_settings_;
};