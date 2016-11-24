#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include "sheet.h"

class QMenu;
class QAction;
class QActionGroup;
class QLabel;

class MainWin : public QMainWindow
{
    Q_OBJECT

     public:
        MainWin(QWidget *parent = 0);
        QAction *actLigne;

    protected:
        void closeEvent(QCloseEvent *event);

    private:
        void createActions();
        void createMenus();
        void createToolBars();
        void readSettings();
        void writeSettings();

        Sheet *mySheet;
        QMenu *menuFichier, *menuEdit, *menuDessin, *menuFormes, *menuZoom, *menuAide;
        QAction *actNouveau, *actQuitter, *actAnnuler;
        QAction *actSave, *actSaveAS, *actOpen;
        QAction *actZoomIn, *actZoomOut, *actZoomReset, *actAPropos;
        QActionGroup *groupFiles;
        QLabel *infoStatus;

        QString fileName;

    private slots:
        void setTitle(const QString &);
        void setStatus(const QString &);
        void about();
        void updateFileMenu();
        void openFile(QAction*);
};

#endif
