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

        world.addSheep(1, 1);
        world.addWolf(1, 1);

        window.repaint();
    }

    public World getWorld() {
        return world;
    }

    public void handleInput(String input) {
        if (input.equalsIgnoreCase("t")) {
            world.update();
        } else if (input.equalsIgnoreCase("q")) {
            window.dispose();
        }
    }
}
