import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import Qt.labs.calendar 1.0
import QtQuick.Controls.Universal 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Item {
    id: historyContentItem
    parent: contentSpase
    width: parent.width
    height: parent.height

    Connections {
        id: historyfilteringSucessConnection
        target: cMod
        onHSucess: {
            historyContentList.model === cMod ? console.log("nothing to do") : historyContentList.model = cMod
        }
    }

    function dateParser(time_t) {
        var date = new Date(time_t*1000)
        var strDate = date.getFullYear()+"."+date.getMonth()+"."+date.getDate()+" "+date.getHours()+":"+date.getMinutes()
        return strDate
    }

    Rectangle {
        id: historyContentRect
        width: contentSpase.width
        height: contentSpase.height
        color: "transparent"
        opacity: 0.8

        Component {
            id: historyContentComp

            Rectangle {

                id: historyContentDelegateOutSpaceRect
                property string currIdx: index
                width: historyContentList.width
                height: 110
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
                        position: 0.06
                        color: "transparent"
                    }

                    GradientStop {
                        position: 0.94
                        color: "transparent"
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
                    id: historyContentDelegateRect
                    width: parent.width
                    height: parent.height-10
                    anchors.centerIn: parent
                    color: "transparent"


                    Rectangle {
                        id: historyContentDelegateUserImageRect
                        width: parent.height
                        height: parent.height
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        color: "transparent"


                        Image {
                            id: historyContentDelegateUserImage
                            width: parent.height-4
                            height: parent.height-4
                            anchors.centerIn: parent
                            source: "orgIm.png"
                        }
                    }

                    Rectangle {
                        id: historyContentDelegateCallerInfoRect
                        width: parent.width/4
                        height: parent.height-8
                        anchors.top: parent.top
                        anchors.left: historyContentDelegateUserImageRect.right
                        anchors.topMargin: 4
                        color: "transparent"
                        border.color: "silver"
                        border.width: 1

                        Rectangle {
                            id: historyContentDelegateTimeRect
                            width: parent.width
                            height: parent.height/4
                            anchors.top: parent.top
                            color: "transparent"


                            Label {
                                id: historyContentDelegateTimeLabel
                                anchors.left: parent.left
                                anchors.leftMargin: 5
                                text: dateParser(dateTime)
                                font.pixelSize: 14
                            }
                        }

                        Rectangle {
                            id: historyContentDelegatePhoneRect
                            width: parent.width
                            height: parent.height/4
                            anchors.top: historyContentDelegateTimeRect.bottom
                            color: "transparent"

                            Label {
                                id: historyContentDelegatePhoneLabelInfo
                                anchors.right: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                text: "Telephone:"
                                font.pixelSize: 14
                            }

                            Label {
                                id: historyContentDelegatePhoneLabel
                                anchors.left: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.leftMargin: 5
                                text: callerPhone
                                font.pixelSize: 14
                            }
                        }

                        Rectangle {
                            id: historyContentDelegateOrgNameRect
                            width: parent.width
                            height: parent.height/4
                            anchors.top: historyContentDelegatePhoneRect.bottom
                            color: "transparent"

                            Label {
                                id: historyContentDelegateOrgNameLabelInfo
                                anchors.right: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                text: "Organization:"
                                font.pixelSize: 14
                            }

                            Label {
                                id: historyContentDelegateOrgNameLabel
                                anchors.left: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                text: callerName
                                font.pixelSize: 14
                            }
                        }

                        Rectangle {
                            id: historyContentDelegateUserNameRect
                            width: parent.width
                            height: parent.height/4
                            anchors.top: historyContentDelegateOrgNameRect.bottom
                            color: "transparent"

                            Label {
                                id: historyContentDelegateUserNameLabelInfo
                                anchors.right: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                text: "Caller:"
                                font.pixelSize: 14
                            }

                            Label {
                                id: historyContentDelegateUserNameLabel
                                anchors.left: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                text: asterOrgUser
                                font.pixelSize: 14
                            }
                        }
                    }

                    Rectangle {
                        id: historyContentDelegateQueryRect
                        width: parent.width/7
                        height: parent.height/2
                        anchors.left: historyContentDelegateCallerInfoRect.right
                        anchors.leftMargin: 5
                        color: "transparent"

                        Label {
                            id: historyContentDelegateQueryLabel
                            anchors.centerIn: parent
                            text: query
                            font.pixelSize: 14
                        }
                    }

                    Popup {
                        id: historyContentDelegateRecordPopUp
                        width: historyContentDelegateRect.width
                        height: historyContentDelegateRect.height
                        focus: true
                        margins: 0
                        contentItem: Rectangle {
                            id: historyContentDelegateRecordPopUpDelegate
                            width: historyContentDelegateRect.width
                            height: historyContentDelegateRect.height
                            border.color: "gray"
                            border.width: 1
                            color: "silver"

                            Rectangle {
                                id: historyContentDelegatePopupRect
                                width: parent.width
                                height: parent.height-10
                                anchors.centerIn: parent
                                color: "transparent"


                                Rectangle {
                                    id: historyContentDelegatePopupUserImageRect
                                    width: parent.height
                                    height: parent.height
                                    anchors.left: parent.left
                                    anchors.verticalCenter: parent.verticalCenter
                                    color: "transparent"


                                    Image {
                                        id: historyContentDelegatePopupUserImage
                                        width: parent.height-4
                                        height: parent.height-4
                                        anchors.centerIn: parent
                                        source: "orgIm.png"
                                    }
                                }

                                Rectangle {
                                    id: historyContentDelegatePopupCallerInfoRect
                                    width: parent.width/4
                                    height: parent.height-8
                                    anchors.top: parent.top
                                    anchors.left: historyContentDelegatePopupUserImageRect.right
                                    anchors.topMargin: 4
                                    color: "transparent"
                                    border.color: "gray"
                                    border.width: 1

                                    Rectangle {
                                        id: historyContentDelegatePopupTimeRect
                                        width: parent.width
                                        height: parent.height/4
                                        anchors.top: parent.top
                                        color: "transparent"


                                        Label {
                                            id: historyContentDelegatePopupTimeLabel
                                            anchors.left: parent.left
                                            anchors.leftMargin: 5
                                            text: dateParser(dateTime)
                                            font.pixelSize: 14
                                        }
                                    }

                                    Rectangle {
                                        id: historyContentDelegatePopupPhoneRect
                                        width: parent.width
                                        height: parent.height/4
                                        anchors.top: historyContentDelegatePopupTimeRect.bottom
                                        color: "transparent"

                                        Label {
                                            id: historyContentDelegatePopupPhoneLabelInfo
                                            anchors.right: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            text: "Telephone:"
                                            font.pixelSize: 14
                                        }

                                        Label {
                                            id: historyContentDelegatePopupPhoneLabel
                                            anchors.left: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.leftMargin: 5
                                            text: callerPhone
                                            font.pixelSize: 14
                                        }
                                    }

                                    Rectangle {
                                        id: historyContentDelegatePopupOrgNameRect
                                        width: parent.width
                                        height: parent.height/4
                                        anchors.top: historyContentDelegatePopupPhoneRect.bottom
                                        color: "transparent"

                                        Label {
                                            id: historyContentDelegatePopupOrgNameLabelInfo
                                            anchors.right: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            text: "Organization:"
                                            font.pixelSize: 14
                                        }

                                        TextField {
                                            id: historyContentDelegatePopupOrgNameTextField
                                            anchors.left: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: parent.width/2
                                            height: parent.height
                                            placeholderText: callerName
                                            font.pixelSize:14
                                        }
                                    }

                                    Rectangle {
                                        id: historyContentDelegatePopupUserNameRect
                                        width: parent.width
                                        height: parent.height/4
                                        anchors.top: historyContentDelegatePopupOrgNameRect.bottom
                                        color: "transparent"

                                        Label {
                                            id: historyContentDelegatePopupUserNameLabelInfo
                                            anchors.right: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            text: "Caller:"
                                            font.pixelSize: 14
                                        }

                                        TextField {
                                            id: historyContentDelegatePopupUserNameTextField
                                            anchors.left: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            width: parent.width/2
                                            height: parent.height
                                            placeholderText: asterOrgUser
                                            font.pixelSize: 14
                                        }
                                    }
                                }

                                Rectangle {
                                    id: historyContentDelegatePopupQueryRect
                                    property string qType: query
                                    width: parent.width/7
                                    height: parent.height/2
                                    anchors.left: historyContentDelegatePopupCallerInfoRect.right
                                    anchors.leftMargin: 5
                                    color: "transparent"

                                    ComboBox {
                                        id: historyContentPopupOrgQueryComboBox
                                        width: parent.width
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.bottom: parent.bottom
                                        displayText: historyContentDelegatePopupQueryRect.qType
                                        model: qMod
                                        delegate: Rectangle {
                                            id: historyContentPopupOrgQueryDelegateRect
                                            width: historyContentPopupOrgQueryComboBox.width
                                            height: 30
                                            color: "transparent"
                                            border.color: "silver"
                                            border.width: 1

                                            Label {
                                                id: historyContentPopupOrgQueryDelegateLabel
                                                anchors.centerIn: parent
                                                text: q_type
                                                font.pixelSize: 14

                                                MouseArea {
                                                    id: historyContentPopupOrgQueryDelegateEvent
                                                    anchors.fill: parent
                                                    onClicked: {
                                                        historyContentDelegatePopupQueryRect.qType = historyContentPopupOrgQueryDelegateLabel.text
                                                        historyContentPopupOrgQueryComboBox.popup.close()
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                Rectangle {
                                    id: historyContentDelegatePopupCommentRect
                                    height: parent.height-10
                                    width: parent.width-historyContentDelegateRecordRect.width-historyContentDelegatePopupQueryRect.width-historyContentDelegatePopupPhoneRect.width-historyContentDelegatePopupUserImageRect.width-20
                                    anchors.left: historyContentDelegatePopupQueryRect.right
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.leftMargin: 5
                                    color: "transparent"
                                    border.color: "gray"
                                    border.width: 1

                                    TextArea {
                                        id: historyContentDelegatePopupCommentTextArea
                                        anchors.fill: parent
                                        placeholderText: comment
                                        font.pixelSize:14
                                    }
                                }

                                Rectangle {
                                    id: historyContentDelegatePopupRecordRect
                                    property int idx: index
                                    width: parent.height/4
                                    height: parent.height/4
                                    anchors.top: parent.top
                                    anchors.topMargin: 5
                                    anchors.right: parent.right
                                    anchors.rightMargin: 5
                                    color: "transparent"

                                    Image {
                                        id: historyContentDelegatePopupRecordImage
                                        anchors.fill: parent
                                        source: "/confirm.png"
                                    }

                                    MouseArea {
                                        id: historyContentDelegatePopupRecordEvent
                                        anchors.fill: parent
                                        onClicked: {
                                            dtControl.setRecRequest(historyContentDelegateOutSpaceRect.currIdx, historyContentDelegatePopupUserNameTextField.text === "" ? historyContentDelegatePopupUserNameTextField.placeholderText : historyContentDelegatePopupUserNameTextField.text, historyContentDelegatePopupOrgNameTextField.text === "" ? historyContentDelegatePopupOrgNameTextField.placeholderText : historyContentDelegatePopupOrgNameTextField.text, callerPhone, historyContentPopupOrgQueryComboBox.displayText, historyContentDelegatePopupCommentTextArea.text === "" ? historyContentDelegatePopupCommentTextArea.placeholderText : historyContentDelegatePopupCommentTextArea.text, historyContentDelegatePopupUserImage.source)
                                        }
                                    }
                                }
                            }
                        }
                        padding: 0
                    }

                    Rectangle {
                        id: historyContentDelegateRecordRect
                        width: parent.height/4
                        height: parent.height/4
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        color: "transparent"

                        Image {
                            id: historyContentDelegateRecordImage
                            anchors.fill: parent
                            source: "/edit.png"
                        }

                        MouseArea {
                            id: historyContentDelegateRecordEvent
                            anchors.fill: parent
                            onClicked: {
                                historyContentDelegateRecordPopUp.open()
                            }
                        }
                    }

                    Rectangle {
                        id: historyContentDelegateCommentRect
                        height: parent.height-10
                        width: parent.width-historyContentDelegateRecordRect.width-historyContentDelegateQueryRect.width-historyContentDelegatePhoneRect.width-historyContentDelegateUserImageRect.width-20
                        anchors.left: historyContentDelegateQueryRect.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: 5
                        color: "transparent"
                        border.color: "silver"
                        border.width: 1

                        Label {
                            id: historyContentDelegateCommentLabel
                            anchors.fill: parent
                            text: comment
                            font.pixelSize: 14
                        }
                    }
                }
            }
        }

        ListView {
            id: historyContentList
            anchors.fill: parent
            model: cMod
            delegate: historyContentComp
            ScrollBar.vertical: ScrollBar{}
        }
    }
}
