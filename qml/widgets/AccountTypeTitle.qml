import QtQuick 2.0

Rectangle {
    width: 100
    height: 30

    property alias title: text.text

    color: "transparent"

    Text {
       id: text
       anchors.left: parent.left
       anchors.top: parent.top
       anchors.bottom: parent.bottom

       anchors.leftMargin: 10
       anchors.topMargin: 10
       anchors.bottomMargin: 20

       text: "CASH"
       color: "#c5c9c3"
    }
}
