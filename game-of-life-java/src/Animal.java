import lib.Size;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public abstract class Animal extends Organism {
    public Animal(int strength, int initiative, Point position, World world, int age) {
        super(strength, initiative, position, world, age);
    }

    public void move() {
        Point newPos = world.generateRandomPosition(position);
        if (newPos != null) {
            Organism other = world.getOrganismAtPosition(newPos);
            if (other != null) {
                collision(other);
            } else {
                position = newPos; // Przesuwamy organizm na nową pozycję
            }
        }
    }

    @Override
    public void collision(Organism other) {
        if (this.getClass().equals(other.getClass())) {
            if (other.getAge() == 0) {
                return; // Nie rozmnażaj się z nowo narodzonym organizmem
            }

            // Reprodukcja
            Point newPos = world.generateRandomPosition(position);
            if (newPos != null && !world.isTileOccupied(newPos)) {
                if (this instanceof Sheep) {
                    Sheep baby = new Sheep(newPos, world, 0);
                    world.addOrganism(baby);
                    System.out.println("Reproduction occurred: new Sheep at " + newPos);
                }
            }
        } else {
            // Walka
            if (this.getStrength() >= other.getStrength()) {
                world.removeOrganism(other);
                System.out.println(this.getClass().getSimpleName() + " wins against " + other.getClass().getSimpleName());
            } else {
                world.removeOrganism(this);
                System.out.println(other.getClass().getSimpleName() + " wins against " + this.getClass().getSimpleName());
            }
        }
    }

    @Override
    public void action() {
        age++; // Inkrementacja wieku
        if (age > 1) {
            move(); // Ruch zwierzęcia
        }
    }
}
