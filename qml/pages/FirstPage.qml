import QtQuick 2.0
import Sailfish.Silica 1.0
import QtMultimedia 5.6
import it.kempe.AudioPlayer 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    Audio {
        id: player
        source: "http://str0.creacast.com/accent4"
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("Audio Test")
            }

            SectionHeader {
                text: "QML Audio component"
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: (player.playbackState == Audio.PlayingState) ? "Pause" : "Play"
                onPressed: {
                    if (player.playbackState == Audio.PlayingState) {
                        player.pause()
                    }
                    else {
                        player.play()
                    }
                }
            }

            SectionHeader {
                text: "C++ Audio component"
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: AudioPlayer.isPlaying ? "Pause" : "Play"
                onPressed: {
                    if (AudioPlayer.isPlaying) {
                        AudioPlayer.stopPlayback()
                    }
                    else {
                        AudioPlayer.loadUrl("http://str0.creacast.com/accent4")
                    }
                }
            }
        }
    }
}
