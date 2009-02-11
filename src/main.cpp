#include <QApplication>
#include "FastClipboardImpl.h"
//
int main(int argc, char ** argv)
{
    QApplication app( argc, argv );
    //
    QApplication::setOrganizationName("Cisco");
    QApplication::setOrganizationDomain("cisco.com");
    QApplication::setApplicationName("Fast-Clipboard");
    // //

    FastClipboardImpl win;
	
    win.show();
    app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
    return app.exec();
}
