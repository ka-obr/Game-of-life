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

    public void update() {
        // Sortowanie organizmów według inicjatywy, a następnie wieku
        organisms.sort(Comparator.comparingInt(Organism::getInitiative).reversed()
                                  .thenComparingInt(Organism::getAge));

        // Wywoływanie metody action dla każdego organizmu
        List<Organism> copy = new ArrayList<>(organisms);
        for (Organism organism : copy) {
            organism.action();
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
}
