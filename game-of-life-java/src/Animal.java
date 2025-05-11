import lib.Size;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public abstract class Animal extends Organism {
    public Animal(int strength, int initiative, Point position, World world, int age) {
        super(strength, initiative, position, world, age);
    }

    public void createAnimalByType(Class<? extends Animal> animalType, Point position) {
        if (animalType.equals(Sheep.class)) {
            Sheep baby = new Sheep(position, world, 0);
            world.addOrganism(baby);
            System.out.println("Reproduction occurred: new Sheep at " + position);
        } else if (animalType.equals(Wolf.class)) {
            Wolf baby = new Wolf(position, world, 0);
            world.addOrganism(baby);
            System.out.println("Reproduction occurred: new Wolf at " + position);
        }
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
        if (this.getClass().equals(other.getClass())) { // ten sam gatunek
            if (other.getAge() == 0) {
                // Nie reprodukujemy się z noworodkiem, pozostajemy na miejscu (ruch nie jest wykonywany)
                return;
            }
            // Próba reprodukcji - nie zmieniamy pozycji atakującego
            Point newPos = world.generateRandomPosition(position);
            if (newPos != null && !world.isTileOccupied(newPos)) {
                createAnimalByType(this.getClass(), newPos);
            }
        } else { // różne gatunki - walka
            if (this.getStrength() >= other.getStrength()) {
                world.removeOrganism(other);
                // Po wygranej walce przechodzimy na pozycję przeciwnika
                this.position = other.getPosition();
                System.out.println("Move because win the fight");
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