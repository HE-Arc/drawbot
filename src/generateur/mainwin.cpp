#include <QtWidgets>
#include "mainwin.h"
#include "sheet.h"

MainWin::MainWin(QWidget *parent) : QMainWindow(parent)
{
    actLigne = NULL;
    mySheet = new Sheet;
    setCentralWidget(mySheet);

    infoStatus = new QLabel(this);

    groupFiles = NULL;
    readSettings();

    createActions();
    createMenus();

    QPalette p = palette();
    // Sélectionne la couleur blanche pour le fond de la fenêtre.
    p.setColor( QPalette::Window, Qt::white);
    setPalette(p);

    connect(mySheet, SIGNAL(hasChanged(const QString&)), this, SLOT(setTitle(const QString&)));
    setTitle("");


    statusBar()->addPermanentWidget(infoStatus);

    mySheet->show();
}
void MainWin::writeSettings()
{
    QSettings settings("./mainwindow.ini", QSettings::IniFormat);

    settings.clear();
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("maximized", isMaximized());
    settings.endGroup();

    settings.beginGroup("Fichiers");
    int num = 0;
    while(!mySheet->fileNames.isEmpty() && num <= 5)
    {
        fileName = mySheet->fileNames.takeFirst();
        settings.setValue(QString().setNum(++num), fileName);
    }
    settings.endGroup();
}

void MainWin::readSettings()
{
    QSettings settings("./mainwindow.ini", QSettings::IniFormat);

    settings.beginGroup("MainWindow");
    if(settings.value("maximized").toBool())
    {
        resize(800,400);
        move(200, 200);
        showMaximized ();
    }
    else
    {
        resize(settings.value("size", QSize(800, 400)).toSize());
        move(settings.value("pos", QPoint(200, 200)).toPoint());
    }
    settings.endGroup();

    settings.beginGroup("Fichiers");
    for(int i=1; i <= 5; i++)
    {
        fileName = settings.value(QString().setNum(i), QString("")).toString();
        if(!fileName.isEmpty())
        {
            mySheet->fileNames.append(fileName);
        }
    }
    settings.endGroup();

}

void MainWin::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}

void MainWin::createActions()
{
    actNouveau = new QAction(tr("&Nouveau"),this);
    actQuitter = new QAction(tr("&Quitter"),this);
    actSave = new QAction(tr("Enregi&strer"),this);
    actSave->setShortcut(tr("Ctrl+S"));
    actSaveAS = new QAction(tr("Enregistrer sous..."),this);
    actOpen = new QAction(tr("&Ouvrir"),this);
    actOpen->setShortcut(tr("Ctrl+O"));

    actAnnuler = new QAction(tr("&Annuler"),this);
    actAnnuler->setShortcut(tr("Ctrl+Z"));

    actZoomIn = new QAction(tr("Zoom &In"),this);
    actZoomOut = new QAction(tr("Zoom &Out"),this);
    actZoomReset = new QAction(tr("&Echelle 1:1"),this);

    actAPropos = new QAction(tr("A &Propos"),this);

    connect(actNouveau, SIGNAL(triggered()), mySheet, SLOT(fileNew()));
    connect(actOpen, SIGNAL(triggered()), mySheet, SLOT(open()));
    connect(actSave, SIGNAL(triggered()), mySheet, SLOT(save()));
    connect(actSaveAS, SIGNAL(triggered()), mySheet, SLOT(saveAs()));
    connect(actQuitter, SIGNAL(triggered()), this, SLOT(close()));
    connect(actAnnuler, SIGNAL(triggered()), mySheet, SLOT(undo()));
    connect(actAPropos, SIGNAL(triggered()), this, SLOT(about()));
 
    connect(actZoomIn, SIGNAL(triggered()), mySheet, SLOT(zoomIn()));
    connect(actZoomOut, SIGNAL(triggered()), mySheet, SLOT(zoomOut()));
    connect(actZoomReset, SIGNAL(triggered()), mySheet, SLOT(zoomReset()));

    connect(mySheet, SIGNAL(refresh(const QString&)), this, SLOT(setStatus(const QString&)));
}

void MainWin::createMenus()
{
    menuFichier = menuBar()->addMenu(tr("&Fichier"));
    connect(menuFichier, SIGNAL(aboutToShow()), this, SLOT(updateFileMenu()));
    
    menuEdit = menuBar()->addMenu(tr("&Edition"));
    menuEdit->addAction(actAnnuler);
    
    menuZoom = menuBar()->addMenu(tr("&Zoom"));
    menuZoom->addAction(actZoomIn);
    menuZoom->addAction(actZoomOut);
    menuZoom->addAction(actZoomReset);
    
    menuAide = menuBar()->addMenu(tr("&?"));
    menuAide->addAction(actAPropos);
}

void MainWin::updateFileMenu()
{
    menuFichier->clear();
    menuFichier->addAction(actNouveau);
    menuFichier->addSeparator();
    menuFichier->addAction(actOpen);
    menuFichier->addAction(actSave);
    menuFichier->addAction(actSaveAS);
    menuFichier->addSeparator();
    int num = 0;
    delete groupFiles;
    groupFiles = NULL;

    if(mySheet->fileNames.size() > 0) groupFiles = new QActionGroup(this);
    while(num < mySheet->fileNames.size() && num < 5)
    {
        QAction *action  = new QAction(mySheet->fileNames[num], groupFiles);
        menuFichier->addAction(action);
        ++num;
    }

    if(mySheet->fileNames.size() > 0)
    {
        connect(groupFiles, SIGNAL(triggered(QAction*)), this, SLOT(openFile(QAction*)));
        menuFichier->addSeparator();
    }
    menuFichier->addAction(actQuitter);
}

void MainWin::openFile(QAction* action)
{
    QList<QAction *> lesActions = groupFiles->actions();
    int num = 0;
    while(num < lesActions.size())
    {
        if(lesActions[num] == action)
        {
            mySheet->openFile(mySheet->fileNames[num]);
        }
        ++num;
    }
}

void MainWin::setTitle(const QString &fileName)
{
     setWindowModified(mySheet->isWindowModified());

     QString shownName;
     if (fileName.isEmpty())
         shownName = tr("Sans Titre");
     else
         shownName = QFileInfo(fileName).absoluteFilePath();

     setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Tableau Blanc")));
//     qDebug() << "setTitle";
}

void MainWin::setStatus(const QString &msg){
  //  statusBar()->showMessage(msg);
    infoStatus->setText(msg);
}

void MainWin::about()
{   QMessageBox::information(this, tr("A Propos"), tr("Tableau Blanc\nDessin à main levée\nAvec sérialisation")); }
