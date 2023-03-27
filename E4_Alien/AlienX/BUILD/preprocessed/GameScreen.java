import javax.microedition.lcdui.Image;
import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.game.*;
import javax.microedition.lcdui.AlertType;

public class GameScreen extends GameCanvas implements Runnable {
    public static GameScreen instance;
    public static AlienXMIDlet midlet;
    private volatile Thread animationThread = null;
  
    private static final int MAX_GAMELOOP_CPS = 16;
    private static final int MIN_MILLIS_PER_FRAME = 1000 / MAX_GAMELOOP_CPS ;
    
    private static final int VIBRATION_MILLIS = 200;
    
    // shared direction constants, counter clockwise order
    static final int DIRECTION_NONE = -1;
    static final int DIRECTION_DOWN = 0;
    static final int DIRECTION_RIGHT = 1;
    static final int DIRECTION_UP = 2;
    static final int DIRECTION_LEFT = 3;
    
    public static final int STATUS_PLAYING = 0;
    public static final int STATUS_GAME_OVER = 1;
    public static final int STATUS_LEVEL_COMPLETE = 2;
    public int gameStatus = STATUS_PLAYING;
    
    public Graphics g;
    
    public World world;
    public Alien aliens[];
    public GameSprite potions[];
    public LayerManager layerManager;
    public Spaceman spaceman;
    
    public int score = 000;
    
    public Image tilesImage;
    public Image spacemanImage;
    public Image alienImage;
    public Image potionImage;
    
    public GameScreen(AlienXMIDlet midlet) {
        super(true);
        instance = this;
        this.midlet = midlet;
        
        g = this.getGraphics();
        
        try {
            spacemanImage = Image.createImage("/spaceman.png");
        } catch (Exception e) {
        }
        
        try {
            alienImage = Image.createImage("/alien.png");
        } catch (Exception e) {
        }
        
        try {
            potionImage = Image.createImage("/potion.png");
        } catch (Exception e) {
        }
        
        
        try {
            tilesImage = Image.createImage("/tiles.png");
        } catch (Exception e) {
        }
        
    }
    
    public void init() {
        layerManager = new LayerManager();
        
        world = new World(tilesImage);
        
        spaceman = new Spaceman(spacemanImage);
        spaceman.setPosition(100,64);
        layerManager.append(spaceman);
        
        aliens = new Alien[4];
        aliens[0] = new Alien(alienImage);
        aliens[0].setPosition(24,41);
        layerManager.append(aliens[0]);
        
        aliens[1] = new Alien(alienImage);
        aliens[1].setPosition(59,167);
        layerManager.append(aliens[1]);
        
        aliens[2] = new Alien(alienImage);
        aliens[2].setPosition(133,9);
        layerManager.append(aliens[2]);
        
        aliens[3] = new Alien(alienImage);
        aliens[3].setPosition(178,200);
        layerManager.append(aliens[3]);
        
        //potions = new GameSprite [1];
        potions = new GameSprite [5];
        for (int i = 0; i < potions.length; i++) {
            potions[i] = new GameSprite(potionImage, 13, 16);
            layerManager.append(potions[i]);
        }
        
        potions[0].setPosition(14,198);
        potions[1].setPosition(227,21);
        potions[2].setPosition(227,175);
        potions[3].setPosition(34,84);
        potions[4].setPosition(122,120);

        // add tiles last, behind sprites
        layerManager.append(world);
        
        gameStatus = STATUS_PLAYING;
        score = 0;
        
    }
    
    public synchronized void start() {
        SoundEffects.getInstance().startShoutSound();
        animationThread = new Thread(this);
        animationThread.start();
    }
    
    public synchronized void stop() {
        animationThread = null;
    }
    
