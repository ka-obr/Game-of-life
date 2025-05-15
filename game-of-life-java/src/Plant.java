import javax.swing.*;
import java.awt.*;

public abstract class Plant extends Organism {
    public Plant(int strength, Point position, World world, int age) {
        super(strength, 0, position, world, age);
    }

    public void createPlantByType(Class<? extends Plant> plantType, Point position) {
        if (plantType.equals(Grass.class)) {
            Grass grass = new Grass(position, world, 0);
            world.addOrganism(grass);
            String message = "Organism Grass reproduced";
            world.getWindow().addMessage(message);
        }
        else if (plantType.equals(Dandelion.class)) {
            Dandelion dandelion = new Dandelion(position, world, 0);
            world.addOrganism(dandelion);
            String message = "Organism Dandelion reproduced";
            world.getWindow().addMessage(message);
        }
        // Można dodać więcej typów roślin w przyszłości
    }

    protected boolean canReproduceThisTurn() {
        return (Math.random() < 0.05); // 5% szans na reprodukcję
    }

    protected boolean hasFreeSpace() {
        return world.hasFreeSpaceAround(position);
    }

    protected void reproduce(Point position) {
        Point newPosition = world.getRandomFreeSpaceAround(position);
        createPlantByType(this.getClass(), newPosition);
    }

    @Override
    public void action() {
        if(canReproduceThisTurn() && hasFreeSpace() && age != 0) {
            reproduce(position);
        }
        age++;
    }

    @Override
    public void collision(Organism other) {

    }
}
