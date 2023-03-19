import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id: button

    text: ""
    property alias image: img.source
    property string size: "normal"

    property color borderColor: "transparent"
    property int borderWidth: 0
    property color textColor: "white"
    property color color: "black"
    property alias borderRadius: bg.radius
    property color pressedColor: Qt.darker(color, 1.4)
    property bool shadow: true
    property int contentOffset: 0
    property int contentRight: txt.x + txt.width
    property int textSize: size == 'small' ? 31 : size == 'big' ? 36 : 36

    opacity: enabled ? 1 : 0.6

    implicitWidth: size == 'small' ? 221 : size == 'big' ? 415 : 256
    implicitHeight: size == 'small' ? 73 : size == 'big' ? 107 : 84

    contentItem: Item {
        Item {
            width: childrenRect.width
            height: parent.height

            anchors.centerIn: parent
            anchors.horizontalCenterOffset: button.contentOffset

            ColoredIcon {
                id: img
                color: textColor
                opacity: button.down ? 0.75 : 1
                anchors.verticalCenter: parent.verticalCenter

                anchors.left: parent.left
            }

            Text {
                id: txt
                text: button.text
                font.pixelSize: button.textSize
                opacity: button.down ? 0.75 : 1
                color: button.textColor
                anchors.left: img.right
                anchors.leftMargin: (text != "") && (img.width != 0) ? 16 : 0
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    background: Rectangle {
        id: bg
        radius: 20
        border.width: borderWidth
        border.color: button.borderColor
        color: button.down ? button.pressedColor : button.color
    }
}
