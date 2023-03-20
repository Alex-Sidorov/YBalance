import QtQuick 2.12
import QtQuick.Controls 2.12

import "../widgets" as Widgets
import "../popups" as Popups

Item {
    id:root

    width: parent.width
    height: parent.height

    property int sizeItemAccount: 60

    ScrollView {
        anchors.fill: parent

        contentHeight: itemsArea.height
        contentWidth: parent.width

        background: Rectangle {
            color: "#635e5d"
        }

        clip: true

        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        Rectangle {
            id: itemsArea

            width: childrenRect.width
            height: childrenRect.height

            color: "transparent"

            Column {
                width: childrenRect.width
                height: childrenRect.height

                Widgets.AccountTypeTitle {
                    title: "CARDS"
                    visible: cards.count > 0
                }

                ListView {
                    id: cards

                    clip: true

                    interactive: false

                    property int count: model.count

                    model: accountsModel.getCardAccounts()
                    width: root.width
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

                    interactive: false

                    property int count: model.count

                    model: accountsModel.getCashAccounts()
                    width: root.width
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

                    property int count: model.count

                    interactive: false

                    model: accountsModel.getSavingsAccounts()
                    width: root.width
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

                    interactive: false

                    property int count: model.count

                    model: accountsModel.getDebtAccounts()
                    width: root.width
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

                    width: root.width
                    height: 100

                    Widgets.ColoredIcon {
                        id: icon

                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.left: parent.left
                        anchors.leftMargin: 5

                        imageHeight: 50
                        imageWidth: 50

                        source: "qrc:/icons/plus.svg"
                        color: "#c5c9c3"
                    }

                    Text {
                       id: text
                       anchors.verticalCenter: icon.verticalCenter
                       anchors.left: icon.right
                       anchors.leftMargin: 10

                       font.pixelSize: 15

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

    Popups.AccountCreator {
        id: accountCreator

    }

    Popups.AddAccountPopup {
        id: addAccountPopup

        onCreateAccount: {
            accountCreator.accountType = type
            accountCreator.open()
        }
    }

    Popups.AccountOptions {
        id: drawer
    }

}
