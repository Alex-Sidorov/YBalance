import QtQuick 2.0
import QtQuick.Controls 2.0

Item {

    id:root

    width: parent.width
    height: parent.height



    Row {
       Button {
           onPressed: {
               mymodel.add()
           }
       }
       Button {
           onPressed: {
               mymodel.remove()
           }
       }
    }

    Rectangle {
        anchors.fill: parent
        color: "Red"

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: "Categories"
        }
    }

}
