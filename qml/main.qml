import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import "pages" as Pages

Window {
    id: mainRoot

    width: 640
    height: 480
    visible: true
    title: qsTr("YBalance")

    TabBar {
        id: bar
        width: parent.width
        anchors.bottom: parent.bottom

        TabButton {
            text: qsTr("Accounts")
            font.pixelSize: 15
        }
        TabButton {
            text: qsTr("Categories")
            font.pixelSize: 15
        }
        TabButton {
            text: qsTr("Transaction")
            font.pixelSize: 15
        }
    }

    StackLayout {
        anchors.top: parent.top
        anchors.bottom: bar.top

        width: parent.width
        currentIndex: bar.currentIndex

        Pages.AccountPage {
            id: accountPage
        }

        Pages.CategoriesPage {
            id: categoriesPage

        }

        Pages.TransactionPage {
            id: transactionPage
        }
    }
}
