import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import Qt.labs.calendar 1.0
import QtQuick.Controls.Universal 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Item {
    id: waitForItem
    parent: contentSpase
    width: parent.width
    height: parent.height

    Rectangle {
        id: waitForRect
        width: contentSpase.width
        height: contentSpase.height
        color: "transparent"

        Label {
            id: waitForLabel
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            font.pixelSize: 16
            text: "Waiting for new calls..."
        }
    }
}
