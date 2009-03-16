#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H
//
#include <QMainWindow>
#include "ui_FastClipboard.h"
#include "../libs/src/QChooseGUIStyleImpl.h"
#include "EditImpl.h" 

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
#include "aboutFCimpl.h"

#include <QSettings>

#include <QFile>

#include <QCheckBox>
//
class FastClipboardImpl : public QMainWindow, public Ui::FastClipboard
{
	Q_OBJECT

public:
	FastClipboardImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
        void readSettings();
        void writeSettings();

protected:
	void closeEvent(QCloseEvent *event);


private slots:
	void on_action_Plus_triggered();
	void on_action_Tray_triggered();
	void on_action_style_triggered();
	void addLine(QString);
	void editerX(int);
	void copierX(int);
	void show_hide();
	void sticon_dblclicked(QSystemTrayIcon::ActivationReason);
	void exit_applic();
	void on_lookup_clicked();
	//void lookup_result(const QHostInfo &host);
	void find_mask_and_net_id_from_ip(NetworksXML&);
	// 3 slots pour gerer les boutons speed, duplex et media-type
	void on_speedButton_clicked();
	void on_duplexButton_clicked();
	void on_mediaButton_clicked();
        void resetButtons();
        void on_name_textEdited(QString newName);
        QString readBBconf(QFile &file);
        bool readCheckedX(int);
        void setCheckX(bool);
	
private:
	// Variables :
	QSystemTrayIcon *sticon;		// L'icone qui va aller dans le systemTray (SystemTrayIcon)
	QMenu *stmenu;					// Menu qui ira avec cet icone (SystemTrayMenu)
	QVBoxLayout *vLayout;	// necessaire pour reussir a gerer le stretch en dessous des boutons
	int nombre;				// indique combien de ligne sont actuellement affichee
	QSignalMapper *signalMapper_edit;	// Relie le click du bouton editer a  la fonction editerX et envoit le numero de ligne du bouton
        QSignalMapper *signalMapper_copy;	// Idem mais lie le tout e  copierX
	FCxml *xmlDoc;
	QNetworkAddressEntry tmpAddress; // Ip de l'host trouve grace au lookup
	QString tmpTeamName;
	int tmpShortMask;
	
	// Fonctions :
	void initTray();
};
#endif

