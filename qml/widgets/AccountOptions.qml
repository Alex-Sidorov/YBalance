import QtQuick 2.12
import QtQuick.Controls 2.12

Drawer {
    id: drawer
    width: parent.width
    height: parent.height * 0.4

    edge: Qt.BottomEdge

    background: Rectangle {
        anchors.fill: parent

        color: "transparent"

        Rectangle {
            anchors.centerIn: parent
            color: "transparent"

            radius: 10

            width: parent.width * 0.8
            height: parent.height * 0.8

            Rectangle {
                id: header
                width: parent.width
                height: parent.height * 0.3

                color: "green"
            }

            Rectangle {
                width: parent.width
                height: parent.height * 0.6

                anchors.top: header.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                color: "#e7e8e6"
            }

        }
    }
}
