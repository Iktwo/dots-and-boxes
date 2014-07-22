import QtQuick 2.2
import QtQuick.Controls 1.1

Rectangle {
    anchors.fill: parent

    Label {
        id: name

        text: qsTr("LOADING SCREEN")
        font.pointSize: 40

        anchors.centerIn: parent
    }

    PropertyAnimation {
        target: name; duration: 3500;
        properties: "rotation"
        to: 360
        //direction: RotationAnimation.Counterclockwise
        running: true
        loops: Animation.Infinite
    }
}
