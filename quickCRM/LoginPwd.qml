import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import Qt.labs.calendar 1.0
import QtQuick.Controls.Universal 2.3
import QtQuick.Controls.Material 2.3

Item {
    id: loginPwdItem
    parent: loginPwdRect
    width: parent.width
    height: parent.height

    Connections {
        id: uModPrepareSucessConnection
        target: dtControl
        onUModSucessSignal: {
            loginPwdSpaceRectAnim.running = true
        }
    }

    Rectangle {
        id: loginPwdSpaceRect
        width: parent.width
        height: parent.height
        x: parent.x
        y: parent.y
        color: "transparent"
        opacity: 0.0

        Rectangle {
            id: btnRect
            width: loginPwdSpaceRect.width
            height: loginPwdSpaceRect.height/6-1
            anchors.horizontalCenter: loginPwdSpaceRect.horizontalCenter
            anchors.bottom: loginPwdSpaceRect.bottom
            color: "transparent"

            Rectangle {
                id: btn
                width: parent.width/3*2
                height: parent.height/3*2
                color: "white"
                opacity: 0.9
                radius: 5
                anchors.centerIn: parent


                Label {
                    id: btnLabel
                    anchors.centerIn: parent
                    text: qsTr("Login")
                    font.pixelSize: 12
                    opacity: 1.0
                }

                MouseArea {
                    id: loginBtnMouseEvent
                    anchors.fill: parent
                    onClicked: {
                        ///some event
                        pwdInputSpase.text !== "" ? loginInputSpase.text !== "" ? uMod.authorization(loginInputSpase.text, pwdInputSpase.text) : console.log("Login aren't fill") : console.log("PWD aren't fill")
                    }
                }
            }
        }

        Rectangle {
            id: spaser2
            width: loginPwdSpaceRect.width-20
            height: 1
            color: "black"
            anchors.horizontalCenter: loginPwdSpaceRect.horizontalCenter
            anchors.bottom: btnRect.top
            opacity: 0.5

        }

        Rectangle {
            id: pwdRect
            width: loginPwdSpaceRect.width
            height: loginPwdSpaceRect.height/4-1
            anchors.horizontalCenter: loginPwdSpaceRect.horizontalCenter
            anchors.bottom: spaser2.top
            color: "transparent"

            Label {
                id: pwdLabel
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                text: qsTr("PASSWORD")
                topPadding: 20
                font.pixelSize: 20
            }

            TextField {
                id: pwdInputSpase
                width: spaser1.width
                height: parent.height/2
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                selectByMouse: true
                bottomPadding: 2
                font.pixelSize: 18
                placeholderText: "Password"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                onAccepted: {
                    pwdInputSpase.text !== "" ? loginInputSpase.text !== "" ? uMod.authorization(loginInputSpase.text, pwdInputSpase.text) : loginInputSpase.focus = true : console.log("password aren't fill")
                }
            }
        }

        Rectangle {
            id: spaser1
            width: loginPwdSpaceRect.width-20
            height: 1
            color: "black"
            anchors.horizontalCenter: loginPwdSpaceRect.horizontalCenter
            anchors.bottom: pwdRect.top
            opacity: 0.5

        }

        Rectangle {
            id: loginRect
            width: loginPwdSpaceRect.width
            height: loginPwdSpaceRect.height/4-1
            anchors.horizontalCenter: loginPwdSpaceRect.horizontalCenter
            anchors.bottom: spaser1.top
            color: "transparent"

            Label {
                id: loginLabel
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                text: qsTr("USERNAME")
                topPadding: 20
                font.pixelSize: 20
            }

            TextField {
                id: loginInputSpase
                width: spaser1.width
                height: parent.height/2
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                selectByMouse: true
                bottomPadding: 2
                font.pixelSize: 18
                placeholderText: "Username"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                onAccepted: {
                    loginInputSpase.text !== "" ? pwdInputSpase.text !== "" ? uMod.authorization(loginInputSpase.text, pwdInputSpase.text) : pwdInputSpase.focus = true : console.log("username aren't fill")
                }
            }
        }
    }

    PropertyAnimation {
        id: loginPwdSpaceRectAnim
        target: loginPwdSpaceRect
        property: "opacity"
        from: 0.0
        to: 1.0
        duration: 500
        running: false
        easing.type: Easing.InOutQuad
    }
}
