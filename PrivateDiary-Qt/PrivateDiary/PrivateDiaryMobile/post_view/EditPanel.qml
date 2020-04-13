import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import '../common'


Rectangle {

    property TextArea textArea

    width: parent.width
    height: 60


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
                let start = textArea.selectionStart
                let end = textArea.selectionEnd
                let text = textArea.selectedText.toString()

                textArea.remove(start, end)
                textArea.insert(start, "<div style='font-weight:600;'>"+text+'</div>')
                textArea.cursorPosition = end
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
                let start = textArea.selectionStart
                let end = textArea.selectionEnd
                let text = textArea.selectedText.toString()

                textArea.remove(start, end)
                textArea.insert(start, "<div style='font-style:italic;'>"+text+'</div>')
                textArea.cursorPosition = end
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
                let start = textArea.selectionStart
                let end = textArea.selectionEnd
                let text = textArea.selectedText.toString()

                textArea.remove(start, end)
                textArea.insert(start, "<div style='text-decoration: underline;'>"+text+'</div>')
                textArea.cursorPosition = end
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
                let start = textArea.selectionStart
                let end = textArea.selectionEnd
                let text = textArea.selectedText.toString()

                textArea.remove(start, end)
                textArea.insert(start, "<div align='left'>"+text+'</div>')
                textArea.cursorPosition = end
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
                let start = textArea.selectionStart
                let end = textArea.selectionEnd
                let text = textArea.selectedText.toString()

                textArea.remove(start, end)
                textArea.insert(start, "<div align='center'>"+text+'</div>')
                textArea.cursorPosition = end
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
                let start = textArea.selectionStart
                let end = textArea.selectionEnd
                let text = textArea.selectedText.toString()

                textArea.remove(start, end)
                textArea.insert(start, "<div align='right'>"+text+'</div>')
                textArea.cursorPosition = end
            }
        }
    }

}

