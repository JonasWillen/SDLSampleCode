import javax.microedition.lcdui.*;

public class Alien extends GameSprite {
    static final int WIDTH = 15;
    static final int HEIGHT = 15;
    
    public static int SCANNER_LENGTH = 8;
    
    private int[][][] animations = {{{0},   // stand facing downwards
    {0, 1}}};  // move downwards
    
    public Alien(Image i) {
        super(i, WIDTH, HEIGHT);
        defineReferencePixel(WIDTH / 2, HEIGHT / 2); // transform around
        defineCollisionRectangle(2, 2, WIDTH - 2, HEIGHT - 2);
        speed = 1;
        animationSpeed = 2;
    }
    
    public void tick() {
        move();
        if (isMoving) {  // no collision?
            if (isTargetAt(REL_LEFT)) {
                // turn left if there is a potion there
                turn(REL_LEFT);
            } else if (isTargetAt(REL_RIGHT)) {
                // turn right if there is a potion there
                turn(REL_RIGHT);
            } // else just continue
        } else {
            turn(REL_RANDOM);
        }
        
        
        if (isMoving) {
            advanceRunningAnimation();
        } else {
            setStandingAnimation();
        }
        
    }
    
    private void advanceRunningAnimation() {
        int[] sequence;
        
        sequence = animations[DIRECTION_DOWN][MOVE];
        
        if (direction == DIRECTION_LEFT) {
            setTransform(this.TRANS_ROT90);
        } else if (direction == DIRECTION_UP) {
            setTransform(this.TRANS_ROT180);
        } else if (direction == DIRECTION_RIGHT) {
            setTransform(this.TRANS_ROT270);
        } else {
            setTransform(TRANS_NONE);
        }
        
        animationCounter++;
        setFrame(sequence[animationCounter % sequence.length]);
    }
    
    private void setStandingAnimation() {
        int[] sequence;
        
        sequence = animations[DIRECTION_DOWN][STAND];
        
        if (direction == DIRECTION_LEFT) {
            setTransform(this.TRANS_ROT90);
        } else if (direction == DIRECTION_UP) {
            setTransform(this.TRANS_ROT180);
        } else if (direction == DIRECTION_RIGHT) {
            setTransform(this.TRANS_ROT270);
        } else {
            setTransform(TRANS_NONE);
        }
        
    }
    
    protected boolean isTargetAt(int relDirection) {
        GameSprite potions[] = gameScreen.potions;
        int absDirection = direction + relDirection;

        if (absDirection > 3)
            absDirection -= 4;
        else if (absDirection < 0)
            absDirection += 4;

        // create a temporary sprite and use its collision detection,
        // to check if there is anything to pick up nearby
        GameSprite tmpSprite = new GameSprite(this.spriteImage, WIDTH, HEIGHT);
        tmpSprite.setPosition(getX(), getY());
        tmpSprite.defineCollisionRectangle(
                SCANNER_LENGTH * DIRECTION_VECTOR_X[absDirection],
                SCANNER_LENGTH * DIRECTION_VECTOR_Y[absDirection],
                SCANNER_LENGTH,
                SCANNER_LENGTH);
        
        // aliens are also interested in potions...
        for (int i = 0; i < potions.length; i++) {
            if (potions[i] != null) {
                if (tmpSprite.collidesWith(potions[i], false))
                    return true;
            }
        }
        
        // ...and also want to bug the spaceman
        if (tmpSprite.collidesWith(gameScreen.spaceman, false))
            return true;
        
        return false;
    }
}

