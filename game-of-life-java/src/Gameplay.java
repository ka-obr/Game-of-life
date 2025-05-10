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

        // Dodanie owcy na losowej pozycji
        Random random = new Random();
        int randomX = random.nextInt(world.getSize().x);
        int randomY = random.nextInt(world.getSize().y);
        Sheep sheep = new Sheep(new Point(randomX, randomY), world, 1);
        world.addOrganism(sheep);

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
