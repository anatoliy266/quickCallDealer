import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import Qt.labs.calendar 1.0
import QtQuick.Controls.Universal 2.3
import QtQuick.Controls.Material 2.3

Item {
    id: preLoadItem
    parent: loginPwdRect
    width: parent.width
    height: parent.height

    Connections {
        target: dtControl

        onEstablishedConnectionSignal: {
            preLoadLabel.text = "Connected"
            dtControl.orgsRequest()
        }
        onFailedConnectionSignal: {
            preLoadLabel.text = "Connection failed, check LAN"
        }
        onSendOToServer: {
            preLoadLabel.text = "waiting for organizations info"
        }
        onSendQToServer: {
            preLoadLabel.text = "waiting for query type info"
        }
        onSendToServer: {
            preLoadLabel.text = "waiting for users info"
        }
        onUsersSucessSignal: {
            preLoadLabel.text = "users info prepared"
            preLoadRectAnim.running = true
        }
        onQuerysSucessSignal: {

            dtControl.queueData("query_type", -1)

        }
        onOrgsSucessSignal: {
            dtControl.queueData("orgsPhones", -1)
        }
        onOModSucessSignal: {
            preLoadLabel.text = "Organizations info prepared"

            dtControl.querysRequest()
        }
        onQModSucessSignal: {
            preLoadLabel.text = "Query types info prepared"
            dtControl.usersRequest()
        }
    }

    Rectangle {
        id: preLoadRect
        width: parent.width
        height: parent.height
        x:parent.x
        y: parent.y
        color: "transparent"

        Label {
            id: preLoadLabel
            anchors.centerIn: parent
            text: "Connect to host..."
            font.pixelSize: 16
        }
    }

    PropertyAnimation {
        id: preLoadRectAnim
        target: preLoadRect
        property: "opacity"
        from: 1.0
        to: 0.0
        easing.type: Easing.InOutQuad
        duration: 500
        running: false
        onStopped: {
            dtControl.preloadSucess()
        }
    }
}
