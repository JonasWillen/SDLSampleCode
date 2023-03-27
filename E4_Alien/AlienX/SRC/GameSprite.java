import javax.microedition.lcdui.*;
import javax.microedition.lcdui.game.*;

public class GameSprite extends javax.microedition.lcdui.game.Sprite {
    
    protected static final int STAND = 0;
    protected static final int MOVE = 1;
    
    //counter clockwise order
    public static final int DIRECTION_NONE = -1;
    public static final int DIRECTION_DOWN = 0;
    public static final int DIRECTION_RIGHT = 1;
    public static final int DIRECTION_UP = 2;
    public static final int DIRECTION_LEFT = 3;
    
    public static final int DIRECTION_VECTOR_X[] = {0, 1, 0, -1}; //d,r,u,l
    public static final int DIRECTION_VECTOR_Y[] = {1, 0, -1, 0};
    
    public static final int REL_LEFT = 1;
    public static final int REL_IN_FRONT_OF = 0;
    public static final int REL_RIGHT = -1;
    public static final int REL_RANDOM = 47;
    
    public int speed;
    public int direction = DIRECTION_RIGHT;
    
    protected boolean isMoving = false;
    public int animationSpeed;
    protected int animationCounter = 0;
    
    public Image spriteImage = null;
    public static GameScreen gameScreen = GameScreen.instance;
    
    public GameSprite(Image image, int frameWidth, int frameHeight) {
        super(image, frameWidth, frameHeight);
        this.spriteImage = image;
    }
    
/*
 * Move sprite, while checking for *tile* collisions:
 * Do a temporary move to <speed> pixels in the moving direction,
 * and checking if the area contains an impassable tile, and if so,
 * check if player sprite collides with the tile.
 * Count down length to reach the max number of pixels to move.
 */
    protected void move() {
        
        World world = gameScreen.world;
        
        int originalX = getX();
        int originalY = getY();
        
        int length = speed + 1;

        // Collision detection only works when visible, so make sure we are
        boolean visible = isVisible();
        if (!visible)
            setVisible(true);
        
        do {
            length--;
            
            setPosition(originalX + length * DIRECTION_VECTOR_X[direction],
                    originalY + length * DIRECTION_VECTOR_Y[direction]);
            
        } while (world.collidesWithImpassableTile(this) && (length > 0));
        
        isMoving = (length > 0);

        //Restore visibility
        setVisible(visible);
        
    }
    
    public void turn(int relDirection) {
        if (relDirection == REL_RANDOM) {
            do {
                // get an integer between -1 and 1
                relDirection = Math.abs((int)(System.currentTimeMillis() % 3)) - 1;
            } while (relDirection == 0);
        }
        
        direction += relDirection;

        if (direction > 3)
            direction -= 4;
        else if (direction < 0)
            direction += 4;
    }
}
