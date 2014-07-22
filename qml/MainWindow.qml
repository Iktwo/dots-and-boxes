import QtQuick 2.0

FocusScope {
    focus: true

    /// Count and show toast if more than once
    Keys.onBackPressed: console.log("BACK")

    Menu {
        id: menu

        onNewGame: loader.sourceComponent = gameArea
        visible: loader.sourceComponent == undefined
    }

    Loader {
        id: loader

        anchors.fill: parent

        onStatusChanged: {
            if (status == Loader.Ready)
                item.forceActiveFocus()
            else if (status == Loader.Null)
                menu.forceActiveFocus()
        }
    }

    Component {
        id: gameArea

        GameArea {
            onBack: loader.sourceComponent = undefined
        }
    }
}
