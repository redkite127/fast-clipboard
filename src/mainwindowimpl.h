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

#include <QMessageBox>

#include <QHostInfo>
#include <QNetworkAddressEntry>

#include "NetworksXml.h"
#include "FCxml.h"
//
class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
//	QString lire(int,int);

protected:
	void closeEvent(QCloseEvent *event);


private slots:
	void on_action_Plus_triggered();
	void on_action_Tray_triggered();
	void addLine(QString);
	void editerX(int);
	void copierX(int);
	void show_hide();
	void sticon_dblclicked(QSystemTrayIcon::ActivationReason);
	void exit_applic();
	void on_lookup_clicked();
	void lookup_result(const QHostInfo &host);
	void find_mask_and_net_id_from_ip(NetworksXML&);
	
private:
	// Variables :
	QSystemTrayIcon *sticon;		// L'icone qui va aller dans le systemTray (SystemTrayIcon)
	QMenu *stmenu;					// Menu qui ira avec cet icone (SystemTrayMenu)
	QVBoxLayout *vLayout;	// nécessaire pour réussir a gérer le stretch en dessous des boutons
	int nombre;				// indique combien de ligne sont actuellement affichée
	QSignalMapper *signalMapper_edit;	// Relie le click du bouton editer à la fonction editerX et envoit le numéro de ligne du bouton
	QSignalMapper *signalMapper_copy;	// Idem mais lie le tout à copierX
	FCxml *xmlDoc;
	QNetworkAddressEntry tmpAddress; // Ip de l'host trouvé grace au lookup
	QString tmpTeamName;
	int tmpShortMask;
	
	// Fonctions :
	void initTray();
};
#endif

