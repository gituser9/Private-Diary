import QtQuick 2.13


QtObject {

    function getPlatformValue(forIos = 100, forAndroid = 60) {
        if (isIos()) {
            return forIos
        } else {
            return forAndroid
        }
    }

    function isIos() {
        return Qt.platform.os === 'ios'
    }

    function getIcon(forIos, forAndroid) {
        const path = 'qrc:/images/'
        return getPlatformValue(path + forIos + '.svg', path + forAndroid + '.svg')
    }

}
