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
            String message = "Organism Sheep reproduced";
            world.getWindow().addMessage(message);
        } else if (animalType.equals(Wolf.class)) {
            Wolf baby = new Wolf(position, world, 0);
            world.addOrganism(baby);
            String message = "Organism Wolf reproduced";
            world.getWindow().addMessage(message);
        } else if (animalType.equals(Fox.class)) {
            Fox baby = new Fox(position, world, 0);
            world.addOrganism(baby);
            String message = "Organism Fox reproduced";
            world.getWindow().addMessage(message);
        } else if (animalType.equals(Turtle.class)) {
            Turtle baby = new Turtle(position, world, 0);
            world.addOrganism(baby);
            String message = "Organism Turtle reproduced";
            world.getWindow().addMessage(message);
        } else if (animalType.equals(Antelope.class)) {
            Antelope baby = new Antelope(position, world, 0);
            world.addOrganism(baby);
            String message = "Organism Antelope reproduced";
            world.getWindow().addMessage(message);
        }
    }


    protected boolean haveSavedAttack(Organism other) {
        if (other instanceof Turtle && this.getStrength() < 5) {
            return true;
        } else if (other instanceof Antelope) {
            other.escapeCollision(this);
            return false;
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
            other = world.getOrganismAtPosition(newPos);
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
            }
        } else { // różne gatunki - walka
            if (this.getStrength() >= other.getStrength()) {
                world.removeOrganism(other);
                // Po wygranej walce przechodzimy na pozycję przeciwnika
                this.position = other.getPosition();
                String message = "Organism " + other.getClass().getSimpleName() + " was killed by " + this.getClass().getSimpleName();
                world.getWindow().addMessage(message);
            } else {
                world.removeOrganism(this);
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
