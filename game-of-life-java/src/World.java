import lib.Size;

import java.awt.*;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Comparator;
import java.io.Serializable;

public class World implements Serializable {
    private static final long serialVersionUID = 1L;

    private List<Organism> organisms;
    private Size size;
    private transient Window window;

    public void setWindow(Window window) {
        this.window = window;
    }

    public void setWorldReferenceForAll() {
        for (Organism org : organisms) {
            org.setWorld(this);
        }
    }

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

    public Window getWindow() {
        return window;
    }

    public void update(String input) {
        // Sortowanie organizmów według inicjatywy, a następnie wieku
        organisms.sort(Comparator.comparingInt(Organism::getInitiative).reversed()
                                  .thenComparingInt(Organism::getAge));

        for(Organism organism : organisms) {
            organism.setHasActed(false);
        }

        List<Organism> copy = new ArrayList<>(organisms);
        for (Organism organism : copy) {
            if (!organisms.contains(organism)) continue; // skip if killed this turn
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

    public boolean isWithinBounds(Point position) {
        return position.x >= 0 && position.x < size.x && position.y >= 0 && position.y < size.y;
    }

    public Point generateRandomPosition(Point currentPosition) {
        int[][] directions = { {0, -1}, {0, 1}, {1, 0}, {-1, 0} };
        List<Point> validPositions = new ArrayList<>();

        for (int[] d : directions) {
            Point newPos = new Point(currentPosition.x + d[0], currentPosition.y + d[1]);
            if (isWithinBounds(newPos)) {
                validPositions.add(newPos);
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

    public Point generateSafePosition(Point position) {
        List<int[]> displacements = new ArrayList<>(java.util.Arrays.asList(
                new int[]{0, 1}, new int[]{1, 0}, new int[]{-1, 0}, new int[]{0, -1}
        ));

        Collections.shuffle(displacements); // Losowe przetasowanie kierunków

        Organism org = getOrganismAtPosition(position);

        for (int[] displacement : displacements) {
            Point neighbor = new Point(position.x + displacement[0], position.y + displacement[1]);

            if (isWithinBounds(neighbor)) { // Sprawdzanie granic planszy
                Organism other = getOrganismAtPosition(neighbor);
                if (other != null && other.getStrength() > org.getStrength()) {
                    continue; // Pomijamy, jeśli sąsiad jest silniejszy
                }
                return neighbor; // Zwracamy bezpieczną pozycję
            }
        }

        return position; // Jeśli brak bezpiecznych pozycji, zwracamy bieżącą pozycję
    }

    public Organism getOrganismAtPosition(Point position) {
        for (Organism organism : organisms) {
            if (organism.getPosition().equals(position)) {
                return organism;
            }
        }
        return null; // Brak organizmu na tej pozycji
    }

    public void createOrganism(Class<? extends Organism> organismClass, int count, int age) {
        for (int i = 0; i < count; i++) {
            Point position = generateRandomPosition();
            Organism organism = null;
            try {
                organism = organismClass.getConstructor(Point.class, World.class, int.class)
                        .newInstance(position, this, age);
            } catch (InvocationTargetException | NoSuchMethodException | InstantiationException | IllegalAccessException e) {
                throw new RuntimeException(e);
            }
            addOrganism(organism);
        }
    }

    public void createOrganismAtPosition(Class<? extends Organism> organismClass, Point position, int age) {
        Organism organism = null;
        try {
            organism = organismClass.getConstructor(Point.class, World.class, int.class)
                    .newInstance(position, this, age);
        } catch (InstantiationException | NoSuchMethodException | IllegalAccessException | InvocationTargetException e) {
            throw new RuntimeException(e);
        }
        addOrganism(organism);
    }

    public void killNeighbors(Point position, int type) {
        // type = 1 - animals, type = 0 - everything
        final int[] dx = {-1, -1, -1, 0, 0, 1, 1, 1};
        final int[] dy = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int i = 0; i < 8; i++) {
            Point neighbor = new Point(position.x + dx[i], position.y + dy[i]);
            if (isWithinBounds(neighbor)) { // Sprawdzanie granic planszy
                Organism other = getOrganismAtPosition(neighbor);
                if (other != null) {
                    if (type == 1 && other instanceof Animal) {
                        removeOrganism(other);
                        String message = "Organism " + other.getClass().getSimpleName() + " was killed by Hogweed";
                        window.addMessage(message);
                    } else if (type == 0) {
                        removeOrganism(other);
                        String message = "Organism " + other.getClass().getSimpleName() + " was killed by Human";
                        window.addMessage(message);
                    }
                }
            }
        }
    }

    public Point getRandomSpaceDoubleMove(Point position) {
        List<int[]> displacements = new ArrayList<>(java.util.Arrays.asList(
            new int[]{0, 1}, new int[]{0, -1}, new int[]{1, 0}, new int[]{-1, 0}, // Single moves
            new int[]{0, 2}, new int[]{0, -2}, new int[]{2, 0}, new int[]{-2, 0}  // Double moves
        ));

        java.util.Collections.shuffle(displacements); // Losowe przetasowanie kierunków

        for (int[] displacement : displacements) {
            Point neighbor = new Point(position.x + displacement[0], position.y + displacement[1]);

            if (isWithinBounds(neighbor)) { // Sprawdzanie granic planszy
                return neighbor; // Zwracamy pierwszą dostępną pozycję
            }
        }

        return position; // Jeśli brak dostępnych pozycji, zwracamy bieżącą pozycję
    }

    public Point getRandomFreeSpaceAround(Point position) {
        List<int[]> displacements = new ArrayList<>(java.util.Arrays.asList(
                new int[]{0, 1}, new int[]{0, -1}, new int[]{1, 0}, new int[]{-1, 0}, // Single moves
                new int[]{1, 1}, new int[]{1, -1}, new int[]{-1, 1}, new int[]{-1, -1} // Diagonal moves
        ));

        java.util.Collections.shuffle(displacements); // Losowe przetasowanie kierunków

        for (int[] displacement : displacements) {
            Point neighbor = new Point(position.x + displacement[0], position.y + displacement[1]);

            if (isWithinBounds(neighbor) && getOrganismAtPosition(neighbor) == null) {
                return neighbor; // Zwracamy pierwsze wolne sąsiednie pole
            }
        }

        return new Point(-1, -1); // Jeśli brak wolnych pól, zwracamy nieprawidłową pozycję
    }

    public boolean hasFreeSpaceAround(Point position) {
        final int[] dx = {-1, -1, -1, 0, 0, 1, 1, 1};
        final int[] dy = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int i = 0; i < 8; i++) {
            Point neighbor = new Point(position.x + dx[i], position.y + dy[i]);

            if (isWithinBounds(neighbor) && getOrganismAtPosition(neighbor) == null) {
                return true; // Znaleziono wolne pole
            }
        }
        return false; // Brak wolnych pól
    }
}