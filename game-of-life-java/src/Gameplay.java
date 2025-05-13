import java.awt.*;

public class Gameplay {
    private boolean running = true;
    private Window window;
    private World world;
    private Human human; // Dodana zmienna pola dla człowieka

    public Gameplay(World world) {
        this.world = world;
        window = new Window(this);
        world.setWindow(window);

        // Inicjalizacja człowieka na pozycji (0,0)
        human = new Human(new Point(0, 0), world, 1);
        world.addOrganism(human);
        world.addSheep(2, 1);
        world.addWolf(2, 1);
        world.addFox(2, 1);
        world.addTurtle(2, 1);
        world.addAntelope(2, 1); // Dodanie antylopy

        window.repaint();
    }

    private void handleHumanSpecialAbility(Human human) {
        if (human == null || !world.getOrganisms().contains(human)) {
            String message = "Human is dead!";
            world.getWindow().addMessage(message); // Dodanie wiadomości do okna
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

    public void handleInput(String input) {
        if (input.equalsIgnoreCase("q")) {
            window.dispose();
        } else if (input.equalsIgnoreCase("r")) {
            handleHumanSpecialAbility(human);
        } else {
            world.update(input);
        }
    }
}
