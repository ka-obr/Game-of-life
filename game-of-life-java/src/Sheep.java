import javax.swing.*;
import java.awt.*;
  
public class Sheep extends Animal {
    public static final ImageIcon sheepIcon = new ImageIcon("images/sheep.png");
    public static final Image scaledSheepIcon = sheepIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Sheep(Point position, World world, int age) {
        super(4, 4, position, world, age); // Strength = 4, Initiative = 4
    }
  
    @Override
    public ImageIcon getIcon() {
        return sheepIcon; // Zwracanie zcache'owanej ikony
    }
}
