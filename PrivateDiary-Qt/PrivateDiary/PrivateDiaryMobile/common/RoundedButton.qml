import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.12


Item {

    height: btnHeight
    width: btnWidth

    property int btnWidth
    property int btnHeight: 40
    property int btnRadius: 20
    property int btnTextSixe: 18
    property bool btnEnabled: true
    property bool isBoldText: true
    property string btnColor: constant.colors.darkBlue
    property string btnText: ''
    property string btnTextColor: '#fff'
    property Constant constant: Constant{}

    signal tap()


    Button {
        id: btn
        width: btnWidth
        enabled: btnEnabled
        background: Rectangle {
            radius: btnRadius
            color: btnColor
            implicitHeight: btnHeight
            opacity: btn.down || !btn.enabled ? 0.7 : 1
        }
        contentItem: Text {
            text: btnText
            font.pixelSize: btnTextSixe
            font.weight: isBoldText ? Font.Bold : Font.Normal
            color: btnTextColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
//            bottomPadding: 2
        }
        onClicked: tap()

    }
//    DropShadow {
//        anchors.fill: btn
//        horizontalOffset: 0
//        verticalOffset: 0
//        radius: 4
//        samples: 9
//        color: "#000000"
//        source: btn
//        spread: 0
//    }
}
