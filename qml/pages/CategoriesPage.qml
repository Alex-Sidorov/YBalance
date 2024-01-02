import QtQuick 2.12
import QtQuick.Controls 2.12

import "../widgets" as Widgets

Item {

    id:root

    width: parent.width
    height: parent.height


    property bool isIncome: false

    Rectangle {
        anchors.fill: parent

        color: "#635e5d"

        Widgets.CustomButton {
            width: 50
            height: 30
            onClicked: {
                isIncome = !isIncome
            }
        }

        SwipeView {
            currentIndex: isIncome
            anchors.fill: parent
            anchors.topMargin: 30

            Rectangle {
                color: "transparent"

                GridView {
                    anchors.fill: parent
                    model: 10

                    delegate: Rectangle{
                        width: 50
                        height: 50
                        color: "red"
                        radius: 10
                    }
                }
            }

            Rectangle {
                color: "transparent"

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: "inIncome == true"
                }
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
