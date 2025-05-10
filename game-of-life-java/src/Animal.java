import lib.Size;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public abstract class Animal extends Organism {
    public Animal(int strength, int initiative, Point position, World world, int age) {
        super(strength, initiative, position, world, age);
    }

    // Losowy ruch: góra, dół, prawo lub lewo
    public void move() {
        int[][] directions = { {0, -1}, {0, 1}, {1, 0}, {-1, 0} };
        List<int[]> validDirections = new ArrayList<>();
        Size worldSize = world.getSize();

        // Filtrujemy kierunki, które są w granicach świata
        for (int[] d : directions) {
            int newX = position.x + d[0];
            int newY = position.y + d[1];
            if (newX >= 0 && newX < worldSize.x && newY >= 0 && newY < worldSize.y) {
                validDirections.add(d);
            }
        }

        // Jeśli są dostępne kierunki, wybieramy losowy
        if (!validDirections.isEmpty()) {
            int[] chosenDirection = validDirections.get((int) (Math.random() * validDirections.size()));
            Point newPos = new Point(position.x + chosenDirection[0], position.y + chosenDirection[1]);

            if (world.isTileOccupied(newPos)) {
                // Znajdujemy organizm na nowej pozycji i wywołujemy collision
                for (Organism other : world.getOrganisms()) {
                    if (other.getPosition().equals(newPos)) {
                        collision(other);
                        break;
                    }
                }
            } else {
                position = newPos; // Przesuwamy organizm na nową pozycję
            }
        }
    }

    @Override
    public void collision(Organism other) {
        if (this.getClass().equals(other.getClass())) {
            if (other.getAge() == 0) {
                return;
            }

            // Reprodukcja
            int[][] directions = { {0, -1}, {0, 1}, {1, 0}, {-1, 0} };
            for (int[] d : directions) {
                Point newPos = new Point(position.x + d[0], position.y + d[1]);
                Size worldSize = world.getSize();
                if (newPos.x >= 0 && newPos.x < worldSize.x && newPos.y >= 0 && newPos.y < worldSize.y) {
                    if (!world.isTileOccupied(newPos)) {
                        if (this instanceof Sheep) {
                            Sheep baby = new Sheep(newPos, world, 0);
                            world.addOrganism(baby);
                            System.out.println("Reproduction occurred: new Sheep at " + newPos);
                        }
                        break;
                    }
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
