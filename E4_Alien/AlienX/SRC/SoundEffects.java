import javax.microedition.media.*;
import java.io.*;


class SoundEffects {
    private static SoundEffects instance;
    public Player shoutSoundPlayer;
    
    private SoundEffects() {
        shoutSoundPlayer = createPlayer("/elapame.wav", "audio/x-wav");
    }
    
    // SoundEffects is a singleton
    static SoundEffects getInstance() {
        if (instance == null) {
            instance = new SoundEffects();
        }
        return instance;
    }
    
    void startShoutSound() {
        startPlayer(shoutSoundPlayer);
    }
    
    void startGameOverSound() {
        startPlayer(createPlayer("/gameover.mid", "audio/midi"));
    }
    
    void startLevelCompleteSound() {
        startPlayer(createPlayer("/level.mid", "audio/midi"));
    }

    private Player createPlayer(String filename, String format) {
        Player p = null;
        try {
            InputStream is = getClass().getResourceAsStream(filename);
            p = Manager.createPlayer(is, format);
            p.prefetch();
        } catch (IOException ioe) {
            // ignore
        } catch (MediaException me) {
            // ignore
        }
        return p;
    }
    
    private void startPlayer(Player p) {
        if (p != null) {
            try {
                p.stop();
                p.setMediaTime(0L);
                p.start();
            } catch (MediaException me) {
                // ignore
            }
        }
    }
    
}
