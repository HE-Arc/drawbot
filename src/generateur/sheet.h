#ifndef SHEET_H
#define SHEET_H

#include <QWidget>
#include <QStack>

class QPaintEvent;
class QMouseEvent;
class MainWin;

class Sheet : public QWidget
{
      Q_OBJECT
      public:
        Sheet(QWidget *parent = 0);
//        ~Sheet();
//        QString getFileName();
//        QStringList getFileNames();

      public slots:
        void fileNew();
        void open();
        void openFile(const QString &);
        void save();
        void saveAs();
        void undo();
        void zoomIn();
        void zoomOut();
        void zoomReset();

      protected:
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *);
        void mouseMoveEvent(QMouseEvent *);
        void mouseReleaseEvent(QMouseEvent *);
        void readFile();
        void prependInFileNames();
        QStringList fileNames;

      private:
        QPoint point;
        QList<QPoint> liste;
        QStack<int> pileUndo;
        double zoom, mag;
        QString fileName;
        //MainWin* mw;
        void updateStatus();

      signals:
        void hasChanged(const QString&);
        void refresh(const QString&);

      friend class MainWin;
};

#endif
