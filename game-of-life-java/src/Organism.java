import lib.Size;

import javax.swing.*;
import java.awt.*;

public abstract class Organism {
    protected int strength;
    protected int initiative;
    protected Point position;
    protected World world;
    protected int age;

    public Organism(int strength, int initiative, Point position, World world, int age) {
        this.strength = strength;
        this.initiative = initiative;
        this.position = position;
        this.world = world;
        this.age = age;
    }

    public int getStrength() {
        return strength;
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

    public void action() {

    }

    public void collision(Organism other) {

    }

    public ImageIcon getIcon() {
        return null; // Domyślnie brak ikony
    }
}