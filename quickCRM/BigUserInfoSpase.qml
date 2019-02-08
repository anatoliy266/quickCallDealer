import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import Qt.labs.calendar 1.0
import QtQuick.Controls.Universal 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Item {
    id: bigUserInfoItem
    parent: userInfoInLineRect
    width: parent.width
    height: parent.height

    Rectangle {
        id: userInfoRect
        width: userInfoInLineRect.width
        height: userInfoInLineRect.height

        Rectangle {
            id: userCompRect
            width: 360
            height: 200
            implicitHeight: 20
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            Label {
                id: userNameLabel
                text: "UserName"
                font.pixelSize: 24
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                id: userCompStatDealer
                width: (parent.width-40)/3
                height: (parent.width-40)/3
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 15
                color: "silver"
                radius: 2
            }

            Rectangle {
                id: userCompCalls
                width: (parent.width-40)/3
                height: (parent.width-40)/3
                color: "silver"
                anchors.right: userCompStatDealer.left
                anchors.rightMargin: 10
                anchors.verticalCenter: userCompStatDealer.verticalCenter
                radius: 2
            }

            Rectangle {
                id: userCompHistory
                width: (parent.width-40)/3
                height: (parent.width-40)/3
                color: "silver"
                anchors.left: userCompStatDealer.right
                anchors.leftMargin: 10
                anchors.verticalCenter: userCompStatDealer.verticalCenter
                radius: 2
            }
        }

        Rectangle {
            id: rightInLineRect
            width: userCompRect.height
            height: userCompRect.height
            anchors.verticalCenter: userCompRect.verticalCenter
            anchors.right: userCompRect.left
            anchors.rightMargin: 15
            radius: 3
            color: "silver"
        }

        Rectangle {
            id: leftInLineRect
            width: userCompRect.height
            height: userCompRect.height
            anchors.verticalCenter: userCompRect.verticalCenter
            anchors.left: userCompRect.right
            anchors.leftMargin: 15
            radius: 3
            color: "silver"
        }
    }
}
