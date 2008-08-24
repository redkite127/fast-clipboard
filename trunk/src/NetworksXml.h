#ifndef NETWORKSXML_H
#define NETWORKSXML_H
//
#include <QXmlDefaultHandler>
#include <QNetworkAddressEntry>

//
class NetworksXML : public QObject, public QXmlDefaultHandler
{
	Q_OBJECT
	
public:
	//NetworksXML();	//Le constructeur va être obliger de lancer la recherche et de
	NetworksXML(QHostAddress);	//Le constructeur va être obliger de lancer la recherche et de 

	virtual bool startDocument () ;                        //traite le début du document
	virtual bool startElement ( const QString &, const QString &, const QString &, const QXmlAttributes & );	//traite la balise ouvrante
	virtual bool fatalError (const QXmlParseException & exception);
	virtual bool characters ( const QString &);            //traite les données
	virtual bool endDocument ();                           //traite la fin du document
	virtual bool endElement ( const QString &, const QString &, const QString & );	//traite la balise fermante
	
	QNetworkAddressEntry getNetworkAddress();
	QString getTeamName();
	int getShortMask();

private :
	QString balise_item;         //drapeau pour une balise “item”
	QString balise;                //drapeau pour une balise “TeamName” ou “IP” ou "SubnetMask"
	
	QNetworkAddressEntry networkAddress;
	QString teamName;
	QHostAddress IP;
	int shortMask;
};
#endif
