#include "FastClipboardImpl.h"
#include <QtSingleApplication>
//
int main(int argc, char ** argv)
{
    QtSingleApplication  app( argc, argv );

    //if (app.isRunning())
    //        return 0;
    if (app.sendMessage("Wake up!"))
        return 0;

    //
    QApplication::setOrganizationName("Cisco");
    QApplication::setOrganizationDomain("cisco.com");
    QApplication::setApplicationName("Fast-Clipboard");
    // //

    FastClipboardImpl win;
    // Set the widget which need to be made visible when a second instance is trying to start
    app.setActivationWindow(&win);
    // Affiche la fenetre si une deuxieme instance de FC a voulu se lancer
    QObject::connect(&app, SIGNAL(messageReceived(const QString&)), &win, SLOT(show_hide()));
	
    win.show();
    app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
    return app.exec();
}
