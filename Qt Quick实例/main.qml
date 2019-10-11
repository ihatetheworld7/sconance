import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 700
    height: 550
    title: qsTr("stuInfo")
    MainFormForm{
        anchors.fill:parent
        submit.onClicked: {
            var hobbyText="";
            for(var i=0;i<7;++i)
            {
                hobbyText+=hobby.children[i].checked?(hobby.children[i].text+"`"):"";
            }
            if(hobby.children[7].checked)
            {
                hobbyText+="..."
            }
            details.text="my name is"+name.text+"a"+age.text+"years"+sex.checked.toString()+
                    "\nprofession with"+spec.currentText+"hobby"+hobbyText;
        }
    }
}
