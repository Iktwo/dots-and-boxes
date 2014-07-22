import QtQuick 2.0

Rectangle {
    signal hide

    anchors.fill: parent

    color: "black"

    Timer {
        interval: 650

        running: true

        onTriggered: hide()
    }

    Image {
        id: imgLogo

        source: "qrc:/images/logo"

        anchors.centerIn: parent
    }
}