    public void run() {
        Thread currentThread = Thread.currentThread();
        long timeElapsed = 0;
        
        try {
            // The game loop ends when animationThread is set to null, or when
            // it is subsequently set to a new thread; either way, the
            // current thread should terminate
            
            while (currentThread == animationThread) {
                timeElapsed = System.currentTimeMillis();
                
                if (gameStatus == STATUS_PLAYING) {
                    
                    // If player presses two or more direction buttons, we
                    // ignore them all. But pressing fire is independent. The
                    // code below also ignores direction buttons if
                    // GAME_A..GAME_D are pressed.
                    
                    int keyStates = getKeyStates();
                    keyStates &= ~FIRE_PRESSED;
                    int direction = (keyStates == UP_PRESSED) ? DIRECTION_UP :
                        (keyStates == LEFT_PRESSED) ? DIRECTION_LEFT:
                            (keyStates == DOWN_PRESSED) ? DIRECTION_DOWN :
                                (keyStates == RIGHT_PRESSED) ?
                                    DIRECTION_RIGHT : DIRECTION_NONE;
                    
                    spaceman.tick(direction);
                    
                    boolean levelComplete = true;
                    for (int i = 0; i < potions.length; i++) {
                        if (potions[i] != null) {
                            levelComplete = false;
                            if (spaceman.collidesWith(potions[i], false)) {
                                // spaceman picks up a potion
                                midlet.playSound(AlertType.INFO);
                                spaceman.regainPower(7);
                                score++;
                                layerManager.remove(potions[i]);
                                potions[i] = null;
                            }
                        }
                    }
                    
                    // move aliens and check if the spaceman bumps
                    // into any of them
                    for (int i = 0; i < aliens.length; i++) {
                        aliens[i].tick();
                        
                        if (spaceman.collidesWith(aliens[i], false)) {
                            spaceman.losePower(spaceman.MAX_POWER / 4 - 1);
                        }
                        
                        for (int j = 0; j < potions.length; j++) {
                            if (potions[j] != null &&
                                    aliens[i].collidesWith(potions[j], false)) {
                                // an alien picked up a potion
                                midlet.vibrate(VIBRATION_MILLIS);
                                midlet.playSound(AlertType.WARNING);
                                layerManager.remove(potions[j]);
                                potions[j] = null;
                            }
                        }
                    }
                    
                    // check is spaceman runs out of power
                    if (spaceman.power <= 0) {
                        gameStatus = STATUS_GAME_OVER;
                        SoundEffects.getInstance().startGameOverSound();
                        
                        // or all potions have been found
                    } else if (levelComplete) {
                        gameStatus = STATUS_LEVEL_COMPLETE;
                        SoundEffects.getInstance().startLevelCompleteSound();
                    }
                }
                
                draw();
                
                timeElapsed = System.currentTimeMillis() - timeElapsed;
                
                if (timeElapsed < Math.max(MIN_MILLIS_PER_FRAME - timeElapsed, 1)) {
                    synchronized (this) {
                        wait(MIN_MILLIS_PER_FRAME - timeElapsed);
                    }
                } else {
                    currentThread.yield();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public void draw() {
        
        // clear screen (only visible if display larger that tiled layer)
        g.setColor(0x000066ff);
        g.fillRect(0, 0, getWidth(), getHeight());
        
        // If the screen is bigger than the canvas, we center the tiles
        // in the screen. Otherwise we center the screen on the focus,
        // except that we don't scroll beyond the edges of the screen.
        
        int dx = origin(spaceman.getX() + spaceman.getWidth() / 2,
                world.getWidth(),
                getWidth());
        
        int dy = origin(spaceman.getY() + spaceman.getHeight() / 2,
                world.getHeight(),
                getHeight());
        
        g.setClip(dx, dy, world.getWidth(), world.getHeight());
        g.translate(dx, dy);
        
        // draw tiles and sprites
        layerManager.paint(g, 0, 0);
        
        // undo both clip and translation
        g.translate(-dx, -dy);
        g.setClip(0, 0, getWidth(), getHeight());
        
        // draw score and power status
        g.setColor(0x00ffffff);
        g.fillRect(5, 5, spaceman.power/2, 4);
        g.drawString("00" + Integer.toString(score),
                    getWidth() - 20, 2, Graphics.TOP | Graphics.LEFT);
        
        // if game over or level completed, display message
        if (gameStatus == STATUS_GAME_OVER) {
            
            drawOutlinedString("GAME OVER",
                    getWidth() / 2,
                    getHeight() / 2,
                    Graphics.HCENTER | Graphics.TOP);
            
        } else if (gameStatus == STATUS_LEVEL_COMPLETE) {
            
            drawOutlinedString("LEVEL CLEARED",
                    getWidth() / 2,
                    getHeight() / 2,
                    Graphics.HCENTER | Graphics.TOP);
        }
        
        flushGraphics();
        
    }
    
    private void drawOutlinedString(String s, int x, int y, int anchor) {
        g.setColor(0x00000000);
        g.drawString(s, x+1, y, anchor);
        g.drawString(s, x-1, y, anchor);
        g.drawString(s, x, y+1, anchor);
        g.drawString(s, x, y-1, anchor);
        g.drawString(s, x+2, y+2, anchor);
        g.setColor(0x00ffffff);
        g.drawString(s, x, y, anchor);
    }
    
    // If the screen is bigger than the world, we center the world
    // in the screen. Otherwise we center the screen on the focus, except
    // that we don't scroll beyond the edges of the world.
    private int origin(int focus, int worldLength, int screenLength) {
        int origin;
        if (screenLength >= worldLength) {
            origin = (screenLength - worldLength) / 2;
        } else if (focus <= screenLength / 2) {
            origin = 0;
        } else if (focus >= (worldLength - screenLength / 2)) {
            origin = screenLength - worldLength;
        } else {
            origin = screenLength / 2 - focus;
        }
        return origin;
    }
    
    public void keyPressed(int keyCode) {
        // The constructor suppresses key events for game keys, so we'll
        // only get key events for non-game keys. The number keys, * & #
        // have positive keyCodes, so negative keyCodes mean non-game
        // special keys like soft-keys. We'll use key-presses on special
        // keys to take us to the menu.
        if (keyCode < 0) {
            stop();
            midlet.gameScreenMenu();
        }
    }
}
