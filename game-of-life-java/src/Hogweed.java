import javax.swing.*;
import java.awt.*;

public class Hogweed extends Plant {
    private static final ImageIcon hogweedIcon = new ImageIcon("images/hogweed.png");
    public static final Image scaledHogweedIcon = hogweedIcon.getImage()
            .getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Hogweed(Point position, World world, int age) {
        super(10, position, world, age); // Siła 10, inicjatywa zawsze 0
    }

    @Override
    public ImageIcon getIcon() {
        return hogweedIcon;
    }

    @Override
    public void action() {
        if(age != 0) {
            world.killNeighbors(position, 1);

            if(canReproduceThisTurn() && hasFreeSpace()) {
                reproduce(position);
            }
        }
        age++;
    }

    @Override
    public void collision(Organism other) {
        world.removeOrganism(other);
        world.removeOrganism(this);
        String message = "Hogweed was eaten by " + other.getClass().getSimpleName();
        world.getWindow().addMessage(message);
    }
}
