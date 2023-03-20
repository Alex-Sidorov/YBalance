import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    property alias source: img.source
    property alias color: overlay.color

    property alias imageWidth: img.sourceSize.height
    property alias imageHeight: img.sourceSize.width

    width: childrenRect.width
    height: childrenRect.height

    Image {
        id: img
        source: ""
        visible: false
    }

    ColorOverlay {
        id: overlay
        source: img
        anchors.fill: img


    }
}
