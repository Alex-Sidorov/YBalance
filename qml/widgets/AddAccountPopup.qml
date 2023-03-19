import QtQuick 2.12
import QtQuick.Controls 2.12

Popup {
    id: root

    property int selectedItem: 1
    signal createAccount(int type)

    anchors.centerIn: parent
    width: parent.width * 0.6
    height: parent.height * 0.6

    modal: true

    onClosed: {
        selectedItem = 1
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

                onCheckedChanged: {
                    if(checked)
                        root.selectedItem = 1
                }
            }

            RadioButton {
                text: qsTr("Card")

                onCheckedChanged: {
                    if(checked)
                        root.selectedItem = 2
                }
            }

            RadioButton {
                text: qsTr("Debt")

                onCheckedChanged: {
                    if(checked)
                        root.selectedItem = 3
                }
            }

            RadioButton {
                text: qsTr("Saving")

                onCheckedChanged: {
                    if(checked)
                        root.selectedItem = 4
                }
            }
        }

        CustomButton {
            id: closeButton

            text: "Close"

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

        CustomButton {
            id: okButton

            text: "Ok"

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
