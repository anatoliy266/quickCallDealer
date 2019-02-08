import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import Qt.labs.calendar 1.0
import QtQuick.Controls.Universal 2.3
import QtQuick.Controls.Material 2.3
import Qt.labs.platform 1.0


Window {
    id: mainWin
    visible: true
    width: 940
    height: 768
    minimumHeight: 384
    minimumWidth: 940

    title: qsTr("quickCRM")
    property string name: ""
    property int num: 0

    SystemTrayIcon {
        id: mainWinTrayIcon
        visible: true
        iconSource: "/phoneLogo.ico"
        onActivated: {
            mainWin.show()
            mainWin.raise()
            mainWin.requestActivate()
        }
    }

    Connections {
        id: authSucessConnection
        target: uMod
        onAuthSucess: {
            console.log("main.qml >> authSucess signal emitted >> name and num setted >> modelRequest called >> "+dtControl.user+" >> "+dtControl.num)
            generalLoader.source = "MainWindow.qml"
        }
        onSucess: {
            uMod.trayIconChangeEvent(dtControl.num)
        }
        onUserInLine: {
            mainWinTrayIcon.iconSource = "/phoneLogo.ico"
        }
        onUserNotInLine: {
            mainWinTrayIcon.iconSource = "/notinline.png"
        }
    }

    Rectangle {
        id:generalRect
        anchors.fill: parent

        Loader {
            id: generalLoader
            anchors.fill: parent
            source: "Authorization.qml"
        }
    }
}
