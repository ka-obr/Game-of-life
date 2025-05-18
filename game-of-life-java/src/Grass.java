import javax.swing.*;
import java.awt.*;

public class Grass extends Plant {
    private static final ImageIcon grassIcon = new ImageIcon("images/grass.png");
    static final Image scaledGrassIcon = grassIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Grass(Point position, World world, int age) {
        super(0, position, world, age);
    }

    @Override
    public ImageIcon getIcon() {
        return grassIcon;
    }
}
