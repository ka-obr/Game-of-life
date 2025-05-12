import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class Gameplay {
    private boolean running = true;
    private Window window;
    World world;

    public Gameplay(World world) {
        this.world = world;
        window = new Window(this);

        Human human = new Human(new Point(0, 0), world, 1);
        world.addOrganism(human);
        world.addSheep(1, 1);
        world.addWolf(1, 1);

        window.repaint();
    }

    public World getWorld() {
        return world;
    }

    public void handleInput(String input) {
        if (input.equalsIgnoreCase("q")) {
            window.dispose();
        } else {
            world.update(input);
        }
    }
}
