import QtQuick 2.12
import QtQuick.Controls 2.12

import AccountType 1.0

import "../widgets" as Widgets

Popup {
    id: root

    property int accountType: AccountType.NONE

    anchors.centerIn: parent
    width: parent.width * 0.6
    height: parent.height * 0.8

    modal: true

    onClosed: {
        nameField.text = ""
        amountField.text = ""
    }

    background: Rectangle {
        radius: 10

        Column {

            spacing: 20

            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10

            Row {

                Widgets.CustomTextField {
                    id: nameField

                    fontSize: 15

                    width: root.width * 0.8
                    height: root.height * 0.1
                    inputWidth: width * 0.78


                    radius: 5
                    label: "Name"
                    labelColor: "#635e5d"
                }

                Rectangle {
                    color: "transparent"
                    width: root.width * 0.05
                    height: 1

                }

                Rectangle {
                    width: height
                    height: root.height * 0.1
                }
            }



            Widgets.CustomComboBox{
                id: type

                listOptions: ["CASH", "CARD", "DEBT", "SAVING"]

                index: accountType - 1

                fontSize: 15

                width: root.width * 0.935
                height: root.height * 0.1
                inputWidth: width * 0.82

                radius: 5
                label: "Type"
                labelColor: "#635e5d"
            }

            Widgets.CustomTextField {
                id: amountField

                fontSize: 15

                width: root.width * 0.935
                height: root.height * 0.1
                inputWidth: width * 0.82

                input.validator : RegExpValidator { regExp : /[1-9]\d*\.?\d*/ }
                input.inputMethodHints: Qt.ImhFormattedNumbersOnly

                radius: 5
                label: "Amount"
                labelColor: "#635e5d"
            }

            Widgets.CustomComboBox{
                id: currency

                fontSize: 15

                listOptions: currencyStorage.getCurrencyList()

                width: root.width * 0.935
                height: root.height * 0.1
                inputWidth: width * 0.82

                radius: 5
                label: "Currency"
                labelColor: "#635e5d"
            }
        }

        color: "#c5c9c3"

        Widgets.CustomButton {
            id: closeButton

            text: "Close"
            textSize: 20

            color: "#635e5d"

            width: parent.width * 0.3
            height: parent.height * 0.15

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

            enabled: accountType > 0
                     && amountField.text.length > 0
                     && nameField.text.length > 0

            width: parent.width * 0.3
            height: parent.height * 0.15

            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 10

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            onClicked: {
                accountsModel.addAccount(nameField.text, currency.value, amountField.text, "", type.index + 1)
                close()
            }
        }

    }
}
