#pragma once
#include <QWidget>
#include <memory>

namespace Ui {
class LogPage;
} // namespace Ui

class LogPage : public QWidget {
public:
    explicit LogPage(const QString &path, QWidget *parent = nullptr);
    ~LogPage() override;

private:
    void ReadAll();

    std::unique_ptr<Ui::LogPage> ui;

    QString path_;
    qint64 pos_ = 0;
};