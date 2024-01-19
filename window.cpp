#include "window.h"
#include "ui_window.h"

#include "log_item_delegate.h"
#include "qss_loader.h"
#include "log_page.h"
#include "log_name_dialog.h"

#include <QStandardItemModel>
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QFileInfo>

enum {
    kPageRole = Qt::UserRole + 1,
    kFormatRole,
};

LogWindow::LogWindow() : ui(new Ui::LogWindow), file_settings_("LogReader") {
    ui->setupUi(this);

    setAttribute(Qt::WA_StyledBackground, true);

    QssLoader::Load(this, ":/qss/window.css");

    ui->listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    model_ = new QStandardItemModel(ui->listView);
    ui->listView->setModel(model_);
    ui->listView->setItemDelegate(new LogItemDelegate(ui->listView));
    ui->listView->setSelectionMode(QListView::SingleSelection);
    QItemSelectionModel *selection_model = ui->listView->selectionModel();
    connect(selection_model, &QItemSelectionModel::currentChanged, this, [this](const QModelIndex &current, const QModelIndex &){
        ui->stackedWidget->setCurrentIndex(current.data(kPageRole).toInt());
    });


    QStringList files = file_settings_.value("File").toStringList();
    for (const QString& file : files) {
        if (file.indexOf("::") == -1) {
            AddFile(file);
        } else {
            QStringList args = file.split("::", QString::SkipEmptyParts);
            if (args.size() == 3) {
                AddFile(LogNameDialog::FormatFileName(args[0], args[1], args[2]), file);
            }
        }
    }
}

LogWindow::~LogWindow() {
    QStringList lst;
    for (int row = 0; row < model_->rowCount(); ++row) {
        QStandardItem *item = model_->item(row);
        QString content = item->data(kFormatRole).toString();
        if (content.isEmpty()) {
            content = item->text();
        }
        if (!content.isEmpty()) {
            lst.append(content);
        }
    }
    file_settings_.setValue("File", lst);
}

void LogWindow::on_pushButton_add_file_clicked() {
    QString local = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/..";
    QString file = QFileDialog::getOpenFileName(this, tr("选择日志文件"), local);
    if (file.isEmpty()) {
        return;
    }

    AddFile(file);
}

void LogWindow::on_pushButton_roll_log_clicked() {
    LogNameDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString dir = dialog.dir();
        QString name_fmt = dialog.name_format();
        QString date_fmt = dialog.date_format();
        AddFile(dialog.file(), QString("%1::%2::%3").arg(dir, name_fmt, date_fmt));
    }
}

void LogWindow::on_pushButton_close_clicked() {
    int row = ui->listView->currentIndex().row();
    model_->removeRow(row);
    --row;
    if (model_->rowCount() > 0 && row < 0) {
        row = 0;
    }
    ui->listView->setCurrentIndex(model_->index(row, 0));
}

void LogWindow::AddFile(const QString &file, const QString &fmt) {
    LogPage *page = new LogPage(file);

    int index = ui->stackedWidget->addWidget(page);
    ui->stackedWidget->setCurrentWidget(page);

    QStandardItem *item = new QStandardItem();
    item->setText(QFileInfo(file).fileName());
    item->setSelectable(true);
    item->setEditable(false);
    item->setData(index, kPageRole);
    item->setData(fmt, kFormatRole);
    model_->appendRow(item);

    ui->listView->clearSelection();
    ui->listView->setCurrentIndex(model_->indexFromItem(item));
}