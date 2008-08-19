#include "mainwindowimpl.h"
//

MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) : QMainWindow(parent, f)
{
	setupUi(this);
	
	this->nombre = 0;
	
	// Lecture du fichier (va le charger dans domDocument)
	QFile *file= new QFile("pp2DB.xml"); //FIXME pas en hard pleaaaaase ! 
	xmlDoc = new FCxml(file);
	connect(xmlDoc,SIGNAL(newNode(QString)),this,SLOT(addLine(QString)));

	// Quitter le programme par le menu
	connect(action_Quitter,SIGNAL(triggered()),this,SLOT(exit_applic()));
	
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
	xmlDoc->lireAll();	// Va lire le fichier xml et chaque fois qu'il trouvera un item, il enverra un signal à addLine avec le titre en paramètre !
	
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
	
	EditImpl *e = new EditImpl(xmlDoc, i, this);

	//connect(e->buttonBox,SIGNAL(accepted()),this,SLOT(acc()));
	//connect(e->buttonBox,SIGNAL(rejected()),this,SLOT(rej()));
	
	e->show();	
	
}

void MainWindowImpl::acc()
{
	xmlDoc->writeX(2,"t","tt");
	qDebug("accept");
	
}

void MainWindowImpl::rej()
{
	qDebug("cancel");
//	exit(0);
}

void MainWindowImpl::copierX(int i)
{
	QStringList r;
	QClipboard *clipboard = QApplication::clipboard();
	
	r=xmlDoc->lireX(i);
	
	if(r.size()==2)	//chaque fois verifier que size ok? ...
		clipboard->setText(r.at(1));
}

void MainWindowImpl::on_action_Plus_triggered()
{
	xmlDoc->addNode();
	return;
}

void MainWindowImpl::on_action_Tray_triggered()
{
	show_hide();
}

void MainWindowImpl::initTray()
{
	/*
	 * Va initialiser et afficher un icone dans le systeme tray
	 */

	sticon = new QSystemTrayIcon(QIcon(":/images/icon/colors.png"),this);
	
	stmenu = new QMenu(this);
	
	QAction *aff_cach = new QAction("Afficher / Cacher",this);		// Crée une action
	stmenu->addAction(aff_cach);									// L'ajoute dans un menu
	stmenu->setDefaultAction(aff_cach);								// Change l'APPARANCE de l'action (en gras) et c'est tout! 
	connect(aff_cach,SIGNAL(triggered()),this,SLOT(show_hide()));	// Lie l'actionau slot qui affiche/cache la fenêtre principale
	
	stmenu->addSeparator();
	
	connect(sticon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(sticon_dblclicked(QSystemTrayIcon::ActivationReason)));	// Lie au slot qui dit quoi faire quand on double clic sur l'icone
	
	QAction *quit = new QAction("Quitter",this);
	stmenu->addAction(quit);
	connect(quit,SIGNAL(triggered()),this,SLOT(exit_applic())); //mwouai, ca serait mieux de se baser sur autre chose que le fait que le tray soit la ou pas
	
	sticon->setContextMenu(stmenu); // On assigne le menu contextuel à l'icône de notification
	
	sticon->show();
	
	return;
}

void MainWindowImpl::show_hide()
{
	if(this->isHidden())
	{
		/*
		 * void QWidget::activateWindow ()
		 *
		 * This function performs the same operation as clicking the mouse on the title bar of a top-level window.
		 * On X11, the result depends on the Window Manager. If you want to ensure that the window is stacked on top
		 * as well you should also call raise(). Note that the window must be visible, otherwise activateWindow() has no effect.
		 */
		this->show();
		this->raise();
		this->activateWindow();
	}
	else
		if(this->isMinimized())
		{
			this->showNormal();
			//raise et activate? faire test sous windows
		}
		else
			this->hide();
		
	return;
}

void MainWindowImpl::sticon_dblclicked(QSystemTrayIcon::ActivationReason reason)
{
	if ( reason == 2 || reason == 3 )
		this->show_hide();

	return;
}

void MainWindowImpl::closeEvent(QCloseEvent *event)
{
	if (sticon->isVisible()) 
	{
		//QMessageBox::information(this, tr("Systray"),tr("The program will keep running in the system tray. To terminate the program,choose <b>Quit</b> in the context menu of the system tray entry."));
		hide();
		event->ignore();
	}
}

void MainWindowImpl::exit_applic()
{
	sticon->hide();
	this->close();
}
//
