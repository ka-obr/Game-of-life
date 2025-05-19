import javax.swing.*;
import java.awt.*;

public class Nightshade extends Plant {
    private static final ImageIcon nightshadeIcon = new ImageIcon("images/nightshade.png");
    public static final Image scaledNightshadeIcon = nightshadeIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Nightshade(Point position, World world, int age) {
        super(99, position, world, age);
    }

    @Override
    public ImageIcon getIcon() {
        return nightshadeIcon;
    }

    @Override
    public void collision(Organism other) {
        String message = "Nightshade was eaten by " + other.getClass().getSimpleName();
        world.getWindow().addMessage(message);
        world.removeOrganism(this);
        world.removeOrganism(other);
    }
}
