import java.awt.*;
import java.lang.reflect.InvocationTargetException;

public class Gameplay {
    private Window window;
    private World world;
    private Human human;
    private WorldFileManager fileManager;

    public void setHuman(Human human) {
        this.human = human;
    }

    public Gameplay(World world) {
        this.world = world;
        this.fileManager = new WorldFileManager();
        window = new Window(this);
        world.setWindow(window);

        human = new Human(new Point(0, 0), world, 1);
        world.addOrganism(human);
        world.createOrganism(Sheep.class, 2, 1);
        world.createOrganism(Wolf.class, 2, 1);
        world.createOrganism(Fox.class, 2, 1);
        world.createOrganism(Turtle.class, 2, 1);
        world.createOrganism(Antelope.class, 2, 1);
        world.createOrganism(Grass.class, 2, 1);
        world.createOrganism(Dandelion.class, 2, 1);
        world.createOrganism(Guarana.class, 2, 1);
        world.createOrganism(Nightshade.class, 2, 1);
        world.createOrganism(Hogweed.class, 2, 1);

        window.repaint();
    }

    private void handleHumanSpecialAbility(Human human) {
        if (human == null || !world.getOrganisms().contains(human)) {
            String message = "Human is dead!";
            world.getWindow().addMessage(message);
        } else if (human.getSpecialAbilityCooldown() > 0) {
            String message = "Human special ability is on cooldown for " + human.getSpecialAbilityCooldown() + " turns!";
            world.getWindow().addMessage(message);
        } else if (human.getSpecialAbilityActive()) {
            String message = "Human special ability is already active!";
            world.getWindow().addMessage(message);
        } else { // human != null
            human.setSpecialAbilityActive(true);
            String message = "Human special ability activated!!!";
            world.getWindow().addMessage(message);
        }
    }

    public World getWorld() {
        return world;
    }

    private void loadWorld() {
        World loaded = fileManager.loadWorldFromFile();
        if (loaded != null) {
            this.world = loaded;
            world.setWindow(window);
            world.setWorldReferenceForAll();
            this.human = (Human) world.getOrganisms().stream()
                    .filter(o -> o instanceof Human)
                    .findFirst()
                    .orElse(null);
            window.addMessage("World loaded from file.");
            window.setWorld(loaded);
            window.repaint();
        }
    }

    public void handleInput(String input) {
        if (input.equalsIgnoreCase("q")) {
            window.dispose();
        } else if (input.equalsIgnoreCase("r")) {
            handleHumanSpecialAbility(human);
        } else if (input.equalsIgnoreCase("s")) {
            fileManager.saveWorldToFile(world);
        } else if (input.equalsIgnoreCase("l")) {
            loadWorld();
        }
        else {
            window.clearMessages();
            world.update(input);
        }
    }
}
