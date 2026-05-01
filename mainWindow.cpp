#include "mainWindow.h"
#include "ui_questionaire.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

