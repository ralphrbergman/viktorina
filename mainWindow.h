#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <array>
#include <nlohmann/json.hpp>
#include <QMainWindow>
#include <QPushButton>

struct Jautajums {
    std::string jautajums;
    std::string atbilde;
    std::vector<std::string> varianti;
};

inline void from_json(const nlohmann::json& j, Jautajums& jj) {
    j.at("jautajums").get_to(jj.jautajums);
    j.at("atbilde").get_to(jj.atbilde);
    j.at("varianti").get_to(jj.varianti);
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int punkti = 0;
    std::string nosaukums;

    void atnemtPunktu();
    void atiestatitPunktus();
    void pievienotPunktu();

private:
    Ui::MainWindow *ui;

    std::vector<Jautajums> jautajumi;

    Jautajums* aktualaisJautajums = nullptr;
    int jautajumaKarta = 0;
    std::string atbilde;
    std::array<QPushButton*, 3> pogas;

private slots:
    void pogasNospiesana();
    void parskirtJautajumu(int numurs);
    void saktViktorinu();
    void beigtViktorinu();

signals:
    void punktiMainijusies(int jaunaSumma);
};

#endif
