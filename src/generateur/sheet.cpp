#include <QtWidgets>
#include "mainwin.h"
#include "sheet.h"

Sheet::Sheet(QWidget *parent) : QWidget(parent)
{
    fileNew();
    mag = 3;        // 3px for 1mm on the robot
    setWindowTitle("Sans Titre[*] - Dessin pour drawbot Arc");
    setFixedSize(297*mag,210*mag);
}

void Sheet::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    int x=(int)(width()/zoom);
    int y=(int)(height()/zoom);

    paint.setWindow(0, 0, x, y);
    for (int i=0; i<liste.size()-1; i++) {
        paint.drawLine(liste[i], liste[i+1]);
    }
        updateStatus();
}

void Sheet::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(!isWindowModified())
        {
            setWindowModified(true);
            emit(hasChanged(fileName));
        }
        point=event->pos()/zoom;
        pileUndo.push(liste.size());
        update();
        updateStatus();
    }
}

void Sheet::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        liste.append(event->pos()/zoom);
        update();
        updateStatus();
        point=event->pos()/zoom;
   }
}

void Sheet::mouseReleaseEvent(QMouseEvent *event)
{
   if (event->button() == Qt::LeftButton)
    {
       liste.append(event->pos()/zoom);
       update();
       updateStatus();
    }
}

//SLOTS
void Sheet::fileNew()
{
    if(isWindowModified())
    {
        if ( QMessageBox::No == QMessageBox::question(this,
              tr("Modifications non sauvées"),
              tr("Sûr de vouloir pedre ce dessin ?")))
            return;
    }
    zoom=1;

    if (!liste.isEmpty())
    {
        liste.clear();
        pileUndo.clear();
        update();
    }
    fileName = "";
    setWindowModified(false);
    emit(hasChanged(fileName));
}

void Sheet::openFile(const QString & name)
{
    fileName = name;
    readFile();
}

void Sheet::readFile()
{
    QString s;
    QStringList c;
    QPoint p;
    double x,y;
    QFile fileSource(fileName);
    if (!fileSource.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(0, "Erreur", QString("Lecture"));
        return;
    }
    QTextStream sin(&fileSource);
    liste.clear();
    sin.readLine(0); // 1ère ligne

    while (!sin.atEnd())
    {
        s = sin.readLine(0);
        if (s!="};") {
            c = s.split(",");
            x = c[0].toDouble();
            y = c[1].toDouble();

            x = x*mag + 148.5*mag;
            y = -y*mag + 210*mag;

            p = QPoint(x, y);
            qDebug() << p;
            liste << p;
        }
    }
    fileSource.close();

    setWindowModified(false);
    emit(hasChanged(fileName));
    prependInFileNames();
    updateStatus();
    update();
}

void Sheet::open()
{
    if(isWindowModified())
    {
        if ( QMessageBox::No == QMessageBox::question(this,
              tr("Modifications non sauvées"),
              tr("Sûr de vouloir pedre ce dessin ?")))
            return;
    }
    QString oldName = fileName;
    fileName=QFileDialog::getOpenFileName(this,tr("Ouvrir"), "./", tr("Dessins (*.h)") );
    if (!fileName.isNull())
    {
        readFile();
    }
    else fileName = oldName;
}

void Sheet::save()
{
    if (!fileName.isEmpty())
    {
        QFile fileDest(fileName);

        if (!fileDest.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::critical(0, "Erreur", QString("Ecriture"));
            return;
        }

        QTextStream sout(&fileDest);
        double x, y;
        sout << "double liste[] = {" << endl;
        foreach(QPoint p, liste) {
        // Chgt coordonnées widget -> feuille
            x = (p.x() - 148.5*mag)/mag;
            y = (210*mag - p.y())/mag;
            sout << QString::number(x) << ", " << QString::number(y) << ", " << endl;
        }
        sout << "};" << endl;

        fileDest.close();

        setWindowModified(false);
        emit(hasChanged(fileName));
        prependInFileNames();
    }
    else saveAs();
}

void Sheet::saveAs()
{
    QString oldName = fileName;
    fileName=QFileDialog::getSaveFileName(this,tr("Sauver"), "./", tr("Dessins (*.h)") );
    if (!fileName.isEmpty()) save();
    else fileName = oldName;
}

void Sheet::undo()
{
    if (!pileUndo.isEmpty())
    {    
        int limite=pileUndo.pop();
        while (liste.size()>limite)
            liste.takeLast();
        update();
    }
}

void Sheet::zoomIn()
{
    zoom*=2;
    update();
}
    
void Sheet::zoomOut()
{
    zoom/=2;
    update();
}
    
void Sheet::zoomReset()
{
    zoom=1;
    update();
}

void Sheet::prependInFileNames()
{
    fileNames.prepend(fileName);
    fileNames.removeDuplicates();
    while(fileNames.size() > 5)
    {
        fileNames.removeLast();
    }
}

void Sheet::updateStatus() {
    QString info = QString("zoom : %1").arg(zoom) + "     " + QString("Nombre de points : %1").arg(liste.size());
    emit refresh(info);
}
