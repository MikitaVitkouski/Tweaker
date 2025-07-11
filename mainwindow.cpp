#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QProcess>
#include <QPixmap>
#include <QMessageBox>
#include <QToolTip>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString basePath = QCoreApplication::applicationDirPath();

    QFile fileStyle(basePath + QDir::separator() + "style.css");
    if (fileStyle.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&fileStyle);
        QString styleSheet = stream.readAll();
        this->setStyleSheet(styleSheet);
        fileStyle.close();
    }

    // logos
    QString imagePath = basePath + QDir::separator() + "icons" + QDir::separator() + "resources" + QDir::separator() + "gear.png";
    QPixmap pixmap(imagePath);
    ui->logoGear->setPixmap(pixmap);
    ui->logoGear->setScaledContents(true);

    // RAM representation
    memoryUsagePercent = 0;
    constexpr double RAM_UPDATE_INTERVAL_MS = 1000;

    ramTimer = new QTimer(this);
    connect(ramTimer, &QTimer::timeout, this, &MainWindow::updateMemoryUsage);
    ramTimer->start(RAM_UPDATE_INTERVAL_MS);
    ramLabel = new RamLabel(this);
    ramLabel->setGeometry(510, 70, 150, 100);
    ramLabel->show();

    // buttons
    connect(ui->btnEasyMode, &QPushButton::clicked, this, &MainWindow::onbtnEasyModeClicked);
    connect(ui->btnMediumMode, &QPushButton::clicked, this, &MainWindow::onbtnMediumModeClicked);
    connect(ui->btnHardMode, &QPushButton::clicked, this, &MainWindow::onbtnHardModeClicked);
    connect(ui->btnExpertMode, &QPushButton::clicked, this, &MainWindow::onbtnExpertModeClicked);
    connect(ui->btnCleanPC, &QPushButton::clicked, this, &MainWindow::onbtnCleanPCClicked);

    // tool tips for buttons
    ui->btnEasyMode->setToolTip("- Printing, taxing, remote regitsry, touch keyboard, Xbox-related services\n"
                                "- Improves JPEG import quality\n"
                                "- Geolocation, BITS, Distributed Link Tracking, Program Compatibility Assistant, etc.\n"
                                "- Game DVR");
    ui->btnMediumMode->setToolTip("Includes everything from easy tweaking mode\n"
                                  "- Windows Defender\n"
                                  "- User Account Control (UAC)\n"
                                  "- Windows Firewall\n"
                                  "- Sleep, hibernate\n"
                                  "- Power scheme is set to Maximum performance\n"
                                  "- Windows Update (including auto updates)\n"
                                  "- Windows Search\n"
                                  "- More services (Hyper-V)");
    ui->btnHardMode->setToolTip("Includes everything from medium tweaking mode\n"
                                "- Adjust for best performance (rectangle and antialiasing fonts are on)\n"
                                "- Disable virtual memory\n"
                                "- More services (Windows Modules Installer)");
    ui->btnExpertMode->setToolTip("Includes everything from hard tweaking mode\n"
                                  "- Indexing of disks\n"
                                  "- Cortana");
    ui->btnCleanPC->setToolTip("Cleans Temp, NVIDIA NV_Cache and NVIDIA Shader Cache");

    // label about with hyperlink to repository
    ui->labelAbout->setAlignment(Qt::AlignCenter);
    ui->labelAbout->setText(R"(
    <a href="https://github.com/MikitaVitkouski/Tweaker/blob/master/README.md" style="font-size: 15px;
    color: blue;
    background: transparent;
    border: none;">
        About
    </a>
)");
    ui->labelAbout->setTextFormat(Qt::RichText);
    ui->labelAbout->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->labelAbout->setOpenExternalLinks(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void applyRegistryFile(const QString& regFilePath) {
    QProcess process;
    QString command {"regedit"};
    QStringList arguments{};
    arguments << "/s" << regFilePath;

    bool success = process.startDetached(command, arguments);
    if (!success) {
        qWarning("Cannot load regedit!");
    }
}

void applyBatFile(const QString& batFilePath) {
    QProcess process;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    // don't show cmd window
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.setProcessEnvironment(env);
    process.setCreateProcessArgumentsModifier([](QProcess::CreateProcessArguments *args) {
        args->flags |= CREATE_NO_WINDOW;
    });

    process.start(batFilePath);
    if (!process.waitForStarted()) {
        qWarning("Cannot start cleaning script!");
        return;
    }

    process.waitForFinished();
}

bool confirmRisk() {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Warning!");
    msgBox.setText("You are about to apply changes to the registry.\n"
                   "This may lead to unpredictable consequences.\n"
                   "Proceed at your own risk!\n\n"
                   "Do you want to continue?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret {msgBox.exec()};
    return ret == QMessageBox::Yes;
}

void promptRestart() {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Restart required");
    msgBox.setText("Some changes require a system restart to apply changes.\n\nRestart now?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret {msgBox.exec()};
    if (ret == QMessageBox::Yes) {
        QProcess::startDetached("shutdown", QStringList() << "/r" << "/t" << "0");
    }
}

void applyModeRegFile(const QString& fileName) {
    if(!confirmRisk()) return;

    QString regPath = QCoreApplication::applicationDirPath() + QDir::separator() + fileName;
    applyRegistryFile(regPath);

    promptRestart();
}

void applyCMDFile(const QString& fileName) {
    QString batPath = QCoreApplication::applicationDirPath() + QDir::separator() + fileName;
    applyBatFile(batPath);
}

void MainWindow::onbtnEasyModeClicked() {
    applyModeRegFile("easy.reg");
}

void MainWindow::onbtnMediumModeClicked() {
    applyModeRegFile("medium.reg");
}

void MainWindow::onbtnHardModeClicked() {
    applyModeRegFile("hard.reg");
}

void MainWindow::onbtnExpertModeClicked() {
    applyModeRegFile("expert.reg");
}

void MainWindow::onbtnCleanPCClicked() {
    applyCMDFile("cleaning.bat");
}

void MainWindow::updateMemoryUsage() {
    MEMORYSTATUSEX statex; // struct MEMORYSTATUSEX includes DWORD fields: dwLength;dwMemoryLoad;ullTotalPhys;ullAvailPhys;ullTotalPageFile;
                                                                    // ullAvailPageFile;ullTotalVirtual;ullAvailVirtual;ullAvailExtendedVirtual;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    memoryUsagePercent = static_cast<int>(statex.dwMemoryLoad);

    ramLabel->usage = memoryUsagePercent;
    ramLabel->update();

    DWORDLONG totalPhys = statex.ullTotalPhys;
    DWORDLONG availPhys = statex.ullAvailPhys;
    DWORDLONG usedPhys = totalPhys - availPhys;

    double totalGB = totalPhys / (1024.0 * 1024.0 * 1024.0);
    double usedGB = usedPhys / (1024.0 * 1024.0 * 1024.0);

    QString usedStr = QString::number(usedGB, 'f', 2);
    QString totalStr = QString::number(totalGB, 'f', 2);

    ui->labelRAMused->setText(usedStr + " GB");
    ui->labelRAMinstalled->setText(totalStr + " GB");

    double ratio = usedGB/ totalGB;
    constexpr double RAM_USAGE_LOW = 0.5;
    constexpr double RAM_USAGE_MEDIUM = 0.75;

    ui->labelRAMused->setProperty("class", " ");
    if (ratio < RAM_USAGE_LOW) {
        ui->labelRAMused->setProperty("class", "low");
    } else if (ratio < RAM_USAGE_MEDIUM) {
        ui->labelRAMused->setProperty("class", "medium");
    } else {
        ui->labelRAMused->setProperty("class", "high");
    }

    ui->labelRAMused->style()->unpolish(ui->labelRAMused);
    ui->labelRAMused->style()->polish(ui->labelRAMused);
}
