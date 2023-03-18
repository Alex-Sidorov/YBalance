import QtQuick 2.0

Item {
    id:root

    width: parent.width
    height: parent.height

    Rectangle {
        anchors.fill: parent
        color: "Red"

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: "Transaction"
        }
    }
}
