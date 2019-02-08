import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import Qt.labs.calendar 1.0
import QtQuick.Controls.Universal 2.3
import QtQuick.Controls.Material 2.3

Item {
    id: authItem
    parent: generalRect
    width: parent.width
    height: parent.height
    x: parent.x
    y: parent.y
    opacity: 1.0

    Connections {
        id: authSucessConnection
        target: dtControl
        onAuthSucess: {
            changeAnim.running = true
        }
        onPreloadSucessSignal: {
            console.log("preload sucess signal emitted")
            loginLoader.source === "/LoginPwd.qml" ? console.log("nothing to do") : loginLoader.source = "/LoginPwd.qml"
            dtControl.queueData("users", -1)
        }
    }

    Connections {
        id: loginPwdShowConnection
        target: dtControl

    }

    Rectangle {
        id: authRect
        width: parent.width
        height: parent.height
        x: parent.x
        y: parent.y

        Image {
            id: authBgImage
            anchors.fill: parent
            source: "fb.jpg"
            opacity: 0.3
        }

        Rectangle {
            id: loginPwdRect
            width: 400
            height: 400
            x: authRect.x+authRect.width/2-200
            y: authRect.height/2-200
            color: "transparent"

            Loader {
                id: loginLoader
                anchors.fill: parent
                source: "/PreLoad.qml"
            }
        }

        Image {
            id: logoImage
            source: "phoneLogo.png"
            width: loginPwdRect.width
            height: loginPwdRect.width
            anchors.horizontalCenter: loginPwdRect.horizontalCenter
            y: loginPwdRect.y
        }

        ParallelAnimation {
            id: logoAmim
            running: true
            onStopped: {
                loginPwdRect.visible = true
                dtControl.init()
            }

            SequentialAnimation {
                id: logoRotAnim

                RotationAnimation {
                    id: rotation1
                    target: logoImage
                    from: 0
                    to: 15
                    duration: 50
                }

                RotationAnimation {
                    id: rotation2
                    target: logoImage
                    from: 15
                    to: -15
                    duration: 50
                }

                RotationAnimation {
                    id: rotation3
                    target: logoImage
                    from: -15
                    to: 0
                    duration: 50
                }

                RotationAnimation {
                    id: rotation4
                    target: logoImage
                    from: 0
                    to: 1
                    duration: 175
                }

                RotationAnimation {
                    id: rotation5
                    target: logoImage
                    from: 1
                    to: 0
                    duration: 175
                }

                RotationAnimation {
                    id: rotation6
                    target: logoImage
                    from: 0
                    to: 15
                    duration: 50
                }

                RotationAnimation {
                    id: rotation7
                    target: logoImage
                    from: 15
                    to: -15
                    duration: 50
                }

                RotationAnimation {
                    id: rotation8
                    target: logoImage
                    from: -15
                    to: 0
                    duration: 50
                }

                RotationAnimation {
                    id: rotation9
                    target: logoImage
                    from: 0
                    to: 1
                    duration: 175
                }

                RotationAnimation {
                    id: rotation10
                    target: logoImage
                    from: 1
                    to: 0
                    duration: 175
                }
            }

            NumberAnimation {
                id: logoWidthAnim
                target: logoImage
                property: "width"
                from: logoImage.width
                to: loginPwdRect.width/4
                duration: 1000
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: logoHeightAnim
                target: logoImage
                property: "height"
                from: logoImage.height
                to: loginPwdRect.height/4
                duration: 1000
                easing.type: Easing.InOutQuad
            }
        }

        Label {
            id: cLabel
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            text: qsTr("quickCRM, Russia, Irkutsk, King Anthony, MIT 3.0")
        }
    }

    PropertyAnimation {
        id: changeAnim
        target: authItem
        property: "opacity"
        from: 1.0
        to: 0.0
        duration: 1000
        easing.type: Easing.InOutQuad
        running: false
        onStopped: {
            generalLoader.source = "MainWindow.qml"
        }
    }
}
