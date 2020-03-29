import QtQuick 2.12
import QtQuick.Controls 2.5


Item {

    height: fieldHeight
    width: field.width

    property string placeholder: ''
    property bool isPassword: false
    property int fieldHeight: 40
    property int fieldWidth: 200

    property alias text: field.text

    TextField {
        id: field
        height: fieldHeight
        width: fieldWidth
        placeholderText: placeholder
        echoMode: isPassword ? TextInput.Password : TextInput.Normal
        background: Rectangle {
            radius: 10
            border.color: '#E4E5E7'
            width: 1
            anchors.fill: parent
            color: '#F2F3F5'
        }
    }
}
