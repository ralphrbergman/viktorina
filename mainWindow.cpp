#include "mainWindow.h"
#include "ui_questionaire.h"
#include <algorithm>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->pogas = {ui->atbildesPoga1, ui->atbildesPoga2, ui->atbildesPoga3};

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

    // Ielādējam jautājumus no JSON faila.
    std::ifstream f(cels + "jautajumi.json");

    if (f.is_open()) {
        json dati = json::parse(f);

        if (
            dati.contains("jautajumi") &&
            dati["jautajumi"].is_array() &&
            dati.contains("nosaukums")
        ) {
            this->jautajumi = dati["jautajumi"].
            get<std::vector<Jautajums>>();

            this->nosaukums = dati["nosaukums"];
        }
    } else {
        qDebug() << "Neizdevās atvērt JSON failu: " + cels + "jautajumi.json\n"\
        "Pārliecinies ka tev ir tiesības viņam piekļūt "\
        "vai lai fails eksistē ar pareizu JSON sintaksi!";

        exit(1);
    }

    // Savienojam GUI pogas nospiešanu uz atbilstošām metodēm.
    connect(ui->saktPoga, &QPushButton::clicked, this, &MainWindow::saktViktorinu);
    connect(ui->atsaktPoga, &QPushButton::clicked, this, &MainWindow::saktViktorinu);

    for (QPushButton* poga : this->pogas) {
        connect(poga, &QPushButton::clicked, this, &MainWindow::pogasNospiesana);
    }

    // Savienojam punktu mainīšanās pasākumu lai nomaina redzamo punktu summu.
    connect(this, &MainWindow::punktiMainijusies, this, [this](int jaunaSumma) {
        ui->punkti->setText(QString::number(jaunaSumma) + " Punkti");
    });

    // Uzstādam viktorīnas nosaukumu.
    ui->nosaukums->setText(QString::fromStdString(this->nosaukums));
    ui->nosaukums_2->setText(QString::fromStdString(this->nosaukums));
}

void MainWindow::atnemtPunktu() {
    this->punkti -= 1;

    emit punktiMainijusies(this->punkti);
}

void MainWindow::atiestatitPunktus() {
    this->punkti = 0;

    emit punktiMainijusies(this->punkti);
}

void MainWindow::pievienotPunktu() {
    this->punkti += 1;

    emit punktiMainijusies(this->punkti);
}

void MainWindow::pogasNospiesana() {
    // Iegūstam nospiesto pogu.
    QPushButton* poga = qobject_cast<QPushButton*>(sender());

    // Punktu maiņa.
    if (poga->text().toStdString() == this->atbilde) {
        MainWindow::pievienotPunktu();
    } else if (this->punkti > 0) {
        MainWindow::atnemtPunktu();
    }

    // Jautājumu pāršķiršana/nobeigums.
    if (this->jautajumaKarta < (int)this->jautajumi.size()) {
        this->parskirtJautajumu(this->jautajumaKarta + 1);
    } else {
        this->beigtViktorinu();
    }
}

void MainWindow::parskirtJautajumu(int numurs) {
    numurs -= 1;
    if (numurs < 0 || numurs >= (int)this->jautajumi.size()) return;

    this->aktualaisJautajums = &this->jautajumi[numurs];
    this->jautajumaKarta = numurs + 1;
    Jautajums* j = this->aktualaisJautajums;
    this->atbilde = j->atbilde;

    // Nomainām etiķetes un pogas uz aktuālo informāciju.
    ui->jautajums->setText(QString::fromStdString(j->jautajums));
    ui->lapaspuse->setText(QString::fromStdString(
        std::to_string(numurs + 1) +
        "/" +
        std::to_string(this->jautajumi.size())
    ));

    ui->atbildesPoga1->setText(QString::fromStdString(j->varianti[0]));
    ui->atbildesPoga2->setText(QString::fromStdString(j->varianti[1]));
    ui->atbildesPoga3->setText(QString::fromStdString(j->varianti[2]));
}

void MainWindow::saktViktorinu() {
    ui->page_1->setCurrentIndex(1);

    MainWindow::parskirtJautajumu(1);
}

void MainWindow::beigtViktorinu() {
    ui->page_1->setCurrentIndex(2);

    ui->punkti_2->setText(QString::fromStdString(
        "Tu esi saņēmis " +
        std::to_string(this->punkti) +
        " punktus!"
    ));

    this->atiestatitPunktus();
}

MainWindow::~MainWindow() {
    delete ui;
}

