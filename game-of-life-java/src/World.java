import lib.Size;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Comparator;

public class World {
    private List<Organism> organisms;
    private Size size;

    public World(Size size) {
        this.organisms = new ArrayList<Organism>();
        this.size = size;
    }

    public Size getSize() {
        return size;
    }

    public List<Organism> getOrganisms() {
        return organisms;
    }

    public void update(String input) {
        // Sortowanie organizmów według inicjatywy, a następnie wieku
        organisms.sort(Comparator.comparingInt(Organism::getInitiative).reversed()
                                  .thenComparingInt(Organism::getAge));

        // Wywoływanie metody action dla każdego organizmu
        List<Organism> copy = new ArrayList<>(organisms);
        for (Organism organism : copy) {
            organism.action(input);
        }

        System.out.println("Number of organisms: " + organisms.size());
    }

    public boolean isTileOccupied(Point position) {
        for (Organism organism : organisms) {
            if (organism.getPosition().equals(position)) {
                return true; // Kafelek jest zajęty
            }
        }
        return false; // Kafelek jest wolny
    }

    public void addOrganism(Organism organism) {
        if (!isTileOccupied(organism.getPosition())) {
            organisms.add(organism);
        } else {
            System.out.println("Tile at " + organism.getPosition() + " is already occupied!");
        }
    }

    public void removeOrganism(Organism organism) {
        organisms.remove(organism);
    }

    public Point generateRandomPosition(Point currentPosition) {
        int[][] directions = { {0, -1}, {0, 1}, {1, 0}, {-1, 0} };
        List<Point> validPositions = new ArrayList<>();
        Size worldSize = getSize();

        for (int[] d : directions) {
            int newX = currentPosition.x + d[0];
            int newY = currentPosition.y + d[1];
            if (newX >= 0 && newX < worldSize.x && newY >= 0 && newY < worldSize.y) {
                validPositions.add(new Point(newX, newY));
            }
        }

        if (!validPositions.isEmpty()) {
            return validPositions.get((int) (Math.random() * validPositions.size()));
        }
        return null; // Brak dostępnych pozycji
    }

    // Nowa metoda generująca losową pozycję w obrębie planszy
    public Point generateRandomPosition() {
        java.util.Random random = new java.util.Random();
        Point position;
        do {
            int x = random.nextInt(size.x);
            int y = random.nextInt(size.y);
            position = new Point(x, y);
        } while (isTileOccupied(position)); // Sprawdzanie, czy pole nie jest zajęte
        return position;
    }

    public Organism getOrganismAtPosition(Point position) {
        for (Organism organism : organisms) {
            if (organism.getPosition().equals(position)) {
                return organism;
            }
        }
        return null; // Brak organizmu na tej pozycji
    }

    public void addSheep(int count, int age) {
        Point pos = generateRandomPosition();
        for (int i = 0; i < count; i++) {
            Sheep sheep = new Sheep(pos, this, age);
            addOrganism(sheep);
        }
    }

    public void addWolf(int count, int age) {
        Point pos = generateRandomPosition();
        for (int i = 0; i < count; i++) {
            Wolf wolf = new Wolf(pos, this, age);
            addOrganism(wolf);
        }
    }

    public void killNeighbors(Point position, int type) {
        // type = 1 - animals, type = 0 - everything
        final int[] dx = {-1, -1, -1, 0, 0, 1, 1, 1};
        final int[] dy = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int i = 0; i < 8; i++) {
            Point neighbor = new Point(position.x + dx[i], position.y + dy[i]);
            if (neighbor.x >= 0 && neighbor.x < size.x && neighbor.y >= 0 && neighbor.y < size.y) {
                Organism other = getOrganismAtPosition(neighbor);
                if (other != null) {
                    if (type == 1 && other instanceof Animal) {
                        removeOrganism(other);
                        System.out.println("Killed animal at " + neighbor);
                    } else if (type == 0) {
                        removeOrganism(other);
                        System.out.println("Killed organism at " + neighbor);
                    }
                }
            }
        }
    }
}
