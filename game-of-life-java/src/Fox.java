import javax.swing.*;
import java.awt.*;

public class Fox extends Animal {
    public static final ImageIcon foxIcon = new ImageIcon("images/fox.png");
    public static final Image scaledFoxIcon = foxIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Fox(Point position, World world, int age) {
        super(3, 7, position, world, age); // Strength = 3, Initiative = 7
    }

    @Override
    public ImageIcon getIcon() {
        return foxIcon; // Zwracanie zcache'owanej ikony
    }

    @Override
    public void move() {
        Point newPos = world.generateSafePosition(position);
        if (newPos != null) {
            Organism other = world.getOrganismAtPosition(newPos);
            if(haveSavedAttack(other)) {
                return;
            }
            other = world.getOrganismAtPosition(newPos);
            if (other != null) {
                collision(other);
            } else {
                position = newPos;
            }
        }
    }
}
