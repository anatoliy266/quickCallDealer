import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import Qt.labs.calendar 1.0
import QtQuick.Controls.Universal 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

// This is available in all editors.

Item {
    id: mainWindowItem
    parent: generalRect
    width: parent.width
    height: parent.height
    x: parent.x
    y: parent.y
    opacity: 0.0


    Connections {
        id: onUserNumSetted
        target: dtControl
        onNumChanged: {
            dtControl.modelRequest(dtControl.num)
        }
        onCallsSucessSignal: {
            console.log("MainWin.qml: callsSucess signal from dtControl emitted")
            contentLoader.src === "Calls" ? dtControl.queueData("callsDealer", 0) : contentLoader.src === "History" ? dtControl.queueData("callsDealer", 1) : contentLoader.src === "Waitforcalls" ? dtControl.queueData("callsDealer", 0) : contentLoader.src === "Waitforhistory" ? dtControl.queueData("callsDealer", 1) : dtControl.queueData("callsDealer", 1)
        }
        onCModSucessSignal: {
            console.log("cSucess signal emited")
            contentLoader.source = "/content/CallsContent.qml"
            contentLoader.src = "Calls"
        }
        onHModSucessSignal: {
            console.log("HSucess signal emited")
            contentLoader.source = "/content/HistoryContent.qml"
            contentLoader.src = "History"
        }
        onHModNYSignal: {
            console.log("nothing signal emited")
            contentLoader.source = "/content/WaitFor.qml"
            contentLoader.src = "Waitforhistory"
        }
        onCModNYSignal: {
            console.log("nothing signal emited")
            contentLoader.source = "/content/WaitFor.qml"
            contentLoader.src = "Waitforcalls"
        }
    }

    Rectangle {
        id: mainWindowRect
        width: parent.width
        height: parent.height
        x: parent.x
        y: parent.y

        Image {
            id: bgMainWinImage
            anchors.fill: parent
            source: "fb.jpg"
            opacity: 0.1
        }

        Popup {
            id: menuPopup
            width: parent.width/5
            height: parent.height-20
            focus: true
            background: Rectangle {
                width: menuPopup.width
                height: menuPopup.height
            }
            contentItem: Item {
                id: popupItem
                Rectangle {
                    id: popupRect
                    width: menuPopup.width
                    height: menuPopup.height

                    Rectangle {
                        id: popupVerticalSpaser
                        width: 1
                        height: parent.height-20
                        color: "black"
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Rectangle {
                        id: popupIconRect
                        width: 40
                        height: 40
                        anchors.top: parent.top
                        anchors.right: parent.right
                        anchors.rightMargin: -2

                        Image {
                            id: popupIcon
                            anchors.fill: parent
                            source: "menu_icon.png"
                        }

                        MouseArea {
                            id: popupEvent
                            anchors.fill: parent
                            onClicked: menuPopup.close()
                        }
                    }

                    Rectangle {
                        id: userNameRect
                        width: parent.width-popupIconRect.width
                        height: 40
                        anchors.top: parent.top
                        anchors.left: parent.left

                        Label {
                            id: userNameLb
                            anchors.centerIn: parent
                            text: dtControl.user
                            font.pixelSize: 16
                        }
                    }

                    Rectangle {
                        id: popupSpaser1
                        width: parent.width-20
                        height: 1
                        color: "black"
                        anchors.top: userNameRect.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Rectangle {
                        id: callsMenuRect
                        width: parent.width -10
                        height: 25
                        anchors.top: popupSpaser1.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.topMargin: 5

                        Label {
                            id: callsMenuLabel
                            anchors.centerIn: parent
                            text: "Calls"
                            font.pixelSize: 16
                        }

                        MouseArea {
                            id: callsMenuRectEvent
                            anchors.fill: parent
                            onClicked: {
                                cMod.queueData("callsDealer", 0)
                                menuPopup.close()
                            }
                        }
                    }

                    Rectangle {
                        id: historyMenuRect
                        width: parent.width -10
                        height: 25
                        anchors.top: callsMenuRect.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.topMargin: 5

                        Label {
                            id: historyMenuLabel
                            anchors.centerIn: parent
                            text: "History"
                            font.pixelSize: 16
                        }

                        MouseArea {
                            id: historyMenuRectEvent
                            anchors.fill: parent
                            onClicked: {
                                cMod.queueData("callsDealer", 1)
                                menuPopup.close()
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            id: menuIconRect
            width: 40
            height: 40
            x: parent.x+20
            y: 10
            z: 1

            Image {
                id: menuIcon
                anchors.fill: parent
                source: "menu_icon.png"
            }

            MouseArea {
                id: menuEvent
                anchors.fill: parent
                onClicked: menuPopup.open()
            }
        }

        Rectangle {
            id: userInfoInLineRect
            width: parent.width
            height: 200
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            radius: 3
            //user info space
            Loader {
                id: userInfoLoader
                anchors.fill: parent
                source: "/mainwin/SmallUserInfoSpase.qml"
            }
        }

        Rectangle {
            id: showHideButton
            width: userInfoInLineRect.width/6-40
            height: 10
            radius: 5
            color: "silver"
            anchors.top: userInfoInLineRect.bottom
            anchors.horizontalCenter: userInfoInLineRect.horizontalCenter
            anchors.topMargin: 10

            MouseArea {
                id: showHideEvent
                anchors.fill: parent
                onClicked: {
                    //userInfoInLineRect.height === 200 ? changeToSmall() : changeToBig()
                }
            }
        }

        Rectangle {
            id: contentSpase
            width: parent.width-60
            height: parent.height/3*2
            anchors.top: userInfoInLineRect.bottom
            anchors.horizontalCenter: userInfoInLineRect.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.topMargin: 30
            color: "transparent"
            clip: true
            radius: 3

            Loader {
                id: contentLoader
                property string src: "Loading"
                anchors.fill: parent
                source: "/content/Loading.qml"
            }
        }
    }

    PropertyAnimation {
        id: mainWinAnim
        target: mainWindowItem
        property: "opacity"
        from: 0.0
        to: 1.0
        duration: 1000
        easing.type: Easing.InOutQuad
        running: true
        onStarted: {
            //dtControl.getCalls()
        }
    }

    PropertyAnimation {
        id: userInfoInLineRectAnim
        target: userInfoInLineRect
        property: "height"
        from: userInfoInLineRect.height
        to: 40
        duration: 700
        easing.type: Easing.InOutQuad
        running: true
    }
}
