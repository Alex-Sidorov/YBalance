import QtQuick 2.12
import QtQuick.Controls 2.12

import "../widgets" as Widgets

Item {
    id:root

    width: parent.width
    height: parent.height

    property int sizeItemAccount: 50

    StackView {
        id: view

        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: "#635e5d"

            Column {
                anchors.fill: parent

                Widgets.AccountTypeTitle {
                    title: "CARDS"
                    visible: cards.count > 0
                }

                ListView {
                    id: cards

                    clip: true

                    property int count: model.rowCount()

                    model: accountsModel.getCashAccounts()
                    width: parent.width
                    height: count * sizeItemAccount

                    delegate: Widgets.DelegateAccount {
                        height: sizeItemAccount
                        item: model

                        isLast: index === cards.count - 1

                        onClicked: {
                            console.log(model.name)
                            drawer.open()
                        }
                    }
                }

                Widgets.AccountTypeTitle {
                    title: "CASH"
                    visible: cash.count > 0
                }

                ListView {
                    id: cash

                    clip: true

                    property int count: model.rowCount()

                    model: accountsModel.getCardAccounts()
                    width: parent.width
                    height: count * sizeItemAccount

                    delegate: Widgets.DelegateAccount {
                        height: sizeItemAccount
                        item: model

                        isLast: index === cash.count - 1

                        onClicked: {
                            console.log(model.name)
                            drawer.open()
                        }
                    }
                }

                Widgets.AccountTypeTitle {
                    title: "SAVINGS"
                    visible: savings.count > 0
                }

                ListView {
                    id: savings

                    clip: true

                    property int count: model.rowCount()

                    model: accountsModel.getSavingsAccounts()
                    width: parent.width
                    height: count * sizeItemAccount

                    delegate: Widgets.DelegateAccount {
                        height: sizeItemAccount
                        item: model

                        isLast: index === savings.count - 1

                        onClicked: {
                            console.log(model.name)
                            drawer.open()
                        }
                    }
                }

                Widgets.AccountTypeTitle {
                    title: "DEBTS"
                    visible: debts.count > 0
                }

                ListView {
                    id: debts

                    clip: true

                    property int count: model.rowCount()

                    model: accountsModel.getDebtAccounts()
                    width: parent.width
                    height: count * sizeItemAccount

                    delegate: Widgets.DelegateAccount {
                        height: sizeItemAccount
                        item: model

                        isLast: index === debts.count - 1

                        onClicked: {
                            console.log(model.name)
                            drawer.open()
                        }
                    }
                }

                Rectangle {

                    color: "transparent"

                    width: parent.width
                    height: 50

                    Widgets.ColoredIcon {
                        id: icon

                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.left: parent.left
                        anchors.leftMargin: 5

                        source: "qrc:/icons/plus.svg"
                        color: "#c5c9c3"
                    }

                    Text {
                       id: text
                       anchors.verticalCenter: icon.verticalCenter
                       anchors.left: icon.right
                       anchors.leftMargin: 10

                       text: "Add account"
                       color: "#c5c9c3"
                    }

                    MouseArea {
                        anchors.fill: parent

                        onReleased: {
                            addAccountPopup.open()
                        }
                    }
                }
            }
        }
    }



    Widgets.AddAccountPopup {
        id: addAccountPopup

        onCreateAccount: {
            console.log(type)
            //view.push()
        }
    }

    Widgets.AccountOptions {
        id: drawer
    }

}
