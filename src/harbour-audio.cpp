#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include "audioplayer.h"

#include <sailfishapp.h>

int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/harbour-audio.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //   - SailfishApp::pathToMainQml() to get a QUrl to the main QML file
    //
    // To display the view, call "show()" (will show fullscreen on device).

    QGuiApplication *app = SailfishApp::application(argc, argv);
    QQuickView *view = SailfishApp::createView();

    qmlRegisterSingletonType<AudioPlayer>("it.kempe.AudioPlayer", 1, 0, "AudioPlayer", audioPlayerProvider);

    view->setSource(SailfishApp::pathTo("qml/harbour-audio.qml"));
    view->showFullScreen();
    return app->exec();
}
