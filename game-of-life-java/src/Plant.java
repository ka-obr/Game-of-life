import javax.swing.*;
import java.awt.*;

public abstract class Plant extends Organism {
    public Plant(int strength, Point position, World world, int age) {
        super(strength, 0, position, world, age);
    }

    public void createPlantByType(Class<? extends Plant> plantType, Point position) {
//        if (plantType.equals(Grass.class)) {
//            Grass grass = new Grass(position, world, 0);
//            world.addOrganism(grass);
//            String message = "New Grass spawned at " + position;
//            world.getWindow().addMessage(message);
//        } else if (plantType.equals(Dandelion.class)) {
//            Dandelion dandelion = new Dandelion(position, world, 0);
//            world.addOrganism(dandelion);
//            String message = "New Dandelion spawned at " + position;
//            world.getWindow().addMessage(message);
//        }
        // Można dodać więcej typów roślin w przyszłości
    }

    @Override
    public void action() {
        // Domyślna implementacja dla roślin (np. brak ruchu)
    }

    @Override
    public void collision(Organism other) {
        // Rośliny nie inicjują kolizji
    }
}
