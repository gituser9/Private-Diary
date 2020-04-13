import QtQuick 2.13
import QtQuick.Controls 2.13
import Qt.labs.settings 1.1
import QtQuick.Layouts 1.13
import QtGraphicalEffects 1.13
import QtQuick.Dialogs 1.2

import StatusBar 0.1
import PostListModel 0.1
import PostPresenter 0.1

import '../common'


AppPage {

    property StackView stack
    property var userData
    readonly property Util util: Util{}
    readonly property Constant constant: Constant{}
    readonly property PostListModel postListModel: PostListModel{}
    property PostPresenter presenter: PostPresenter{}

    statusBarTheme: StatusBar.Dark

    Component.onCompleted: {
        postListModel.setAppData(userData.id, userData.password)
        presenter.setAppData(userData.id, userData.password)
    }

    Connections {
        target: presenter
        onShowMessage: {
            messageDialog.text = message
            messageDialog.visible = true
        }
    }

    Page {
        id: feedLsitPage
        anchors.fill: parent
        header: Rectangle {
            id: headerItem
            color: constant.colors.darkBlue
            height: util.getPlatformValue(100, 60)

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 15
                text: "Post List"
                font.weight: Font.Bold
                font.pixelSize: 18
                color: '#fff'
            }
        }

        Rectangle {
            height: feedLsitPage.height - 95
            width: feedLsitPage.width
            anchors.bottom: feedLsitPage.bottom

            ListView {
                anchors.fill: parent
                model: postListModel
                delegate: ItemDelegate {
                    id: itemColumn
                    height: 60
                    width: feedLsitPage.width
                    onClicked: {
                        stack.push('qrc:/post_view/PostView.qml', {
                            stack: stack,
                            post: model,
                            userModel: userData,
                        })
                    }

                    Row {
                        anchors.fill: parent

                        Text {
                            id: feedName
                            height: itemColumn.height
                            width: itemColumn.width - 30
                            text: model.title
                            leftPadding: 10
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 16
                            wrapMode: Text.WordWrap
                        }
                        Rectangle {
                            id: badge
                            width: deleteBtn.width
                            height: 21
                            radius: 10
                            anchors.verticalCenter: feedName.verticalCenter
                            anchors.right: sepItem.left

                            IconButton {
                                id: deleteBtn
                                anchors.centerIn: parent
                                imgSource: 'qrc:/images/trash-f.svg'
                                height: 35
                                width: 35
                                iconHeight: 20
                                onTap: {
                                    postListModel.remove(model.id)
                                }
                            }
                        }
                        Rectangle {
                            id: sepItem
                            width: 10
                            anchors.right: parent.right
                        }
                    }
                    Rectangle {
                        color: '#ebebeb'
                        width: feedLsitPage.width
                        height: 1
                    }
                }
            }
        }

        RoundButton {
            id: addButton
            width: 50
            height: 50
            y: parent.height - height - 12
            anchors.right: parent.right
            anchors.margins: 12
            highlighted: true

            onClicked: {
                postListModel.create()
            }
            contentItem: Image {
                id: addImg
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                source: "qrc:/images/add.svg"
                scale: 0.6

                ColorOverlay{
                    anchors.fill: addImg
                    source:addImg
                    color: '#fff'
                    transform:rotation
                    antialiasing: true
                }
            }
        }

        Settings {
            id: appSettings
            property string jwt: ''
        }
    }

    MessageDialog {
        id: messageDialog
        title: "Error"
        text: ''
    }

}

