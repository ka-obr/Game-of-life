import lib.Size;

import javax.swing.*;
import java.awt.*;
import java.io.Serializable;

public abstract class Organism implements Serializable {
    private static final long serialVersionUID = 1L;

    private int strength;
    protected int initiative;
    protected Point position;
    protected transient World world;
    protected int age;
    private boolean hasActed;

    public Organism(int strength, int initiative, Point position, World world, int age) {
        this.strength = strength;
        this.initiative = initiative;
        this.position = position;
        this.world = world;
        this.age = age;
    }

    public void setWorld(World world) {
        this.world = world;
    }

    public int getStrength() {
        return strength;
    }

    public void setStrength(int strength) {
        this.strength = strength;
    }

    protected void plantCollision(Organism plant, Organism animal) {
        //
    }

    public int getInitiative() {
        return initiative;
    }

    public Point getPosition() {
        return position;
    }

    public int getAge() {
        return age;
    }

    public boolean getHasActed() {
        return hasActed;
    }

    public void setHasActed(boolean hasActed) {
        this.hasActed = hasActed;
    }

    public void action() {

    }

    protected int escapeCollision(Organism other) {
        return 0;
    }

    public void action(String input) {
        action();
    }

    public void collision(Organism other) {
        // Domyślna implementacja, jeśli nie zostanie nadpisana w klasie potomnej
    }

    public ImageIcon getIcon() {
        return null;
    }
}
