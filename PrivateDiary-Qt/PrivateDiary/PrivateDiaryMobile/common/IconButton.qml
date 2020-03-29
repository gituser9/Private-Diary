import QtQuick 2.13
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.13


Item {
    id: imgContainer

    property string imgSource
    property string imgColor
    property int iconWidth: 25
    property int iconHeight: 25

    signal tap()


    Image {
        id: imgItem
        source: imgSource
        fillMode: Image.PreserveAspectFit
        sourceSize.height: iconHeight
        sourceSize.width: iconWidth
        width: iconWidth
        height: iconHeight
        anchors.centerIn: imgContainer

        MouseArea {
            height: parent.height + 15
            width: parent.width + 15
            anchors.centerIn: parent
            onClicked: tap()
        }
        ColorOverlay{
            anchors.fill: imgItem
            source:imgItem
            color: imgColor
            transform:rotation
            antialiasing: true
        }
    }

}
