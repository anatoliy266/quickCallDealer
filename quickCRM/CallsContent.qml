import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import Qt.labs.calendar 1.0
import QtQuick.Controls.Universal 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Item {
    id: callsItem
    parent: contentSpase
    width: parent.width
    height: parent.height

    function dateParser(time_t) {
        var date = new Date(time_t*1000)
        var strDate = date.getFullYear()+"."+date.getMonth()+"."+date.getDate()+" "+date.getHours()+":"+date.getMinutes()
        return strDate
    }

    Connections {
        id: callsSucessdtContolConnection
        target: dtControl
        onCModSucessSignal: {
            callsContentList.model = cMod
        }
    }

    Connections {
        id: callsSucessConnection
        target: cMod
        onCSucess: {
            //callsContentList.model === cMod ? console.log("CallsContent.qml: nothing to do") : callsContentList.model = cMod
            //callsContentList.model = cMod
        }
        onModelDataChange: {
            callsContentList.model = 0
        }
    }



    Rectangle {
        id: callsRect
        width: contentSpase.width
        height: contentSpase.height
        color: "transparent"

        Component {
            id: callsContentComp

            Rectangle {
                id: callsContentRect
                width: callsContentList.width
                height: 230
                border.color: "white"
                border.width: 2
                color: "transparent"
                opacity: 0.8

                gradient: Gradient {

                    GradientStop {
                        position: 0.0
                        color: "white"
                    }

                    GradientStop {
                        position: 0.05
                        color: "silver"
                    }

                    GradientStop {
                        position: 0.1
                        color: "white"
                    }

                    GradientStop {
                        position: 0.9
                        color: "white"
                    }

                    GradientStop {
                        position: 0.95
                        color: "silver"
                    }

                    GradientStop {
                        position: 1.0
                        color: "white"
                    }
                }

                Rectangle {
                    id: callsContentOrgRect
                    width: (parent.height-20)/3*2
                    height: parent.height-20
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 10
                    color: "transparent"
                    border.color: "silver"
                    border.width: 2

                    Image {
                        id: callsContentOrgImage
                        width: parent.width-10
                        height: parent.width-14
                        anchors.top: parent.top
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.topMargin: 2
                        source: "orgIm.png"
                    }

                    Label {
                        id: callsContentOrgUserLabel
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: callsContentOrgImage.bottom
                        text: "user name"
                        font.pixelSize: 12
                    }

                    TextField {
                        id: callsContentOrgUserTextField
                        width: parent.width-4
                        height: 25
                        anchors.top: callsContentOrgUserLabel.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.topMargin: 2
                        selectByMouse: true
                        bottomPadding: 2
                        font.pixelSize: 14
                        placeholderText: asterOrgUser
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    Label {
                        id: callsContentOrgLabel
                        anchors.top: callsContentOrgUserTextField.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.topMargin: 2
                        text: "organization"
                        font.pixelSize: 12
                    }

                    TextField {
                        id: callsContentOrgTextField
                        width: parent.width-4
                        height: 25
                        anchors.top: callsContentOrgLabel.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.topMargin: 2
                        selectByMouse: true
                        bottomPadding: 2
                        font.pixelSize: 14
                        placeholderText: callerName
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Rectangle {
                    id: calsContentOrgPhoneRect
                    width: parent.height
                    height: 40
                    anchors.left: callsContentOrgRect.right
                    anchors.top: calsContentOrgCommentLabel.top
                    anchors.leftMargin: 5
                    anchors.bottomMargin: 5
                    color: "transparent"

                    Label {
                        id: calsContentOrgPhoneLabel
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.topMargin: 2
                        text: callerPhone
                        font.pixelSize: 18
                    }
                }

                Rectangle {
                    id: calsContentOrgQueryRect
                    width: parent.height
                    height: (calsContentOrgCommentRect.height+calsContentOrgQueryLabel.height)-calsContentOrgPhoneRect.height
                    anchors.bottom: calsContentOrgCommentRect.bottom
                    anchors.left: callsContentOrgRect.right
                    anchors.leftMargin: 5
                    anchors.topMargin: 5
                    color: "transparent"

                    ComboBox {
                        id: calsContentOrgQueryComboBox
                        width: parent.width
                        //anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottom
                        model: qMod
                        displayText: "Другое"
                        delegate: Rectangle {
                            id: calsContentOrgQueryDelegateRect
                            width: calsContentOrgQueryComboBox.width
                            height: 30
                            color: "transparent"
                            border.color: "silver"
                            border.width: 1

                            Label {
                                id: calsContentOrgQueryDelegateLabel
                                anchors.centerIn: parent
                                text: q_type
                                font.pixelSize: 14

                                MouseArea {
                                    id: calsContentOrgQueryDelegateEvent
                                    anchors.fill: parent
                                    onClicked: {
                                        calsContentOrgQueryComboBox.displayText = calsContentOrgQueryDelegateLabel.text
                                        calsContentOrgQueryComboBox.popup.close()
                                    }
                                }
                            }
                        }
                    }

                    Label {
                        id: calsContentOrgQueryLabel
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        text: "Query"
                        font.pixelSize: 14
                    }
                }

                Rectangle {
                    id: calsContentOrgCommentRect
                    height: parent.height/2
                    width: parent.width-(calsContentOrgQueryRect.x+calsContentOrgQueryRect.width+15)
                    anchors.left: calsContentOrgQueryRect.right
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    color: "transparent"
                    border.color: "silver"
                    border.width: 2

                    TextArea {
                        id: calsContentOrgCommentTextField
                        anchors.fill: parent
                        selectByMouse: true
                        textMargin: 2
                        wrapMode: TextEdit.WordWrap
                    }
                }

                Label {
                    id: calsContentOrgCommentLabel
                    anchors.left: calsContentOrgCommentRect.left
                    anchors.bottom: calsContentOrgCommentRect.top
                    anchors.bottomMargin: 2
                    text: "Comment"
                    font.pixelSize: 14
                }

                Label {
                    id: callsContentCallTime
                    anchors.top: parent.top
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.topMargin: 15
                    text: dateParser(dateTime)
                    font.pixelSize: 14
                }

                Rectangle {
                    id: callsContentCallAcceptButtonRect
                    property string currIdx: id_call
                    width: parent.height/2
                    height: 30
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.bottomMargin: 15
                    anchors.rightMargin: 5
                    color: "green"
                    radius: 3

                    Label {
                        id: callsContentCallAcceptButtonLabel
                        anchors.centerIn: parent
                        text: "complete"
                        font.pixelSize: 16
                    }

                    MouseArea {
                        id: callsContentCallAcceptButtonEvent
                        anchors.fill: parent
//                        property string idx: callsContentCallAcceptButtonRect.currIdx
//                        property string orgUserName: callsContentOrgUserTextField.text === "" ? callsContentOrgUserTextField.placeholderText : callsContentOrgUserTextField.text
//                        property string orgName: callsContentOrgTextField.text === "" ? callsContentOrgTextField.placeholderText : callsContentOrgTextField.text
//                        property string orgPhone: callerPhone
//                        property string query: calsContentOrgQueryComboBox.displayText
//                        property string comment: calsContentOrgCommentTextField.text
//                        property string image: callsContentOrgImage.source
                        onClicked: {
                            dtControl.setRecRequest(callsContentCallAcceptButtonRect.currIdx, callsContentOrgUserTextField.text === "" ? callsContentOrgUserTextField.placeholderText : callsContentOrgUserTextField.text, callsContentOrgTextField.text === "" ? callsContentOrgTextField.placeholderText : callsContentOrgTextField.text, callerPhone, calsContentOrgQueryComboBox.displayText, calsContentOrgCommentTextField.text, callsContentOrgImage.source)
                            callsContentDelegateLoaderRect.visible = true
                            callsContentDelegateLoaderloadingIndicator.running = true
                        }
                    }
                }

                Rectangle {
                    id: callsContentDelegateLoaderRect
                    anchors.fill: parent
                    opacity: 0.5
                    visible: false

                    BusyIndicator {
                        id: callsContentDelegateLoaderloadingIndicator
                        anchors.centerIn: parent
                        width: parent.height/2
                        height: parent.height/2
                        running: false
                    }
                }
            }
        }

        ListView {
            id: callsContentList
            anchors.fill: parent
            model: cMod
            delegate: callsContentComp
            highlight: Rectangle {
                id: callsContentDelegateHighLighter
                color: "silver"
                opacity: 0.3
            }
            ScrollBar.vertical: ScrollBar {
                id: callsContentListScroll

            }
        }
    }
}
