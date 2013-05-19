import QtQuick 1.1
import DownloaderComponent 1.0

Rectangle {
    width: 600
    height: 480

    Downloader {
        id: downloader
    }

    Text {
        id: titleText

        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }

        text: qsTr("imgur /r/Downloader by Iktwo")
    }

    Text {
        id: nsfwText

        anchors {
            top: titleText.bottom; topMargin: 80
        }

        text: qsTr("Download NSFW content")
    }

    Checkbox {
        id: checkbox

        anchors {
            left: nsfwText.right; leftMargin: 20
            verticalCenter: nsfwText.verticalCenter
        }
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
        color: mouseArea.pressed ? "gray" : "lightgray"

        anchors {
            left: input.right; leftMargin: 20
            verticalCenter: input.verticalCenter
        }

        Text {
            text: qsTr("Download!")
            anchors.centerIn: parent
        }

        MouseArea {
            id: mouseArea

            anchors.fill: parent

            onClicked: downloader.download(textInput.text, false, 5)
        }
    }

//    GridView {
//        id: grid

//        anchors.fill: parent

//        model: downloader.files

//        cellHeight: 210
//        cellWidth: 210

//        delegate: Item {

//            height: grid.cellHeight
//            width: grid.cellWidth

//            Image {
//                anchors.fill: parent

//                fillMode: Image.PreserveAspectFit

//                source: modelData

//                clip: true

//                onProgressChanged: console.log("Progress", progress)
//            }
//        }
//    }
}
