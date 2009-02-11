#include "FastClipboardImpl.h"
//

FastClipboardImpl::FastClipboardImpl( QWidget * parent, Qt::WFlags f) : QMainWindow(parent, f)
{
	setupUi(this);
	
	// Initialisation du System Tray Icon ATTENTION, le faire avant d'ajouter des lignes!
	initTray();
	// Configure menu
	AboutFCImpl *about = new AboutFCImpl;
	connect(actionAbout_Fast_Clipboard,SIGNAL(triggered()),about,SLOT(show()));
	connect(actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
		
	this->nombre = 0;
	// Lecture du fichier (va le charger dans domDocument)
	QFile *file= new QFile("FastClipboardDB.xml"); //FIXME pas en hard pleaaaaase ! 
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
	 * ici, je récupère le layout central, j'y ajoute un QVBoxLayout et un stretch comme ça je ne me tracasse
	 * pas du stretch par après puisque qu'il est dans le layout central avec un seul objet(le new VBox). C'est
	 * ce new VBox qui grandi quand j'ajoute des boutons dedans, c'est tout.
	 */
	vLayout = new QVBoxLayout();
	((QBoxLayout *)this->centralWidget()->layout())->addLayout(vLayout); // Si on ne crée pas cette relation avec le layout parent, les modifications apportées au fils ne se veront pas dans le parent car il ne se repeindra pas
	((QBoxLayout *)this->centralWidget()->layout())->addStretch();

	// Création d'un certain nombre de ligne
	xmlDoc->lireAll();	// Va lire le fichier xml et chaque fois qu'il trouvera un item, il enverra un signal �  addLine avec le titre en paramètre !
	
	// Auto-selection du texte lors du clic sur un LineEdit
	//connect(name,SIGNAL(clicked()),name,SLOT(selectAll()));
	//connect(BBinterface,SIGNAL(clicked()),BBinterface,SLOT(selectAll()));
	name->selectAll();
	
	// Adaptation des QLedButton puisque je ne sais pas modifier tout par le designer car c'est seulement un "promote to"
	speedButton->setLedColor(Qt::darkGreen);
	duplexButton->setLedColor(Qt::darkGreen);
	mediaButton->setLedColor(Qt::darkGreen);
	
        // Read settings
        readSettings();
}

void FastClipboardImpl::addLine(QString t)
{
	nombre++;

	QHBoxLayout *hLayout = new QHBoxLayout();
	
	vLayout->addLayout(hLayout);	// Si on ne crée pas cette relation avec le layout parent, les modifications apportées au fils ne se veront pas dans le parent car il ne se repeindra pas
	
	QPushButton *button1 = new QPushButton(t,centralwidget);
	
	QPushButton *button2 = new QPushButton(QIcon(":/images/images/icon/pencil.png"),QString(""),centralwidget);
	button2->setMaximumWidth(32);
	button2->setIconSize(QSize(22,22));
	
	hLayout->addWidget(button1);
	hLayout->addWidget(button2);
	
	// Indication du mapping �  faire (correspondance objet, information)
	signalMapper_copy->setMapping(button1,nombre);
	signalMapper_edit->setMapping(button2, nombre);
	
	// Lie clicked au mapper
	connect(button1, SIGNAL(clicked()), signalMapper_copy, SLOT(map()));
	connect(button2, SIGNAL(clicked()), signalMapper_edit, SLOT(map()));

	// Mise �  jour du menu du system Tray
	QAction *act = new QAction(t,this);
	connect(act,SIGNAL(triggered()),button1,SLOT(click()));
	QList<QAction *> list = stmenu->actions();	// Pour pouvoir récupérer le before
	stmenu->insertAction(list.at(list.size()-2),act); 
}

void FastClipboardImpl::editerX(int i)
{
	QStringList r;
	
	EditImpl *e = new EditImpl(xmlDoc, i, this);

	//connect(e->buttonBox,SIGNAL(accepted()),this,SLOT(acc()));
	//connect(e->buttonBox,SIGNAL(rejected()),this,SLOT(rej()));
	
	e->show();
}

void FastClipboardImpl::copierX(int i)
{
	QStringList r;
	QClipboard *clipboard = QApplication::clipboard();
	
	r=xmlDoc->lireX(i);
	
	if(r.size()==2)	//chaque fois verifier que size ok? ...
		clipboard->setText(r.at(1));
}

void FastClipboardImpl::on_lookup_clicked()
{
	// Recherche de l'adresse de l'host indiqué et stockage dans IP de tmpAddress (QNewtorkAddressEntry)
	//QHostInfo::lookupHost(name->text(),this, SLOT(lookup_result(QHostInfo)));	// Version qui appelle un slot (c'est donc threadé et ç am arrange pas. faut que j'attende davoir la reponse avant de continuer
	QHostInfo info = QHostInfo::fromName(name->text());
	if (!info.addresses().isEmpty())
	{
		tmpAddress.setIp(info.addresses().first());
		lookup_status->setText(info.addresses().first().toString());
		
		NetworksXML handler(tmpAddress.ip());	// En plus d'etre un handler pour le parser SAX, il va contenir les adresses (netID et mask) qui m'interesse
		find_mask_and_net_id_from_ip(handler);
		tmpAddress.setNetmask(handler.getNetworkAddress().netmask());
		tmpAddress.setBroadcast(QHostAddress(handler.getNetworkAddress().ip().toIPv4Address()+1)); // J'ai pas besoin du brodcast, je vai stocker le netID dedans.
		tmpTeamName = handler.getTeamName();
		tmpShortMask = handler.getShortMask();
		//qDebug() << "IP : " << tmpAddress.ip().toString() << "/" << tmpShortMask << endl << "Mask : " << tmpAddress.netmask().toString() << endl << "Gateway : " << tmpAddress.broadcast().toString() << endl;
		lookup_status->setText(tmpTeamName);
		lookup_status_2->setText(tmpAddress.ip().toString() + QString("/%1").arg(tmpShortMask));
	}
	else
	{
		lookup_status->setText("< lookup failed >");
		lookup_status_2->setText("");
	}
	
	
	//Comment faire pour attendre que le slot lookup_result soit fini?
	//qDebug()<< tmpAddress.ip() << endl << tmpAddress.netmask()<<endl<< (tmpAddress.ip().toIPv4Address()&tmpAddress.netmask().toIPv4Address())+1;
	
	//Comment faire d'autre ? un XML avec une variable dedans qui serra remplacée? mouais, pas mal
	QString conf;
	QClipboard *clipboard = QApplication::clipboard();
	
	conf = "\nconfigure terminal\nhostname " + name->text() + "\n";
	conf += "default interface " + BBinterface->text() + "\n";
	conf += "interface " + BBinterface->text() + "\n";
	conf += "ip address " + tmpAddress.ip().toString() + " " + tmpAddress.netmask().toString() + "\n";
	if ( speedButton->text() != "speed" )
		conf += "speed " + speedButton->text().simplified() + "\n";
	if ( duplexButton->text() != "duplex" )
		conf += "duplex " + duplexButton->text().simplified() + "\n";;
	if ( mediaButton->text() != "media" )
		conf += "media-type " + mediaButton->text().simplified() + "\n";;
	conf += "no shut\nexit\n";
	conf += "ip route 0.0.0.0 0.0.0.0 " + tmpAddress.broadcast().toString() + "\n";
	conf += "exit\n";

	clipboard->setText(conf);
}

/*
void FastClipboardImpl::lookup_result(const QHostInfo &host)
{
	if (host.error() != QHostInfo::NoError)
	{
		//qDebug() << "Lookup failed:" << host.errorString();
		lookup_status->setText("< lookup failed >");
		return;
	}

	if (!host.addresses().isEmpty())
	{
		tmpAddress.setIp(host.addresses().first());
		lookup_status->setText("< " + tmpAddress.ip().toString() + " >");
		
		//Recherche de son NetworkID
		find_mask_and_net_id_from_ip();
	}
}
*/

void FastClipboardImpl::find_mask_and_net_id_from_ip(NetworksXML& handler)
{
	QFile file;
	QXmlInputSource *inputSource;
	QXmlSimpleReader reader;                 //une interface pour notre parseur
	file.setFileName("CISCObackbone.xml");         //spécifie le nom du fichier xml �  lire
	inputSource= new QXmlInputSource(&file); //associe une source xml au fichier
	reader.setContentHandler(&handler);      //associe l’interface �  notre parseur
	reader.parse(inputSource);               //débute la lecture du document xml
	//qDebug()<< tmpAddress.ip().toString() << endl << handler.getNetworkAddress().ip().toString() << handler.getNetworkAddress().netmask().toString() <<endl << handler.getTeamName()<< QHostAddress(handler.getNetworkAddress().ip().toIPv4Address()+1).toString();
}

void FastClipboardImpl::on_action_Plus_triggered()
{
	xmlDoc->addNode();
	return;
}

void FastClipboardImpl::on_action_Tray_triggered()
{
	show_hide();
}

void FastClipboardImpl::on_action_style_triggered()
{
	QChooseGUIStyleImpl style;
	style.exec();
}

void FastClipboardImpl::initTray()
{
	/*
	 * Va initialiser et afficher un icone dans le systeme tray
	 */

	sticon = new QSystemTrayIcon(QIcon(":/images/images/icon/colors.png"),this);
	
	stmenu = new QMenu(this);
	
	QAction *aff_cach = new QAction("Afficher / Cacher",this);		// Crée une action
	stmenu->addAction(aff_cach);									// L'ajoute dans un menu
	stmenu->setDefaultAction(aff_cach);								// Change l'APPARANCE de l'action (en gras) et c'est tout! 
	connect(aff_cach,SIGNAL(triggered()),this,SLOT(show_hide()));	// Lie l'actionau slot qui affiche/cache la fenêtre principale
	
	stmenu->setSeparatorsCollapsible(false);
	stmenu->addSeparator();
	stmenu->addSeparator();
	
	connect(sticon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(sticon_dblclicked(QSystemTrayIcon::ActivationReason)));	// Lie au slot qui dit quoi faire quand on double clic sur l'icone
	
	QAction *quit = new QAction("Quitter",this);
	stmenu->addAction(quit);
	connect(quit,SIGNAL(triggered()),this,SLOT(exit_applic()));
	
	sticon->setContextMenu(stmenu); // On assigne le menu contextuel �  l'icône de notification
	
	sticon->show();
	
	return;
}

void FastClipboardImpl::show_hide()
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

void FastClipboardImpl::sticon_dblclicked(QSystemTrayIcon::ActivationReason reason)
{
	if ( reason == 2 || reason == 3 )
		this->show_hide();

	return;
}

void FastClipboardImpl::closeEvent(QCloseEvent *event)
{
	if (sticon->isVisible()) 
	{
		//QMessageBox::information(this, tr("Systray"),tr("The program will keep running in the system tray. To terminate the program,choose <b>Quit</b> in the context menu of the system tray entry."));
		hide();
		event->ignore();
	}
}

void FastClipboardImpl::exit_applic() //mwouai, ca serait mieux de se baser sur autre chose que le fait que le tray soit la ou pas
{
	sticon->hide();
	this->close();
}

void FastClipboardImpl::on_speedButton_clicked()
{
	if(speedButton->text()=="speed")
	{
		speedButton->setText("auto");
		speedButton->setLedValue(true);
	}
	else if(speedButton->text()=="auto")
		speedButton->setText("10");
	else if(speedButton->text()=="10")
		speedButton->setText("100");
	else if(speedButton->text()=="100")
		speedButton->setText("1000");
	else if(speedButton->text()=="1000")
	{
		speedButton->setText("speed");	// Que faire si on ne choisit rien? "default speed" ou "no speed" ou rien? ==> rien 
		speedButton->setLedValue(false);
	}
};

void FastClipboardImpl::on_duplexButton_clicked()
{
	if(duplexButton->text()=="duplex")
	{
		duplexButton->setText("auto");
		duplexButton->setLedValue(true);
	}
	else if(duplexButton->text()=="auto")
		duplexButton->setText("half");
	else if(duplexButton->text()=="half")
		duplexButton->setText("full");
	else if(duplexButton->text()=="full")
	{
		duplexButton->setText("duplex"); 
		duplexButton->setLedValue(false);
	}
};

void FastClipboardImpl::on_mediaButton_clicked()
{
	if(mediaButton->text()=="media")
	{
		mediaButton->setText("rj45");
		mediaButton->setLedValue(true);
	}
	else if(mediaButton->text()=="rj45")
		mediaButton->setText("sfp");
	else if(mediaButton->text()=="sfp")
		mediaButton->setText("gbic");
	else if(mediaButton->text()=="gbic")
	{
		mediaButton->setText("media"); 
		mediaButton->setLedValue(false);
	}
};

void FastClipboardImpl::readSettings()
{
    QSettings settings;

    QString s  = settings.value("style", "NULL").toString();
    if (s != "NULL")
        QApplication::setStyle( QStyleFactory::create(s) );

}

void FastClipboardImpl::writeSettings()
{
    QSettings settings;

}

//
