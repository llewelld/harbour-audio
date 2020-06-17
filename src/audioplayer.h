// Code from harbour-received
// Written by kempe
// https://gitlab.com/sailfish-apps/Received
// GPLv2

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QMediaPlayer>

class AudioPlayer : public QMediaPlayer {
    Q_OBJECT
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY playbackStateChanged)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY playbackStatusChanged)
    Q_PROPERTY(bool isBuffering READ isBuffering NOTIFY playbackStatusChanged)
    Q_PROPERTY(bool isPlayable READ isPlayable)
    Q_PROPERTY(double bufferProgress READ bufferProgress NOTIFY bufferProgressChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString genre READ genre NOTIFY genreChanged)


public:
    explicit AudioPlayer(QObject *parent = 0);
    ~AudioPlayer();

    bool isPlaying() const { return state() == QMediaPlayer::PlayingState; }
    bool isLoading() const { return mediaStatus() == QMediaPlayer::LoadingMedia; }
    bool isBuffering() const { return mediaStatus() == QMediaPlayer::BufferingMedia; }
    bool isPlayable() const { return m_current_url.isValid(); }
    double bufferProgress() const { return m_buffer_progress; }
    QString title() const { return m_title; }
    QString genre() const { return m_genre; }

signals:
    void playbackStateChanged();
    void playbackStatusChanged();
    void seekableChanged();
    void bufferProgressChanged();
    void titleChanged();
    void genreChanged();

public slots:
    void loadUrl(QString url);
    void togglePlayback();
    void startPlayback();
    void pauseOrStopPlayback();
    void stopPlayback();

private slots:
    void bufferStatusChanged(const int);
    void metaDataChanged();

private:
    // States
    QUrl m_current_url;
    double m_buffer_progress;
    QString m_title;
    QString m_genre;

    QVariant getMetaDataValueOrEmptyByKey(QString);
};

inline static QObject *audioPlayerProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    AudioPlayer *audioPlayer = new AudioPlayer();
    return audioPlayer;
}

#endif // AUDIOPLAYER_H
