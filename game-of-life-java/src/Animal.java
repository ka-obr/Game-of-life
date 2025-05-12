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
        } else if (animalType.equals(Fox.class)) {
            Fox baby = new Fox(position, world, 0);
            world.addOrganism(baby);
            System.out.println("Reproduction occurred: new Fox at " + position);
        } else if (animalType.equals(Turtle.class)) {
            Turtle baby = new Turtle(position, world, 0);
            world.addOrganism(baby);
            System.out.println("Reproduction occurred: new Fox at " + position);
        }
    }

    protected boolean haveSavedAttack(Organism other) {
        if(other instanceof Turtle && this.getStrength() < 5) {
            return true;
        }
        return false;
    }

    public void move() {
        Point newPos = world.generateRandomPosition(position);
        if (newPos != null) {
            Organism other = world.getOrganismAtPosition(newPos);
            if(haveSavedAttack(other)) {
                return;
            }
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
            if (this.getAge() == 0 || other.getAge() == 0) {
                // Nie reprodukujemy się z noworodkiem, pozostajemy na miejscu, bez walki
                return;
            }
            // Próba reprodukcji: tylko organizmy tego samego gatunku mogą się rozmnażać
            Point newPos = world.generateRandomPosition(position);
            if (newPos != null && !world.isTileOccupied(newPos)) {
                createAnimalByType(this.getClass(), newPos);
                System.out.println("Reproduction occurred for " + this.getClass().getSimpleName() + " at " + newPos);
            }
        } else { // różne gatunki - walka
            if (this.getStrength() >= other.getStrength()) {
                world.removeOrganism(other);
                // Po wygranej walce przechodzimy na pozycję przeciwnika
                this.position = other.getPosition();
                System.out.println(this.getClass().getSimpleName() + " wins fight and moves to " + this.position);
            } else {
                world.removeOrganism(this);
                System.out.println(this.getClass().getSimpleName() + " loses fight");
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
