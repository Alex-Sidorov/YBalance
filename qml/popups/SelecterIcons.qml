import QtQuick 2.12
import QtQuick.Controls 2.12
import Qt.labs.folderlistmodel 2.3

import "../widgets" as Widgets

Popup {
    id: root

    anchors.centerIn: parent
    width: parent.width
    height: parent.height

    signal selected(image: string)

    modal: true

    background: Rectangle {
        radius: 10
    }

    Rectangle {
        height: 40
        width: 40
        color: "transparent"

        z: 1

        anchors.right: parent.right
        anchors.rightMargin: -5
        anchors.top: parent.top

        Widgets.ColoredIcon {
            imageHeight: parent.height
            imageWidth: parent.width

            color: "black"

            source: "qrc:/icons/close.svg"
        }

        MouseArea {
            anchors.fill: parent
            onReleased: {
                close()
            }
        }
    }



    GridView {
       x: parent.width * 0.1

       width: parent.width
       height: parent.height

       clip: true


       FolderListModel {
            id: folderModel
            folder: "qrc:/icons/accounts_icon"
            nameFilters: ["*"]
        }

        Component {
            id: fileDelegate

            Rectangle {
                width: 60
                height: 60

                border.color: "grey"
                border.width: 1
                radius: 5

                Widgets.ColoredIcon {
                    id: icon

                    imageHeight: parent.height * 0.9
                    imageWidth: parent.width * 0.9

                    anchors.centerIn: parent

                    color: "black"

                    source: "qrc" + filePath
                }

                MouseArea {
                    anchors.fill: parent

                    onReleased: {
                        selected(icon.source)
                        close()
                    }
                }
            }
        }

        model: folderModel
        delegate: fileDelegate
    }
}
