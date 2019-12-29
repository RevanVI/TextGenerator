#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFileButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Открыть файл"),
                                                QApplication::applicationDirPath(),
                                                "Текстовый файл (*.txt)");
    if (!path.isEmpty())
    {
        QLineEdit* pathText = QObject::findChild<QLineEdit*>("filePathText");
        pathText->setText(path);
        curFile.setPath(path);
    }
}

void MainWindow::on_generateButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Сохранить файл"),
                                                QApplication::applicationDirPath(),
                                                "Текстовый файл (*.txt)");
    if (!path.isEmpty())
    {
        //Построение хэш-таблицы по входному файлу
        QFile file(curFile.path());
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QMessageBox* error = new QMessageBox(QMessageBox::Critical, tr("Ошибка"),
                                                 "Входной файл не может быть открыт",
                                                 QMessageBox::Ok);
            error->exec();
            return;
        }
        QTextStream* stream = new QTextStream(&file);
        stream->seek(0);

        Hash hash;
        Prefix prefix;
        int prefLen = QObject::findChild<QSpinBox*>("prefLenSBox")->text().toInt();
        int textLen = QObject::findChild<QSpinBox*>("textLenSBox")->text().toInt();
        for (int i = 0; i < prefLen; ++i)
            add(hash, prefix, stopWord, prefLen);
        buildHash(hash, prefix, *stream, prefLen);
        add(hash, prefix, stopWord, prefLen);
        delete stream;
        file.close();

        //Генерация нового текста
        file.setFileName(path);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
        {
            QMessageBox* error = new QMessageBox(QMessageBox::Critical, tr("Ошибка"),
                                                 "Выходной файл не может быть создан",
                                                 QMessageBox::Ok);
            error->exec();
            return;
        }
        stream = new QTextStream(&file);
        generate(hash, *stream, textLen, prefLen, stopWord);
        QMessageBox* error = new QMessageBox(QMessageBox::Information, tr("Отчет"),
                                             "Текст сгенерирован успешно.",
                                             QMessageBox::Ok);
        error->exec();
    }
}
