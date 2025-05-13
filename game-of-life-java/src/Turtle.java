import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class Turtle extends Animal {
    public static final ImageIcon turtleIcon = new ImageIcon("images/turtle.png");
    public static final Image scaledTurtleIcon = turtleIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Turtle(Point position, World world, int age) {
        super(2, 1, position, world, age); // Strength = 2, Initiative = 1
    }

    @Override
    public ImageIcon getIcon() {
        return turtleIcon; // Zwracanie zcache'owanej ikony
    }

    @Override
    protected boolean haveSavedAttack(Organism other) {
        if(other instanceof Antelope) {
            other.escapeCollision(this);
            return false;
        }
        return false;
    }

    @Override
    public void move() {
        Random random = new Random();
        if (random.nextInt(100) < 25) { // 25% szans na ruch
            Point newPos = world.generateRandomPosition(position);
            if (newPos != null) {
                Organism other = world.getOrganismAtPosition(newPos);
                if(haveSavedAttack(other)) {
                    return;
                }
                other = world.getOrganismAtPosition(newPos);
                if (other != null) {
                    collision(other);
                } else {
                    position = newPos; // Przesuwamy organizm na nową pozycję
                }
            }
        }
    }
}
