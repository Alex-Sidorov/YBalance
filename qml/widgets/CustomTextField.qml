import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: control

    width: 800
    height: 76

    property int inputWidth: 480

    property bool isWarning: false

    property int fontSize: 36
    property int radius: 10
    property bool visibleLabel: true
    property string label: ""
    property string text: ""
    property string placeholder: ""
    property alias labelFont: label.font.family
    property alias readOnly: textField.readOnly
    property color labelColor: "white"
    property color inputText: control.readOnly ? "white" : labelColor
    property color inputBackground: control.readOnly ? "black" : "#e7e8e6"

    property alias input: textField

    signal editingFinished(string text)
    signal editing(string text)

    Text {
        id: label
        text: control.label

        font.pixelSize: control.fontSize
        color: control.labelColor

        visible: visibleLabel

        anchors.left: control.left
        anchors.verticalCenter: control.verticalCenter
    }

    Rectangle {
        id: textInput

        radius: control.radius
        color: inputBackground

        width: control.inputWidth
        height: control.height
        anchors.right: control.right

        border.width: 2
        border.color: isWarning ? "red" : "transparent"

        TextField {
            id: textField
            leftPadding: 24
            rightPadding: 24

            placeholderText: control.placeholder
            text: control.text

            width: textInput.width
            anchors.left: textInput.left
            anchors.verticalCenter: textInput.verticalCenter

            font.pixelSize: control.fontSize - 2
            color: inputText

            selectByMouse: true

            onTextChanged: {
                control.text = text
                control.editing(text)
            }

            onEditingFinished: {
                control.editingFinished(text)
            }

            KeyNavigation.tab: textField

            background: Rectangle {
                color: "transparent"
            }
        }
    }
}
