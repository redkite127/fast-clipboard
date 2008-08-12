#include "mainwindowimpl.h"
//

MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) : QMainWindow(parent, f)
{
	setupUi(this);
	
	this->nombre = 0;
	
	// Lecture du fichier (va le charger dans domDocument)
	QFile *file= new QFile("pp2DB.xml");
	xmlDoc = new FCxml(file);
	connect(xmlDoc,SIGNAL(newNode(QString)),this,SLOT(addLine(Qstring)));

	// Quitter le programme par le menu
	connect(action_Quitter,SIGNAL(triggered()),this,SLOT(close()));
	
	// Création du signalMapper et connection de son signal mapped au slot désiré : http://doc.trolltech.com/qq/qq10-signalmapper.html
	signalMapper_edit = new QSignalMapper(this);
	connect(signalMapper_edit,SIGNAL(mapped(int)),this,SLOT(editerX(int)));
	signalMapper_copy = new QSignalMapper(this);
	connect(signalMapper_copy,SIGNAL(mapped(int)),this,SLOT(copierX(int)));
	
	/*
	 * ici, je crécupère le layout central, j'y ajoute un QVBoxLayout et un stretch comme ça je ne me tracasse
	 * pas du stretch par après puisque qu'il est dans le layout central avec un seul objet(le new VBox). C'est
	 * ce new VBox qui grandi quand j'ajoute des boutons dedans, c'est tout.
	 */
	vLayout = new QVBoxLayout();
	//this->centralWidget()->layout()->addItem(vLayout);
	((QBoxLayout *)this->centralWidget()->layout())->addLayout(vLayout); // Si on ne crée pas cette relation avec le layout parent, les modifications apportées au fils ne se veront pas dans le parent car il ne se repeindra pas
	((QBoxLayout *)this->centralWidget()->layout())->addStretch();

	// Création d'un certain nombre de ligne
	//addLine(nombre);
	xmlDoc->lireAll();
	
	
	// Initialisation du System Tray Icon
	initTray();
}

void MainWindowImpl::addLine(QString t)
{
	nombre++;

	QHBoxLayout *hLayout = new QHBoxLayout();
	
	vLayout->addLayout(hLayout);	// Si on ne crée pas cette relation avec le layout parent, les modifications apportées au fils ne se veront pas dans le parent car il ne se repeindra pas
	
	//QPushButton *button1 = new QPushButton(lire(i,0),centralwidget);
	QPushButton *button1 = new QPushButton(t,centralwidget);
	
	QPushButton *button2 = new QPushButton(QIcon(":/images/icon/pencil.png"),QString(""),centralwidget);
	button2->setMaximumWidth(32);
	button2->setIconSize(QSize(22,22));
	
	hLayout->addWidget(button1);
	hLayout->addWidget(button2);
	
	// Indication du mapping à faire (correspondance objet, information)
	signalMapper_copy->setMapping(button1,nombre);
	signalMapper_edit->setMapping(button2, nombre);
	
	// Lie clicked au mapper
	connect(button1, SIGNAL(clicked()), signalMapper_copy, SLOT(map()));
	connect(button2, SIGNAL(clicked()), signalMapper_edit, SLOT(map()));

}

void MainWindowImpl::editerX(int i)
{
	QStringList r;
	
	EditImpl *e = new EditImpl(i ,this);
	
	///Bordel XML, c le constucteur de editerX qui doit aller lire !
	/*e->titre->setText(lire(i,0));
	e->texte->insertPlainText(lire(i,1));*/
	////////

//REFAIRE 
	r = xmlDoc->lireX(i);
	e->titre->setText(r.at(0));
	e->texte->insertPlainText(r.at(1)); // FIXME, verfifier qu'y en a bien 2 sinon crash

	e->show();	
}

void MainWindowImpl::copierX(int i)
{
	QClipboard *clipboard = QApplication::clipboard();
//	clipboard->setText(lire(i,1));
}

// Refaire ...
/*QString MainWindowImpl::lire(int i, int j)			// i pour la ligne, j pour titre ou texte 0=titre 1=texte
{
	
	///////////////////////////////////////////
	// Bordel de lecture XML ... a réaranger vite fait pour que ça marche
	QFile file("pp2DB.xml");
	if (!file.open(QIODevice::ReadOnly))
		return "Error";
	if (!doc.setContent(&file))
	{
		file.close();
		return "Error";
	}
	file.close();
	

	QDomNodeList tab;
	QDomElement item;
	QDomNode n;
	QDomElement racine = doc.documentElement();	//renvoie la balise racine
	QDomNode noeud = racine.firstChild();	//renvoie la 1ere balise, icifast-clipboard
	///////////////////1ere fin bordel XML

		///////////// suite bordel XML  :
		
		
		while(!noeud.isNull())
		{
			item = noeud.toElement();
			if(item.tagName()=="item"  && item.attribute("num")==QString("%1").arg(i))
			{
				tab = item.childNodes();
				n = tab.item(j);
				return n.firstChild().toText().data();
			}
			noeud = noeud.nextSibling();
		}
		//////////////// derniere fin bordel XML
		
		return "Error";
}
*/

void MainWindowImpl::on_action_Plus_triggered()
{
//	addLine();
	
	return;
}

void MainWindowImpl::initTray()
{
	/*
	 * Va initialiser et afficher un icone dans le systeme tray
	 */

	sticon = new QSystemTrayIcon(QIcon(":/images/icon/colors.png"),this);
	
	stmenu = new QMenu(this);
	
	QAction *aff_cach = new QAction("Afficher",this);				// Crée une action
	stmenu->addAction(aff_cach);									// L'ajoute dans un menu
	stmenu->setDefaultAction(aff_cach);								// Change l'APPARANCE de l'action (en gras) et c'est tout! 
	connect(aff_cach,SIGNAL(triggered()),this,SLOT(show_hide()));	// Lie l'actionau slot qui affiche/cache la fenêtre principale
	connect(sticon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(sticon_dblclicked(QSystemTrayIcon::ActivationReason)));	// Lie au slot qui dit quoi faire quand on double clic sur l'icone
	
	sticon->setContextMenu(stmenu); // On assigne le menu contextuel à l'icône de notification
	
	sticon->show();
	
	return;
}

void MainWindowImpl::show_hide()
{
	if(this->isHidden())
		this->show();
	else
		this->hide();
		
	return;
}

void MainWindowImpl::sticon_dblclicked(QSystemTrayIcon::ActivationReason reason)
{
	if(reason == 2)
		this->show_hide();
	
	return;
}
//
