import QtQuick 2.12
import QtQuick.Controls 2.12

Item {

    id:root

    width: parent.width
    height: parent.height



    ScrollView {
        anchors.fill: parent

        ListView {
            model: 200
            delegate: ItemDelegate {
                text: "Item " + index

                required property int index
            }
        }
    }


    /*Rectangle {
        anchors.fill: parent
        color: "Red"

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: "Categories"
        }
    }*/

}
