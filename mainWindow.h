#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <nlohmann/json.hpp>
#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    std::vector<Jautajums> jautajumi;
};

#endif
