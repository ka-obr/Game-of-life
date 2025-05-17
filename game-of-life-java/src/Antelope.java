import javax.swing.*;
import java.awt.*;

public class Antelope extends Animal {
    public static final ImageIcon antelopeIcon = new ImageIcon("images/antelope.png");
    public static final Image scaledAntelopeIcon = antelopeIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Antelope(Point position, World world, int age) {
        super(4, 4, position, world, age); // Strength = 4, Initiative = 4
    }

    @Override
    public ImageIcon getIcon() {
        return antelopeIcon; // Zwracanie zcache'owanej ikony
    }


    @Override
    protected int escapeCollision(Organism other) {
        int randomNumber = (int) (Math.random() * 2 + 1);
        if (randomNumber == 1 && !other.getClass().equals(this.getClass()) && !(other instanceof Plant)) {
            Point destination = world.getRandomFreeSpaceAround(position);
            if (world.isWithinBounds(destination)) {
                position = destination; // Przesunięcie na nową pozycję
                setHasActed(true);
                return 1; // Ucieczka zakończona sukcesem
            }
        }
        return 0; // Ucieczka nie powiodła się
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
