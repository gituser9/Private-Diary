import QtQuick 2.13
import QtQuick.Controls 2.13

import StatusBar 0.1
import PostModel 0.1

import '../common'


AppPage {

    property var post
    property var userModel
    property StackView stack
    property bool isCompleted: false

    readonly property Util util: Util{}
    readonly property Constant constant: Constant{}
    readonly property PostModel postModel: PostModel{}
    readonly property string iconColor: '#4D5A6F'



    id: postPage
    statusBarTheme: StatusBar.Dark


    Component.onCompleted: {
        postModel.setAppData(userModel.id, userModel.password)
        postModel.load(post.id)
        isCompleted = true
        taskTimer.start()

    }
    Component.onDestruction: {
        postModel.updatePost(post.id, titleTextArea.text, textArea.text, true)
    }


    header: Rectangle {
        id: headerItem
        height: util.getPlatformValue(100, 60)
        color: constant.colors.darkBlue
        width: parent.width

        Column {
            id: headerColumn
            anchors.fill: parent
            anchors.topMargin: util.getPlatformValue(30, 0)

            Row {
                id: headerRow
                anchors.fill: parent

                IconButton {
                    id: backImg
                    imgSource: 'qrc:/images/arrow_back.svg'
                    imgColor: '#fff'
                    height: 45
                    width: 45
                    iconHeight: 30
                    anchors.verticalCenter: headerRow.verticalCenter
                    onTap: {
                        stack.pop()
                    }
                }
                Text {
                    text: post.title
                    elide: Text.ElideRight
                    maximumLineCount: 1
                    color: '#fff'
                    font.weight: Font.Bold
                    font.pixelSize: 16
                    anchors.centerIn: parent
                    width: parent.width - backImg.width
                    height: headerItem.height
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }
            }
        }
    }

    Timer {
        id: taskTimer
        interval: (1000 * 60) * 5
        running: false
        repeat: true
        onTriggered: {
            postModel.updatePost(post.id, titleTextArea.text, textArea.text, true)
        }
    }


    Column {
        anchors.fill: parent

        EditPanel {
            id: editPanel
            width: parent.width
            height: 60
            textArea: textArea
        }
        TextArea {
            id: titleTextArea
            anchors.top: editPanel.bottom
            width: parent.width
            textFormat: Qt.PlainText
            wrapMode: TextArea.Wrap
            focus: false
            selectByMouse: true
            persistentSelection: true
            leftPadding: 6
            rightPadding: 6
            topPadding: 6
            bottomPadding: 0
            background: null
            font.weight: Font.Bold
            font.pointSize: 25
            text: postModel.title
            height: 50
            onTextChanged: {
                if (!isCompleted) {
                    return
                }
                postModel.updatePost(post.id, titleTextArea.text, textArea.text, false)
            }
        }

        Flickable {
            id: flickable
            flickableDirection: Flickable.VerticalFlick
            width: parent.width
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: titleTextArea.bottom

            TextArea.flickable: TextArea {
                id: textArea
                width: parent.width
                textFormat: Qt.RichText
                wrapMode: TextArea.Wrap
                focus: false
                selectByMouse: false
                persistentSelection: true
                leftPadding: 6
                rightPadding: 6
                topPadding: 6
                bottomPadding: 16
                background: null
                onLinkActivated: Qt.openUrlExternally(link)
                text: postModel.body
                onTextChanged: {
                    if (!isCompleted) {
                        return
                    }
                    postModel.updatePost(post.id, titleTextArea.text, textArea.text, false)
                }

            }
        }
    }


    Menu {
        id: contextMenu

        MenuItem {
            text: qsTr("Copy")
            enabled: textArea.selectedText
            onTriggered: textArea.copy()
        }
        MenuItem {
            text: qsTr("Cut")
            enabled: textArea.selectedText
//            onTriggered: textArea.cut()
        }
        MenuItem {
            text: qsTr("Paste")
            enabled: textArea.canPaste
            onTriggered: textArea.paste()
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Font...")
//            onTriggered: fontDialog.open()
        }

        MenuItem {
            text: qsTr("Color...")
//            onTriggered: colorDialog.open()
        }
    }

}
