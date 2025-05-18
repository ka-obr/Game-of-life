import javax.swing.*;
import java.awt.*;

public class Antelope extends Animal {
    private static final ImageIcon antelopeIcon = new ImageIcon("images/antelope.png");
    public static final Image scaledAntelopeIcon = antelopeIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Antelope(Point position, World world, int age) {
        super(4, 4, position, world, age);
    }

    @Override
    public ImageIcon getIcon() {
        return antelopeIcon;
    }


    @Override
    protected int escapeCollision(Organism other) {
        int randomNumber = (int) (Math.random() * 2 + 1);
        if (randomNumber == 1 && !other.getClass().equals(this.getClass()) && !(other instanceof Plant)) {
            Point destination = world.getRandomFreeSpaceAround(position);
            if (world.isWithinBounds(destination)) {
                position = destination;
                setHasActed(true);
                return 1;
            }
        }
        return 0;
    }

    @Override
    protected boolean haveSavedAttack(Organism other) {
        if(other instanceof Turtle && this.getStrength() < 5) {
            return true;
        }
        return false;
    }

    @Override
    public void move() {
        if(getHasActed()) {
            return;
        }
        Point newPos = world.getRandomSpaceDoubleMove(position);
        if (newPos != null) {
            Organism other = world.getOrganismAtPosition(newPos);
            if(haveSavedAttack(other)) {
                return;
            }
            if (other != null) {
                collision(other);
                setHasActed(true);
            } else {
                position = newPos;
            }
        }
    }
}
