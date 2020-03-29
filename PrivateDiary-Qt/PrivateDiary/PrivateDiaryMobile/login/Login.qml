import QtQuick 2.12
import QtQuick.Controls 2.12
import Qt.labs.settings 1.1
import QtQuick.Dialogs 1.2

import StatusBar 0.1
import UserPresenter 0.1

import '../common'


AppPage {
    anchors.fill: parent
    statusBarTheme: StatusBar.Light

    property bool isLoading: false
    property int formWidth: 250
    property StackView stack
    property UserPresenter presenter: UserPresenter{}


    Connections {
        target: presenter
        onShowMessage: {
            messageDialog.text = message
            messageDialog.visible = true
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 10


        RoundTextField {
            id: loginField
            fieldWidth: formWidth
            placeholder: qsTr('Login')
            text: appSettings.login
        }
        RoundTextField {
            id: passwordField
            fieldWidth: formWidth
            isPassword: true
            placeholder: qsTr('Password')
        }
        Rectangle {
            height: 15
            width: formWidth
        }
        RoundedButton {
            btnEnabled: loginField.text !== '' && passwordField.text !== ''
            btnWidth: formWidth
            btnText: qsTr('Login')
            onTap: {
                const data = {
                    'login': loginField.text,
                    'password': passwordField.text
                }
                let id = presenter.auth(data.login, data.password)

                if (id !== 0) {
                    appSettings.login = data.login
                    stack.push('qrc:/post_list/PostList.qml', {
                        stack: stack,
                        userData: {
                            id: id,
                            password: data.password
                        }
                    })
                }
            }
        }
        RoundedButton {
            btnEnabled: loginField.text !== '' && passwordField.text !== ''
            btnWidth: formWidth
            btnText: qsTr('Registration')
            onTap: {
                const data = {
                    'login': loginField.text,
                    'password': passwordField.text
                }
                let id = presenter.registration(data.login, data.password)

                if (id !== 0) {
                    appSettings.login = data.login
                    stack.push('qrc:/post_list/PostList.qml', {
                        stack: stack,
                        userData: {
                            id: id,
                            password: data.password
                        }
                    })
                }
            }
        }
    }

    Settings {
        id: appSettings
        property string login: ''
    }

    MessageDialog {
        id: messageDialog
        title: "Error"
        text: ''
    }
}
