import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import Qt.labs.calendar 1.0
import QtQuick.Controls.Universal 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Item {
    id: smallUserInfoSpaseItem
    parent: userInfoInLineRect
    width: parent.width
    height: parent.height

    Connections {
        target: dtControl
        onUsersSucessSignal: {
            dtControl.queueData("users", -1)
        }
        onUModSucessSignal: {
            inLineSmallList.model === uMod ? console.log("nothing") : inLineSmallList.model = uMod
        }
    }

    Rectangle {
        id: smallUserInfoSpaseRect
        width: userInfoInLineRect.width
        height: userInfoInLineRect.height

        Rectangle {
            id: userInfoSmallRect
            height: parent.height-8
            width: parent.width/3-15
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 4

            Label {
                id: userNameLabel
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: dtControl.user
                font.pixelSize: 18
            }

            Label {
                id: callsCountIntLabel
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                text: cMod.rowCount()
                font.pixelSize: 16
            }

            Label {
                id: callsCountLabel
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.right: callsCountIntLabel.left
                anchors.rightMargin: 10
                text: "Calls count"
                font.pixelSize: 16
            }


        }

        Rectangle {
            id: userStatDealerSmallRect
            height: parent.height-8
            width: parent.width/3-15
            anchors.top: parent.top
            anchors.right: userInfoSmallRect.left
            anchors.rightMargin: 5
            anchors.topMargin: 4

            Rectangle {
                id: callsSmallImSpase
                width: parent.height
                height: parent.height
                anchors.top: parent.top
                anchors.right: parent.right
                gradient: Gradient {
                    GradientStop {
                        position: 0.0
                        color: "white"
                    }

                    GradientStop {
                        position: 0.1
                        color: "silver"
                    }

                    GradientStop {
                        position: 0.2
                        color: "white"
                    }
                }

                Rectangle {
                    id: callsSmallRect
                    width: parent.height-10
                    height: parent.height-10
                    anchors.centerIn: parent

                    Image {
                        id: callsSmallImage
                        anchors.fill: parent
                        source: "/phone.png"
                    }
                }

                MouseArea {
                    id: callsSmallImSpaseEvent
                    anchors.fill: parent
                    onClicked: {
                        contentLoader.source = "/content/Loading.qml"
                        dtControl.queueData("callsDealer", 0)
                    }
                }
            }

            Rectangle {
                id: historySmallImSpase
                width: parent.height
                height: parent.height
                anchors.top: parent.top
                anchors.right: callsSmallImSpase.left
                gradient: Gradient {
                    GradientStop {
                        position: 0.0
                        color: "white"
                    }

                    GradientStop {
                        position: 0.1
                        color: "silver"
                    }

                    GradientStop {
                        position: 0.2
                        color: "white"
                    }
                }

                Rectangle {
                    id: historySmallRect
                    width: parent.height-10
                    height: parent.height-10
                    anchors.centerIn: parent
                    color: "green"

                    Image {
                        id: historySmallImage
                        anchors.fill: parent
                        source: "history.jpg"
                    }
                }

                MouseArea {
                    id: historySmallImSpaseEvent
                    anchors.fill: parent
                    onClicked: {
                        contentLoader.source = "/content/Loading.qml"
                        dtControl.queueData("callsDealer", 1)
                    }
                }
            }

            Rectangle {
                id: statSmallImSpase
                width: parent.height
                height: parent.height
                anchors.top: parent.top
                anchors.right: historySmallImSpase.left
                gradient: Gradient {
                    GradientStop {
                        position: 0.0
                        color: "white"
                    }

                    GradientStop {
                        position: 0.1
                        color: "silver"
                    }

                    GradientStop {
                        position: 0.2
                        color: "white"
                    }
                }

                Rectangle {
                    id: statSmallRect
                    width: parent.height-10
                    height: parent.height-10
                    anchors.centerIn: parent
                    color: "green"

                    Image {
                        id: statSmallImage
                        anchors.fill: parent
                        source: "stats.png"
                    }
                }

                MouseArea {
                    id: statSmallImSpaseEvent
                    anchors.fill: parent
                    onClicked: {
                        contentLoader.source = "/content/Loading.qml"
                    }
                }
            }
        }

        Rectangle {
            id: userInLineSmallRect
            height: parent.height-8
            width: parent.width/3-15
            anchors.top: parent.top
            anchors.left: userInfoSmallRect.right
            anchors.leftMargin: 5
            anchors.topMargin: 4

            Component {
                id: inLineSmallListComp

                Rectangle {
                    id: inLineSmallListItem
                    width: inLineSmallList.height
                    height: inLineSmallList.height
                    border.color: "black"
                    border.width: 1

                    Rectangle {
                        //property string innLine: inLine.toInt()
                        id: inLineSmallIndicator
                        width: parent.width/4
                        height: parent.width/4
                        radius: parent.width/8
                        color: inLine === 0 ? "red" : "green"
                        anchors.top: parent.top
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Label {
                        id: userInLineNumLabel
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 5
                        text: number
                        font.pixelSize: 10
                    }
                }
            }

            ListView {
                id: inLineSmallList
                anchors.fill: parent
                orientation: Qt.Horizontal
                delegate: inLineSmallListComp
                model: uMod
            }
        }
    }
}
