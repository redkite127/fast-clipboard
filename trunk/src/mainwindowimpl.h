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

#include <QSystemTrayIcon>
//
class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
	QString lire(int,int);

private slots:
	void on_action_Plus_triggered();
	void addLine(int);
	void editerX(int);
	void copierX(int);
	void show_hide();
	void sticon_dblclicked(QSystemTrayIcon::ActivationReason);
	
private:
	// Variables :
	QSystemTrayIcon *sticon;		// L'icone qui va aller dans le systemTray (SystemTrayIcon)
	QMenu *stmenu;					// Menu qui ira avec cet icone (SystemTrayMenu)
	QVBoxLayout* vLayout;	// nécessaire pour réussir a gérer le stretch en dessous des boutons
	int nombre;				// indique combien de ligne sont actuellement affichée
	QSignalMapper *signalMapper_edit;	// Relie le click du bouton editer à la fonction editerX et envoit le numéro de ligne du bouton
	QSignalMapper *signalMapper_copy;	// Idem mais lie le tout à copierX
	QDomDocument doc;	
	
	// Fonctions :
	void initTray();
};
#endif
