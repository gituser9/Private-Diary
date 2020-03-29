import QtQuick 2.12

QtObject {

    readonly property var colors: Item {
        readonly property string darkBlue: '#203152'
        readonly property string grey: '#EDEEF0'
        readonly property string lightGrey: '#F2F3F5'
    }
    readonly property var platform: Item {
        readonly property string ios: 'ios'
    }

}
