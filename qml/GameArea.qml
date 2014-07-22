import QtQuick 2.2
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0
import Tile 1.0
import BoxesModel 1.0

FocusScope {
    property var colors: ["#1dd2af", "#2ecc71", "#3498db", "#9b59b6"]
    property int animationDuration: 280
    property int barSize: 5

    signal back

    anchors.fill: parent
    focus: true

    Keys.onLeftPressed: boxesModel.skipPlayer()
    Keys.onBackPressed: back()

    BoxesModel {
        id: boxesModel

        columns: 5
        rows: 5

        onPlayersTie: {
            //winBackground.color = colors[player]
            winBackground.color = "black"
            winLabel.text = "Tie"
            winIndicator.visible = true
        }

        onPlayerWins: {
            winBackground.color = colors[player]
            winLabel.text = "Player " + player +" wins"
            winIndicator.visible = true
        }
    }

    Item {
        id: gameContent

        anchors.fill: parent

        Rectangle {
            anchors.fill: title
            color: colors[boxesModel.currentPlayer]
            opacity: 0.2
        }

        Label {
            id: title
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            text: "Player " + boxesModel.currentPlayer + " " + boxesModel.points[0] + " - " + boxesModel.points[1]
        }

        GridView {
            anchors.fill: parent
            interactive: false

            model: boxesModel.tiles
            /// Change logic so it's always an square
            cellHeight: parent.height / boxesModel.rows
            cellWidth: parent.width / boxesModel.columns
            delegate: Item {
                id: itemDelegate

                height: GridView.view.cellHeight
                width: GridView.view.cellWidth

                //color: mazeModel.inFrontier.indexOf(modelData) !== -1 ? "#2ecc71" : (mazeModel.inMaze.indexOf(modelData) !== -1 ? "#ecf0f1" : "#bdc3c7")

                //            Label {
                //                anchors.centerIn: parent
                //                text: modelData.activeWalls
                //            }

                //            MouseArea {
                //                anchors.fill: parent

                //                enabled: parent.color != "#ecf0f1"
                //                onClicked: mazeModel.generateMaze(modelData)
                //            }

                //            Rectangle {
                //                anchors.fill: parent
                //                border.color: "#3498db"
                //                border.width: 1
                //                opacity: 0.15
                //            }

                Rectangle {
                    id: upBar
                    anchors {
                        top: parent.top
                        horizontalCenter: parent.horizontalCenter
                    }

                    height: 0
                    width: parent.width * 0.1

                    visible: modelData.activeWalls & Tile.UpWall

                    onVisibleChanged: {
                        color = colors[boxesModel.currentPlayer]
                        animationUp.restart()
                    }

                    NumberAnimation { id: animationUp; target: upBar; properties: "height"; from: 0; to: itemDelegate.height / 2; duration: animationDuration }
                }

                Rectangle {
                    id: downBar
                    anchors {
                        bottom: parent.bottom
                        horizontalCenter: parent.horizontalCenter
                    }

                    height: 0
                    width: parent.width * 0.1

                    visible: modelData.activeWalls & Tile.DownWall

                    onVisibleChanged: {
                        color = colors[boxesModel.currentPlayer]
                        animationDown.restart()
                    }

                    NumberAnimation { id: animationDown; target: downBar; properties: "height"; from: 0; to: itemDelegate.height / 2; duration: animationDuration }
                }

                Rectangle {
                    id: leftBar

                    anchors {
                        left: parent.left
                        verticalCenter: parent.verticalCenter
                    }

                    width: 0
                    height: parent.height * 0.1
                    color: "black"

                    visible: modelData.activeWalls & Tile.LeftWall

                    onVisibleChanged: {
                        color = colors[boxesModel.currentPlayer]
                        animationLeft.restart()
                    }

                    NumberAnimation { id: animationLeft; target: leftBar; properties: "width"; from: 0; to: itemDelegate.width / 2; duration: animationDuration }
                }

                Rectangle {
                    id: rightBar

                    anchors {
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                    }

                    width: 0
                    height: parent.height * 0.1
                    color: "black"

                    visible: modelData.activeWalls & Tile.RightWall

                    onVisibleChanged: {
                        color = colors[boxesModel.currentPlayer]
                        animationRight.restart()
                    }

                    NumberAnimation { id: animationRight; target: rightBar; properties: "width"; from: 0; to: itemDelegate.width / 2; duration: animationDuration }
                }

                MouseArea {
                    height: parent.height / 4
                    width: parent.width / 2.5

                    //                Rectangle { anchors.fill: parent; color: "green" }

                    anchors {
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                    }

                    enabled: !(modelData.activeWalls & Tile.RightWall)

                    onClicked: boxesModel.updateValue(index, Tile.RightWall)
                }

                MouseArea {
                    height: parent.height / 4
                    width: parent.width / 2.5

                    //                Rectangle { anchors.fill: parent; color: "yellow" }

                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                    }

                    enabled: !(modelData.activeWalls & Tile.LeftWall)

                    onClicked: boxesModel.updateValue(index, Tile.LeftWall)
                }

                MouseArea {
                    height: parent.height / 2.5
                    width: parent.width / 4

                    //                Rectangle { anchors.fill: parent; color: "blue" }

                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        top: parent.top
                    }

                    enabled: !(modelData.activeWalls & Tile.UpWall)

                    onClicked: boxesModel.updateValue(index, Tile.UpWall)
                }

                MouseArea {
                    height: parent.height / 2.5
                    width: parent.width / 4

                    //                Rectangle { anchors.fill: parent; color: "purple" }

                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        bottom: parent.bottom
                    }

                    enabled: !(modelData.activeWalls & Tile.DownWall)

                    onClicked: boxesModel.updateValue(index, Tile.DownWall)
                }

                Rectangle {
                    height: parent.height > parent.width ? parent.width * 0.15 : parent.height * 0.15
                    width: height
                    anchors.centerIn: parent

                    radius: height * 1.5
                    color: "black"
                    antialiasing: true
                }
            }

            GridView {
                anchors.centerIn: parent

                height: parent.height - parent.cellHeight + 1
                width: parent.width - parent.cellWidth + 1

                cellHeight: parent.cellHeight
                cellWidth: parent.cellWidth

                interactive: false

                model: boxesModel.owners.length
                delegate: Item {
                    height: GridView.view.cellHeight
                    width: GridView.view.cellWidth

                    visible: boxesModel.owners[index]

                    Rectangle {
                        anchors.centerIn: parent
                        width: parent.width * 0.92
                        height: parent.height * 0.92
                        color: colors[boxesModel.owners[index]]
                        opacity: 0.8
                    }

                    Label {
                        anchors.centerIn: parent

                        text: boxesModel.owners[index]
                        color: "white"
                    }
                }
            }
        }
    }


    Item {
        id: winIndicator

        /// TODO: animate

        anchors.fill: parent
        visible: false

        onVisibleChanged: {
            if (visible)
                backgroundAnimation.restart()
            else
                winBackground.x = width
        }

        Rectangle {
            color: "white"
            anchors.fill: _FastBlur
        }

        FastBlur {
            id: _FastBlur

            anchors.fill: parent
            radius: 100
            opacity: 0.50
            source: ShaderEffectSource {
                sourceItem: gameContent
//                sourceRect: Qt.rect(0,0,root.width,200)
            }
        }

        Rectangle {
            id: winBackground

            anchors {
                verticalCenter: parent.verticalCenter; verticalCenterOffset: - (parent.height / 3) / 2
            }

            height: parent.height / 3
            width: parent.width
            x: parent.width

            NumberAnimation { id: backgroundAnimation; target: winBackground; properties: "x"; from: winIndicator.width; to: 0; duration: 800; easing.type: Easing.InOutQuad }

            Label {
                id: winLabel

                anchors.centerIn: parent
                color: "white"
            }
        }

        MouseArea {
            anchors.fill: parent

            enabled: parent.visible

            /// TODO: restart game, show UI to ask size
            onClicked: {
                boxesModel.resetGame()
                parent.visible = false
                console.log("RESTART GAME")
            }
        }
    }
}
