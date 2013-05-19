import QtQuick 1.1

Item {
    id: root

    property bool checked: false

    height: 60
    width: 60

    Rectangle {
        anchors.centerIn: parent
        height: root.height - 10
        width: root.width - 10
        radius: 14
        color: "transparent"
        smooth: true
        border {
            color: "darkgray"
            width: 4
        }

        Rectangle {
            anchors {
                fill: parent
                margins: 8
            }
            smooth: true
            radius: 6
            color: "green"
            opacity: root.checked ? 1 : 0

            Behavior on opacity { NumberAnimation { } }
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: root.checked = !root.checked
    }
}
