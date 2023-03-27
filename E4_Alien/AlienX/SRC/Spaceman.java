import javax.microedition.lcdui.*;

public class Spaceman extends GameSprite {
    public static final int WIDTH = 16;
    public static final int HEIGHT = 16;
    
    public static final int MAX_POWER = 100;
    public int power = MAX_POWER;
    public static final int MAX_IMMUNITY_TIMER = 30;
    
    public boolean isImmune = false;
    private int immunityTimer = 0;
    
    private int[][][] animations = {
        {{0},      // standing downwards
         {0, 1}},  // moving downwards
        {{2},      // standing facing right
         {2, 3}},  // moving facing right
        {{4},      // standing upwards
         {4, 5}}   // moving upwards
    };

      public Spaceman(Image i) {
          super(i, WIDTH, HEIGHT);
          defineReferencePixel(WIDTH / 2, HEIGHT / 2);
          defineCollisionRectangle(4, 10, WIDTH - 8, HEIGHT - 10);
          speed = 3;
          animationSpeed = 2;
      }
      
      public void tick(int direction) {
          if (direction == DIRECTION_NONE) {
              isMoving = false;
              animationCounter = 0;
          } else {
              this.direction = direction;
              move();
          }
          
          if (isMoving) {
              advanceRunningAnimation();
          } else {
              setStandingAnimation();
          }
          
          // spaceman is immune to aliens for a few ticks after collision
          if (immunityTimer > 0) {
              immunityTimer--;
              if ((immunityTimer & 1) == 1)
                  setVisible(false);
              else
                  setVisible(true);
          } else {
              isImmune = false;
          }
      }
      
      private void advanceRunningAnimation() {
          int[] sequence;
          
          if (direction == DIRECTION_LEFT) {
              sequence = animations[DIRECTION_RIGHT][MOVE];
              setTransform(TRANS_MIRROR);
          } else {
              sequence = animations[direction][MOVE];
              setTransform(TRANS_NONE);
          }
          animationCounter++;
          
          setFrame(sequence[animationCounter % sequence.length]);
      }
      
      
      private void setStandingAnimation() {
          if (direction == DIRECTION_LEFT) {
              setFrame(animations[DIRECTION_RIGHT][STAND][0]);
              setTransform(TRANS_MIRROR);
          } else {
              setFrame(animations[direction][STAND][0]);
              setTransform(TRANS_NONE);
          }
      }
      
      public void regainPower(int amount) {
          power += amount;
          if (power > MAX_POWER)
              power = MAX_POWER;
      }
      
      public void losePower(int amount) {
          if (!isImmune) {
              power -= amount;
              immunityTimer = MAX_IMMUNITY_TIMER;
              isImmune = true;
          }
      }
}
