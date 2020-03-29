import QtQuick 2.13
import QtQuick.Controls 2.13

import './login'
import './post_list'
import './post_view'


ApplicationWindow {
    visible: true
    width: 400
    height: 700
    title: qsTr("Private Diary")

    flags: Qt.Window | Qt.MaximizeUsingFullscreenGeometryHint

    StackView {
        id: stack
        anchors.fill: parent

        Login {
            stack: stack
        }
    }

}
