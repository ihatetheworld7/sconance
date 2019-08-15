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
    Text{
        x:60
        y:100
        color:"black"
        font.family: "Helvetica"
        font.pointSize: 24
        text:"Hello Qt Qucik!"
    }
    Text{
        x:60;
        y:140;
        color:"red";
        font.family: "Helvetica"
        font.pointSize: 24
        text:"<b>hello</b> <i>Qt Quick</i>"
    }
    Text{
        x:60
        y:180
        color:"green"
        font.family: "Helvetica"
        font.pointSize: 24
        style:Text.Outline;styleColor: "blue"
        text:"Hello Qt Quick"
    }
    Text{
        width: 200
        color:"green"
        font.family: "Helvetica"
        font.pointSize: 24
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignTop
        elide: Text.ElideRight
        text:"hello Qt Quick"
    }
    Text{
        width: 200
        y:30
        color:"green"
        font.family: "Helvetica"
        font.pointSize: 24
        horizontalAlignment: Text.AlignLeft
        wrapMode: Text.WrapAnywhere
        text:"Hello Qt Quick"
    }
}
