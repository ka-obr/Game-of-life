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
    protected void plantCollision(Organism plant, Organism animal) {
        if (plant instanceof Guarana) {
            plant.collision(animal);
        }
        else if(plant instanceof Hogweed) {
            plant.collision(animal);
        }
    }

    @Override
    public void collision(Organism other) {
        if (isSameSpecies(other)) {
            handleReproduction(other);
        } else {
            handleFight(other);
        }
    }

    private boolean isSameSpecies(Organism other) {
        return this.getClass().equals(other.getClass());
    }

    private void handleReproduction(Organism other) {
        if (this.getAge() == 0 || other.getAge() == 0) {
            // Nie reprodukujemy się z noworodkiem
            return;
        }
        Point newPos = world.generateRandomPosition(position);
        if (newPos != null && !world.isTileOccupied(newPos)) {
            createAnimalByType(this.getClass(), newPos);
        }
    }

    private void handleFight(Organism other) {
        plantCollision(other, this);
        if (this.getStrength() >= other.getStrength()) {
            winFight(other);
        } else {
            loseFight(other);
        }
    }

    private void winFight(Organism other) {
        world.removeOrganism(other);
        this.position = other.getPosition(); // Przejście na pozycję przeciwnika
        String message = "Organism " + other.getClass().getSimpleName() + " was killed by " + this.getClass().getSimpleName();
        world.getWindow().addMessage(message);
    }

    private void loseFight(Organism other) {
        if(other instanceof Nightshade) {
            other.collision(this);
            return;
        }
        world.removeOrganism(this);
        String message = "Organism " + this.getClass().getSimpleName() + " was killed by " + other.getClass().getSimpleName();
        world.getWindow().addMessage(message);
    }

    @Override
    public void action() {
        age++; // Inkrementacja wieku
        if (age > 1) {
            move(); // Ruch zwierzęcia
        }
    }

}
