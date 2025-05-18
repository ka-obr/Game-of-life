import javax.swing.*;
import java.awt.*;

public abstract class Plant extends Organism {
    public Plant(int strength, Point position, World world, int age) {
        super(strength, 0, position, world, age);
    }

    private void createPlantByType(Class<? extends Plant> plantType, Point position) {
        world.createOrganismAtPosition(plantType, position, 0);
        String message = "Organism " + plantType.getSimpleName() + " reproduced";
        world.getWindow().addMessage(message);
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
