import javax.swing.*;
import java.awt.*;

public class Grass extends Plant {
    private static final ImageIcon grassIcon = new ImageIcon("images/grass.png");
    static final Image scaledGrassIcon = grassIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Grass(Point position, World world, int age) {
        super(0, position, world, age); // Siła = 0, inicjatywa = 0 (domyślnie w Plant)
    }

    @Override
    public ImageIcon getIcon() {
        return grassIcon;
    }

//    @Override
//    public void action() {
//        // Grass może np. rozprzestrzeniać się na sąsiednie pola
//        Point newPos = world.getRandomFreeSpaceAround(position);
//        if (newPos.x != -1 && newPos.y != -1) {
//            Grass newGrass = new Grass(newPos, world, 0);
//            world.addOrganism(newGrass);
//            String message = "Grass spread to " + newPos;
//            world.getWindow().addMessage(message);
//        }
//    }
}
