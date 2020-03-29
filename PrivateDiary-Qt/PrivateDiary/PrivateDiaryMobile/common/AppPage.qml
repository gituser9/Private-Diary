import QtQuick 2.13
import QtQuick.Controls 2.13

import StatusBar 0.1


Page {
    id: appPage
    anchors.fill: parent
    header: Rectangle {
        id: appPageHeader
    }

    property int statusBarTheme
    property bool isNeedEmptyHeader: false
    readonly property Constant constant: Constant{}
    readonly property Util util: Util{}


    StatusBar {
        id: statusBar
        theme: {
            if (util.isIos()) {
                statusBar.theme = statusBarTheme

                if (isNeedEmptyHeader) {
                    appPageHeader.height = 40
                }
            } else {
                statusBar.theme = StatusBar.Dark
            }
        }
    }
}
