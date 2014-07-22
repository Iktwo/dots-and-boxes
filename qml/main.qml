import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    id: root

    property bool doLoad : false

    visible: true
    width: 640
    height: 480

    Loader {
        id: menuLoader

        anchors.fill: parent
        visible: false
        asynchronous: true

        focus: true

        onLoaded: loadingScreenLoader.source = ""
    }

    Loader {
        id: splashScreenLoader

        anchors.fill: parent

        source: "SplashScreen.qml"

        onLoaded: loadingScreenLoader.source = "LoadingScreen.qml"
    }

    Loader {
        id: loadingScreenLoader

        anchors.fill: parent

        asynchronous: true
        visible: false

        onVisibleChanged: {
            if (visible){
                menuLoader.source = "MainWindow.qml"
                menuLoader.visible = true
                loadingScreenLoader.source = ""
            }
        }

        source: "LoadingScreen.qml";
    }

    Connections {
        id: splashConnection

        target: splashScreenLoader.item
        onHide: loadMenu()
    }

    function loadMenu(){
        loadingScreenLoader.visible = true
        splashScreenLoader.source = ""
    }
}
