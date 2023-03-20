import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import QtQml 2.12

Item {
    id: control

    width: 800
    height: 76


    property int inputWidth: 480

    property bool isWarning: false

    property string label: "label"
    property alias listOptions: combo.model
    property alias index: combo.currentIndex
    property var value
    property string setValue: ""
    property int fontSize: 36
    property int radius: 10

    property bool highlighted: true
    property bool readOnly: false
    property color labelColor: "white"
    property color inputText: control.readOnly ? "white" : labelColor
    property color inputBackground: control.readOnly ? "black" : "#e7e8e6"

    property color itemText: inputText
    property color itemColor: inputBackground
    signal activate(int index)

    enabled: !readOnly

    Text {
        id: label
        text: control.label

        font.pixelSize: control.fontSize
        color: control.labelColor

        anchors.left: control.left
        anchors.verticalCenter: control.verticalCenter
    }

    ComboBox {
        id: combo
        model: ["First", "Second", "Third"]

        width: control.inputWidth
        height: control.height

        anchors.right: control.right
        anchors.verticalCenter: parent.verticalCenter

        font.pixelSize: control.fontSize

        onCurrentIndexChanged: {
            value = model[currentIndex]
        }

        spacing: 16

        delegate: ItemDelegate {
            width: combo.width

            contentItem: Text {
                leftPadding: 16
                text: modelData
                color: inputText
                font: combo.font
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
            }
            highlighted: control.highlightedIndex === index
        }

        indicator: ColoredIcon {
            id: imgIndicator
            source: combo.popup.visible ? "qrc:/icons/combo_indicator_up.svg" : "qrc:/icons/combo_indicator_down.svg"
            color: inputText
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 16

            visible: !readOnly
        }

        contentItem: Text {
            leftPadding: 24
            rightPadding: combo.spacing

            text: combo.displayText
            font: combo.font
            color: inputText
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            radius: control.radius
            color: inputBackground

            border.width: 2
            border.color: isWarning ? themes.current.text_failure : "transparent"
        }

        popup: Popup {
            y: combo.height + 3
            width: combo.width
            topPadding: 30
            bottomPadding: 30
            leftPadding: 0
            rightPadding: 0

            contentItem: ListView {
                clip: true
                implicitHeight: contentHeight
                model: combo.popup.visible ? combo.delegateModel : null
                currentIndex: combo.highlightedIndex

                highlight: Rectangle {
                    color: inputBackground
                }
            }

            background: Rectangle {
                color: inputBackground
                radius: 8
                layer.enabled: true
                layer.effect: DropShadow {
                    transparentBorder: true
                    verticalOffset: 24
                    color: "#44000000"
                }
            }
        }

        onActivated: control.activate(index)

        function findIndex(value) {
            for(var i = 0; i < model.length; ++i) {
                if(model[i] === value)
                    return i;
            }
            return 0
        }

        Component.onCompleted: {
            if (control.setValue) {
                //currentIndex = indexOfValue(control.setValue)
                currentIndex = findIndex(control.setValue)
            }
        }
    }
}

