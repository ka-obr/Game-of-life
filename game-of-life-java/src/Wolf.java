import javax.swing.*;
import java.awt.*;

public class Wolf extends Animal {
    private static final ImageIcon wolfIcon = new ImageIcon("images/wolf.png");
    public static final Image scaledWolfIcon = wolfIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Wolf(Point position, World world, int age) {
        super(9, 5, position, world, age); // Strength = 9, Initiative = 5
    }

    @Override
    public ImageIcon getIcon() {
        return wolfIcon; // Zwracanie zcache'owanej ikony
    }
}
