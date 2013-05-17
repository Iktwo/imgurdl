import QtQuick 1.1
import DownloaderComponent 1.0

Rectangle {
    width: 600
    height: 480

    Downloader {
        id: downloader
    }

    Text {
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }

        text: qsTr("imgur /r/Downloader by Iktwo")
    }

    Rectangle {
        id: input

        width: 280
        height: 60
        color: "gray"

        radius: 10

        anchors.centerIn: parent

        TextInput {
            id: textInput

            anchors {
                top: parent.top; topMargin: 5
                bottom: parent.bottom; bottomMargin: 5
                right: parent.right; rightMargin: 10
                left: parent.left; leftMargin: 10
            }

            font.pointSize: 28

            color: "white"
        }
    }

    Rectangle {
        height: 120
        width: 120
        radius: 20
        color: "lightgray"

        anchors {
            bottom: parent.bottom; bottomMargin: 20
            horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: qsTr("Download!")
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent

            onClicked: downloader.download(textInput.text, 1)
        }
    }
}
