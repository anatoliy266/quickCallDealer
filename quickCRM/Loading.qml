import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import Qt.labs.calendar 1.0
import QtQuick.Controls.Universal 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Item {
    id: loadingItem
    parent: contentSpase
    width: parent.width
    height: parent.height

    Rectangle {
        id: loadingRect
        width: contentSpase.width
        height: contentSpase.height
        color: "transparent"

        BusyIndicator {
            id: loadingIndicator
            anchors.centerIn: parent
            width: 80
            height: 80
            running: true
        }
    }
}
