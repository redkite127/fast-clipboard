#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H
//
#include <QMainWindow>
#include "ui_mainwindow.h"

#include "editimpl.h" 

#include <QPushButton>
#include <QSignalMapper>

#include <QDomDocument>
#include <QFile>
#include <QClipboard>
//
class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
	QString lire(int,int);

private slots:
	void on_actionPlus_triggered();
	void editerX(int);
	void copierX(int);
	
private:
	int nombre;
	QSignalMapper *signalMapper;
	QSignalMapper *signalMapper2;
	QDomDocument doc;
	
	
	
};
#endif




