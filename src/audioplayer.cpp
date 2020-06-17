// Code from harbour-received
// Written by kempe
// https://gitlab.com/sailfish-apps/Received
// GPLv2

#include <QDebug>
#include "audioplayer.h"

AudioPlayer::AudioPlayer(QObject *parent) : QMediaPlayer(parent)
{
    m_current_url = "";
    m_buffer_progress = 0;

    connect(this, &QMediaPlayer::stateChanged, this, &AudioPlayer::playbackStateChanged);
    connect(this, &QMediaPlayer::mediaStatusChanged, this, &AudioPlayer::playbackStatusChanged);
    connect(this, &QMediaPlayer::bufferStatusChanged, this, &AudioPlayer::bufferStatusChanged);
    connect(
            this, static_cast<void(QMediaPlayer::*)()>(&QMediaPlayer::metaDataChanged),
            this, &AudioPlayer::metaDataChanged
    );
}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::loadUrl(QString url)
{
    stopPlayback();
    m_current_url = QUrl(url);
    startPlayback();
}

void AudioPlayer::togglePlayback()
{
    switch(state()) {
    case QMediaPlayer::PausedState:
    case QMediaPlayer::StoppedState:
        startPlayback();
        break;
    case QMediaPlayer::PlayingState:
        pauseOrStopPlayback();
        break;
    default:
        break;
    }
}

void AudioPlayer::startPlayback() {
    if (mediaStatus() == QMediaPlayer::NoMedia) {
        qDebug() << "Loading new media";
        setMedia(m_current_url);
    }

    play();
}

void AudioPlayer::pauseOrStopPlayback() {
    if (isSeekable()) {
        qDebug() << "Pausing playback";
        pause();
    } else {
        qDebug() << "Stoping playback";
        stopPlayback();
    }
}

void AudioPlayer::stopPlayback()
{
    stop();
    setMedia(QMediaContent());
}

void AudioPlayer::bufferStatusChanged(const int progress)
{
    m_buffer_progress = progress / 100.0;
    emit bufferProgressChanged();
}

void AudioPlayer::metaDataChanged()
{
    qDebug() << "metaDataChanged";
    QString tmp_title = getMetaDataValueOrEmptyByKey("Title").toString();
    if (tmp_title != m_title) {
        qDebug() << "Setting title to: " << tmp_title;
        m_title = tmp_title;
        emit titleChanged();
    }
    QString tmp_genre = getMetaDataValueOrEmptyByKey("Genre").toString();
    if (tmp_genre != m_genre) {
        qDebug() << "Setting genre to: " << tmp_genre;
        m_genre = tmp_genre;
        emit genreChanged();
    }
}

QVariant AudioPlayer::getMetaDataValueOrEmptyByKey(QString key) {
    if (availableMetaData().contains(key)) {
        return metaData(key);
    }

    return "";
}
