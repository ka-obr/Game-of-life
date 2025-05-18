import javax.swing.*;
import java.awt.*;
import java.io.Serializable;

public class Human extends Animal implements Serializable {
    private static final ImageIcon humanIcon = new ImageIcon("images/human.png");
    public static final Image scaledHumanIcon = humanIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);
    private static final long serialVersionUID = 1L;

    private boolean specialAbilityActive;
    private int specialAbilityCooldown;
    private int specialAbilityCounter;

    public boolean getSpecialAbilityActive() {
        return specialAbilityActive;
    }

    public void setSpecialAbilityActive(boolean specialAbilityActive) {
        this.specialAbilityActive = specialAbilityActive;
    }

    public int getSpecialAbilityCooldown() {
        return specialAbilityCooldown;
    }


    public Human(Point location, World world, int age) {
        super(5, 4, location, world, age);
        this.position = location;
        this.world = world;
        this.age = age;
        this.specialAbilityActive = false;
        this.specialAbilityCooldown = 0;
        this.specialAbilityCounter = 5;
    }

    @Override
    public void action(String input) {
        age++;
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
                specialAbilityCooldown = 5;
                specialAbilityCounter = 5;
                String message = "Human special ability deactivated!";
                world.getWindow().addMessage(message);
            }
        }
    }

    @Override
    public void action() {
        age++;
    }

    @Override
    public ImageIcon getIcon() {
        return humanIcon;
    }
}
