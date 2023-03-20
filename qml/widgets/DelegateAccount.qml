import QtQuick 2.10

Rectangle {
    id: root

    width: parent.width

    property var item
    property bool isLast: false

    signal clicked

    color: "transparent"
    MouseArea {
        anchors.fill: parent

        onReleased: {
            root.clicked()
        }
    }

    Rectangle {
        id: icon

        width: height


        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        anchors.leftMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 10
    }

    Text {
       id: name
       text: item.name
       color: "white"

       font.pixelSize: 13

       anchors.left: icon.right
       anchors.top: icon.top

       anchors.leftMargin: 10
    }

    Text {
       id: amount
       text: item.amount
       color: "#7bcf61"

       font.bold: true
       font.pixelSize: 15

       anchors.left: name.left
       anchors.bottom: icon.bottom
    }

    Text {
       id: currency
       text: item.currency
       color: "#7bcf61"

       font.pixelSize: 15

       anchors.left: amount.right
       anchors.verticalCenter: amount.verticalCenter

       anchors.leftMargin: 10
    }

    Rectangle {
        height: 1
        color: "grey"

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.leftMargin: isLast ? 0 : 50
    }
}
