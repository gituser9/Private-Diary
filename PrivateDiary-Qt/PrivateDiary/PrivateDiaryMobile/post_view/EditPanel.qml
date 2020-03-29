import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import '../common'


Rectangle {

    property TextArea textArea

    width: parent.width
    height: 60

//            color: 'blue'

    GridLayout {
        anchors.fill: parent
        columns: 6

        IconButton {
            id: boldImg
            imgSource: 'qrc:/images/format_bold.svg'
            imgColor: iconColor
            height: 45
            width: 45
            iconHeight: 30
            anchors.verticalCenter: headerRow.verticalCenter
            onTap: {
                let position = textArea.selectionEnd
                textArea.text = textArea.text.replace(textArea.selectedText, "<div style='font-weight:600;'>"+textArea.selectedText+'</div>')
                textArea.cursorPosition = position



            }
        }
        IconButton {
            id: italicImg
            imgSource: 'qrc:/images/format_italic.svg'
            imgColor: iconColor
            height: 45
            width: 45
            iconHeight: 30
            anchors.verticalCenter: headerRow.verticalCenter
            onTap: {
                let position = textArea.selectionEnd
                textArea.text = textArea.text.replace(textArea.selectedText, "<div style='font-style:italic;'>"+textArea.selectedText+'</div>')
                textArea.cursorPosition = position


            }
        }
        IconButton {
            id: underlineImg
            imgSource: 'qrc:/images/format_underlined.svg'
            imgColor: iconColor
            height: 45
            width: 45
            iconHeight: 30
            anchors.verticalCenter: headerRow.verticalCenter
            onTap: {
                let position = textArea.selectionEnd
                textArea.text = textArea.text.replace(textArea.selectedText, "<div style='text-decoration: underline;'>"+textArea.selectedText+'</div>')
                textArea.cursorPosition = position
            }
        }






        IconButton {
            id: textLeftImg
            imgSource: 'qrc:/images/format_align_left.svg'
            imgColor: iconColor
            height: 45
            width: 45
            iconHeight: 30
            anchors.verticalCenter: headerRow.verticalCenter
            onTap: {
                let position = textArea.selectionEnd
                textArea.text = textArea.text.replace(textArea.selectedText, "<div align='left'>"+textArea.selectedText+'</div>')
                textArea.cursorPosition = position
            }
        }
        IconButton {
            id: textCenterImg
            imgSource: 'qrc:/images/format_align_center.svg'
            imgColor: iconColor
            height: 45
            width: 45
            iconHeight: 30
            anchors.verticalCenter: headerRow.verticalCenter
            onTap: {
                let position = textArea.selectionEnd
                textArea.text = textArea.text.replace(textArea.selectedText, "<div align='center'>"+textArea.selectedText+'</div>')
                textArea.cursorPosition = position
            }
        }
        IconButton {
            id: textRightImg
            imgSource: 'qrc:/images/format_align_right.svg'
            imgColor: iconColor
            height: 45
            width: 45
            iconHeight: 30
            anchors.verticalCenter: headerRow.verticalCenter
            onTap: {
                let position = textArea.selectionEnd
                textArea.text = textArea.text.replace(textArea.selectedText, "<div align='right'>"+textArea.selectedText+'</div>')
                textArea.cursorPosition = position

//                console.log(textArea.text)
            }
        }
    }
}

