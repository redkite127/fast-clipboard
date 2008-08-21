#ifndef EDITIMPL_H
#define EDITIMPL_H
//
#include <QDialog>


#include <QHostInfo>

#include "ui_edit.h"

#include "FCxml.h"
//

//Le fichier change pas à chaque fois, trouver comment le mettre en "global"? ou pas ?... car c du gaspillage de passer ça en parametre tt le tps

//Séparer la lecture de l'XML dans une autre classe, garder l XML en  mémoire et passer un ptr vers le texte à Edit?
// Le lire dans le main. avoir un objet gglobale? representant le XML

class EditImpl : public QDialog, public Ui::Edit
{
	Q_OBJECT

public:
	EditImpl(FCxml* x,int n=1, QWidget * parent = 0, Qt::WFlags f = 0 );
	
private slots:
	//void acc();
	//void rej();
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();
//	void on_lookup_clicked();
//	void lookup_result(const QHostInfo &host);

private:
	void loadItem(); // Comment faire? loadItem(FCxml, int) ou des variables comme fait ici? ...
	int num;
	FCxml *xmlDoc;
};
#endif
