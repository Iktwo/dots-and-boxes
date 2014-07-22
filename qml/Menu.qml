import QtQuick 2.2
import QtQuick.Controls 1.1

FocusScope {
    signal newGame

    anchors.fill: parent

    focus: true

    Label {
        text: qsTr("Tap to start a new game")
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent

        onClicked: newGame()
    }
}
