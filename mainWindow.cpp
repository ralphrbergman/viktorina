#include "mainWindow.h"
#include "ui_questionaire.h"
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::string cels = QCoreApplication::applicationDirPath().toStdString() + "/";
    std::string faila_nosaukums;

    // Ielādējam tematisko attēlu no diska un parādam to.
    // Izvēloties starp PNG un JPEG attēliem.
    if (std::filesystem::exists(cels + "attels.png")) {
        faila_nosaukums = cels + "attels.png";
    }
    else if (std::filesystem::exists(cels + "attels.jpg")) {
        faila_nosaukums = cels + "attels.jpg";
    }
    else if (std::filesystem::exists(cels + "attels.jpeg")) {
        faila_nosaukums = cels + "attels.jpeg";
    }
    else {
        // Ir pieņemami ka lietotne nenosprāgst dēļ neeksistējoša attēla tapēc vienkārši paziņojam.
        qDebug() << "Tematiskais attēls nav atrodams, ignorējam.";
    }

    if (!faila_nosaukums.empty()) {
        QPixmap attels = QPixmap(QString::fromStdString(faila_nosaukums)).scaled(
            ui->attels->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        );

        if (!attels.isNull()) {
            ui->attels->setPixmap(attels);
            ui->attels_2->setPixmap(attels);
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

