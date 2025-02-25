#include <iostream>
using namespace std;

// Target interface
class MediaPlayer {
public:
    virtual void play(const string& audioType, const string& fileName) = 0;
    virtual ~MediaPlayer() {}
};

// Adaptee interface
class AdvancedMediaPlayer {
public:
    virtual void playVlc(const string& fileName) = 0;
    virtual void playMp4(const string& fileName) = 0;
    virtual ~AdvancedMediaPlayer() {}
};

// Concrete Adaptee
class VlcPlayer : public AdvancedMediaPlayer {
public:
    void playVlc(const string& fileName) override {
        cout << "Playing vlc file: " << fileName << endl;
    }
    
    void playMp4(const string& fileName) override {
        // Do nothing
    }
};

class Mp4Player : public AdvancedMediaPlayer {
public:
    void playVlc(const string& fileName) override {
        // Do nothing
    }
    
    void playMp4(const string& fileName) override {
        cout << "Playing mp4 file: " << fileName << endl;
    }
};

// Adapter
class MediaAdapter : public MediaPlayer {
private:
    AdvancedMediaPlayer* advancedMusicPlayer;
    
public:
    MediaAdapter(const string& audioType) {
        if (audioType == "vlc") {
            advancedMusicPlayer = new VlcPlayer();
        } else if (audioType == "mp4") {
            advancedMusicPlayer = new Mp4Player();
        }
    }
    
    ~MediaAdapter() {
        delete advancedMusicPlayer;
    }
    
    void play(const string& audioType, const string& fileName) override {
        if (audioType == "vlc") {
            advancedMusicPlayer->playVlc(fileName);
        } else if (audioType == "mp4") {
            advancedMusicPlayer->playMp4(fileName);
        }
    }
};

// Concrete Target
class AudioPlayer : public MediaPlayer {
private:
    MediaAdapter* mediaAdapter;
    
public:
    AudioPlayer() : mediaAdapter(nullptr) {}
    
    ~AudioPlayer() {
        delete mediaAdapter;
    }
    
    void play(const string& audioType, const string& fileName) override {
        // Native support for mp3
        if (audioType == "mp3") {
            cout << "Playing mp3 file: " << fileName << endl;
        }
        // Using adapter for other formats
        else if (audioType == "vlc" || audioType == "mp4") {
            mediaAdapter = new MediaAdapter(audioType);
            mediaAdapter->play(audioType, fileName);
        } else {
            cout << "Invalid media type: " << audioType << endl;
        }
    }
};

int main() {
    AudioPlayer* audioPlayer = new AudioPlayer();
    
    audioPlayer->play("mp3", "song.mp3");
    audioPlayer->play("vlc", "movie.vlc");
    audioPlayer->play("mp4", "video.mp4");
    audioPlayer->play("avi", "video.avi");
    
    delete audioPlayer;
    
    return 0;
}