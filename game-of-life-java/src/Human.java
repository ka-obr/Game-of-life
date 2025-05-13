import javax.swing.*;
import java.awt.*;

public class Human extends Animal {
    // Dodane zmienne specjalnej umiejętności
    private boolean specialAbilityActive;
    private int specialAbilityCooldown;
    private int specialAbilityCounter;

    // Dodane gettery i setter dla zmiennych specjalnej umiejętności
    public boolean getSpecialAbilityActive() {
        return specialAbilityActive;
    }

    public void setSpecialAbilityActive(boolean specialAbilityActive) {
        this.specialAbilityActive = specialAbilityActive;
    }

    public int getSpecialAbilityCooldown() {
        return specialAbilityCooldown;
    }

    public int getSpecialAbilityCounter() {
        return specialAbilityCounter;
    }

    public static final ImageIcon humanIcon = new ImageIcon("images/human.png");

    public Human(World world) {
        super(5, 4, new Point(0, 0), world, 0); // Siła = 5, Inicjatywa = 4, pozycja (0,0)
    }

    public Human(Point location, World world, int age) {
        super(5, 4, location, world, age); // Siła = 5, Inicjatywa = 4
        this.position = location; // Ustawienie pozycji na podaną
        this.world = world; // Ustawienie świata
        this.age = age; // Ustawienie wieku
        this.specialAbilityActive = false;
        this.specialAbilityCooldown = 0;
        this.specialAbilityCounter = 5;
    }

    // Zmieniona metoda action(input) umożliwiająca poruszanie się człowieka i podejmowanie walki, jeśli pole jest zajęte
    @Override
    public void action(String input) {
        age++; // Inkrementacja wieku
        Point newPos = null;
            if (input.equalsIgnoreCase("up")) {
                newPos = new Point(position.x, position.y - 1);
            } else if (input.equalsIgnoreCase("down")) {
                newPos = new Point(position.x, position.y + 1);
            } else if (input.equalsIgnoreCase("left")) {
                newPos = new Point(position.x - 1, position.y);
            } else if (input.equalsIgnoreCase("right")) {
                newPos = new Point(position.x + 1, position.y);
            }

            Organism occupant = world.getOrganismAtPosition(newPos);
            if (newPos != null && world.isWithinBounds(newPos) && !haveSavedAttack(occupant)) {
                occupant = world.getOrganismAtPosition(newPos);
                if (occupant != null) {
                    // Jeśli pole jest zajęte, wywołujemy kolizję (human może zabić przeciwnika)
                    collision(occupant);
                } else {
                    position = newPos;
                }
            }

        if(specialAbilityCooldown > 0) {
            specialAbilityCooldown--;
        }

        if(specialAbilityActive && specialAbilityCooldown == 0 && this != null) {
            world.killNeighbors(position, 0);
            specialAbilityCounter--;

            if(specialAbilityCounter == 0) {
                specialAbilityActive = false;
                specialAbilityCooldown = 5; // Ustawienie cooldownu na 5 tur
                specialAbilityCounter = 5; // Resetowanie licznika umiejętności
                System.out.println("Human special ability deactivated");
            }
        }
    }

    // Opcjonalnie: Jeśli action() bez parametrów ma pozostać, można go zdefiniować tak:
    @Override
    public void action() {
        age++; // Ruch bez podanego inputa nie jest wykonywany
    }

    @Override
    public ImageIcon getIcon() {
        return humanIcon;
    }
}
