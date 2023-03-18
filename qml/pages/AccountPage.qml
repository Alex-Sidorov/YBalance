import QtQuick 2.0
import QtQuick.Controls 2.0

import "../widgets" as Widgets

Item {
    id:root

    width: parent.width
    height: parent.height

    property int sizeItemAccount: 50

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
                }
            }
        }
    }




}
