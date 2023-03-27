/*
 * AlienXMidlet.java
 *
 */

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class AlienXMIDlet extends MIDlet {
    static AlienXMIDlet instance;
    static GameScreen gameScreen;
    static MenuList menuList;
    boolean initDone = false;
    
    public AlienXMIDlet() {
        init();
    }
    
    private synchronized void init() {
        if (!initDone) {
            SoundEffects.getInstance();
            gameScreen = new GameScreen(this);
            gameScreen.init();
            menuList = new MenuList(this);
            initDone = true;
        }
    }
    
    public void startApp() {
        Displayable current = Display.getDisplay(this).getCurrent();
        if (current == null) {
            // first time we've been called
            Display.getDisplay(this).setCurrent(gameScreen);
            gameScreen.start();
        } else {
            if (current == gameScreen) {
                gameScreen.start();   // start its animation thread
            }
            Display.getDisplay(this).setCurrent(current);
        }
    }
    
    public void pauseApp() {
        Displayable current = Display.getDisplay(this).getCurrent();
        if (current == gameScreen) {
            gameScreen.stop();   // kill its animation thread
        }
    }
    
    public void destroyApp(boolean unconditional) {
        if (gameScreen != null) {
            gameScreen.stop();   // kill its animation thread
        }
    }
    
    public void quitApp() {
        destroyApp(true);
        notifyDestroyed();
    }
    
    void gameScreenMenu() {
        gameScreen.stop();
        menuList.setGameActive(true);
        Display.getDisplay(this).setCurrent(menuList);
    }
    
    void menuListContinue() {
        Display.getDisplay(this).setCurrent(gameScreen);
        gameScreen.start();
    }
    
    void menuListNewGame() {
        gameScreen.init();
        Display.getDisplay(this).setCurrent(gameScreen);
        gameScreen.start();
    }
    
    void menuListQuit() {
        quitApp();
    }
    
    // only the MIDlet has access to the display, so put this method here
    void vibrate(int millis) {
        Display.getDisplay(this).vibrate(millis);
    }
    
    void playSound(AlertType at) {
        at.playSound(Display.getDisplay(this));
    }
}
