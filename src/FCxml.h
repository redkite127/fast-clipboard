#ifndef FCXML_H
#define FCXML_H
//
#include <QDomDocument>
#include <QFile>
#include <QStringList> // Vérifier les includes...
/* Et pour ça ? includes?
QDomNodeList tab;
	QDomElement item;
	QDomNode n;
	QDomElement racine = doc.documentElement();	//renvoie la balise racine
	QDomNode noeud
*/
//
class FCxml : public QObject
{

	Q_OBJECT

public:
	//FCxml();
	FCxml(QFile*);//refé val ou ptr?
	void lireAll();

signals:
	void newNode(QString);		// On vient de trouver un new item(une config) FIX: reférence, pointeur ou variable?

public slots:
	bool loadFile(QFile*);	// Slot ou fct public?
	QStringList lireX(int);

private:
	QDomDocument doc;
};
#endif
