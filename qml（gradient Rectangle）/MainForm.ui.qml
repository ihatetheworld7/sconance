import QtQuick 2.7

Rectangle {
    property alias mouseArea: mouseArea
    property alias textEdit: textEdit

    width: 360
    height: 360

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
    Rectangle{
        width: 100
        height: 100
        x:40
        y:60
        rotation: 45
        color:"red"
    }
    Rectangle{
        id:topRect
        opacity: 0.6
        scale: 0.8
        x:135
        y:60
        width: 100
        height: 100
        radius: 8
        gradient: Gradient{
            GradientStop{position: 0.0;color:"aqua"}
            GradientStop{position: 1.0;color:"teal"}
        }
        border.color: "blue"
        border.width: 3
    }

    TextEdit {
        id: textEdit
        text: qsTr("Enter some text...")
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 1
        }
    }
}
