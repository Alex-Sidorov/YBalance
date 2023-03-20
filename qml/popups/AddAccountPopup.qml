import QtQuick 2.12
import QtQuick.Controls 2.12

import AccountType 1.0

import "../widgets" as Widgets

Popup {
    id: root

    property int selectedItem: AccountType.CASH

    signal createAccount(int type)

    anchors.centerIn: parent
    width: parent.width * 0.6
    height: parent.height * 0.6

    modal: true

    onClosed: {
        selectedItem = AccountType.CASH
        first.checked = true
    }

    background: Rectangle {
        radius: 10

        color: "#c5c9c3"

        ButtonGroup {
            id: group
            buttons: column.children
        }

        Column {
            id: column

            RadioButton {
                id: first
                checked: true
                text: qsTr("Cash")
                font.pixelSize: 15

                onCheckedChanged: {
                    if(checked)
                        root.selectedItem = AccountType.CASH
                }
            }

            RadioButton {
                text: qsTr("Card")
                font.pixelSize: 15

                onCheckedChanged: {
                    if(checked)
                        root.selectedItem = AccountType.CARD
                }
            }

            RadioButton {
                text: qsTr("Debt")
                font.pixelSize: 15

                onCheckedChanged: {
                    if(checked)
                        root.selectedItem = AccountType.DEBT
                }
            }

            RadioButton {
                text: qsTr("Saving")
                font.pixelSize: 15

                onCheckedChanged: {
                    if(checked)
                        root.selectedItem = AccountType.SAVINGS
                }
            }
        }

        Widgets.CustomButton {
            id: closeButton

            text: "Close"
            textSize: 20

            color: "#635e5d"

            width: parent.width * 0.3
            height: parent.height * 0.2

            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 10

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            onReleased: {
                close()
            }
        }

        Widgets.CustomButton {
            id: okButton

            text: "Ok"
            textSize: 20

            color: "#635e5d"

            width: parent.width * 0.3
            height: parent.height * 0.2

            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 10

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            onClicked: {
                root.createAccount(root.selectedItem)
                close()
            }
        }

    }
}
